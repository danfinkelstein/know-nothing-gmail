#include "InstrMutator.h"
#include "common.h"

#include <BasicBlock.h>
#include <Function.h>
#include <Instrumentation.h>
#include <SymbolTable.h>
#include <RelocationTable.h>
#include <GlobalOffsetTable.h>
#include <X86Instruction.h>
#include <X86InstructionFactory.h>

#include <udis86.h>

#include <vector>
#include <iostream>

using namespace std;

extern "C" {
    /* Symbols from asm64.S */

    extern void func_entry64(void);
    extern void func_entry64_cs_begin(void);
    extern void func_entry64_cs_end(void);

    extern void func_rentry64(void);
    extern void func_rentry64_cs_begin(void);
    extern void func_rentry64_cs_end(void);

    extern void func_exit64(void);
    extern void func_exit64_cs_begin(void);
    extern void func_exit64_cs_end(void);

    extern void __func_info(void);
    extern void __stats(void);
};

#define ENTRY_FUNCTION ((char*)"initlprof")
#define EXIT_FUNCTION ((char*)"exitlprof")
#define INST_LIB_NAME ((char*)"liblprof.so")

InstrMutator::InstrMutator(ElfFile* elf) :
    ElfFileInst(elf), entryFunc(NULL), exitFunc(NULL) {
}

uint64_t InstrMutator::myReserveDataOffset(uint64_t sz) {
    uint64_t addr = reserveDataOffset(sz);
    uint64_t off  = getInstDataAddress();
    for (uint64_t o = 0; o < sz; o++) {
	dataAddresses.push_back(addr + o + off);
    }
    return addr;
}

void InstrMutator::declare() {
    declareLibrary(INST_LIB_NAME);

    exitFunc = declareFunction(EXIT_FUNCTION);
    ASSERT(exitFunc && "Cannot find exit function, are you sure it was declared?");

    entryFunc = declareFunction(ENTRY_FUNCTION);
    ASSERT(entryFunc && "Cannot find entry function, are you sure it was declared?");
}

void InstrMutator::cs_setup(void (*begin)(void), void (*end)(void), void** addrs) {
    uint32_t len = (uint64_t)(end) - (uint64_t)(begin);
    uint64_t addr = getInstDataAddress() + myReserveDataOffset(len);
    initializeReservedData(addr, len, (void*)begin);
    addrs[0] = (void*)addr;
    addrs[1] = (void*)(addr + len);
}

void InstrMutator::setupII(InstrumentationInfo& ii) {
    memset(&ii, 0, sizeof(InstrumentationInfo));

    ii.version = 1;
    ii.counters = 1 << 1;

    cs_setup(func_entry64_cs_begin, func_entry64_cs_end, &ii.cs_marker_pairs[0]);
    cs_setup(func_exit64_cs_begin, func_exit64_cs_end, &ii.cs_marker_pairs[2]);
}

bool isExtJump(Function* f, X86Instruction* ins) {
    if (ins->isBranch()) {
	uint64_t tgt = ins->getTargetAddress();
	return (tgt && !f->inRange(tgt));
    }
    return false;
}

void InstrMutator::instrument() {
    TIMER(double t1 = timer(), t2);
    GlobalOffsetTable* got = getElfFile()->getGlobalOffsetTable();
    uint32_t numFuncs = allFunctions.size();
    uint32_t numEntries = numFuncs + 1 + got->getNumberOfEntries();
    InstrumentationInfo ii;

    // the number functions in the code
    uint64_t counterArrayEntries = myReserveDataOffset(sizeof(uint32_t));
     initializeReservedData(getInstDataAddress() + counterArrayEntries, sizeof(uint32_t), &numEntries);


    statsAddr = myReserveDataOffset(sizeof(struct lprof_stats));
    iiAddr    = myReserveDataOffset(sizeof(InstrumentationInfo));
    setupII(ii);
    initializeReservedData(getInstDataAddress() + iiAddr, sizeof(Instrumentation), &ii);

    // an array of counters. note that everything is passed by reference
    resultArray = myReserveDataOffset(numEntries * sizeof(Result));

    // exitFunc->addArgument(counterArrayEntries);
    // exitFunc->addArgument(resultArray);

    // InstrumentationPoint* p = addInstrumentationPoint(getProgramExitBlock(), exitFunc, InstrumentationMode_tramp);
    // ASSERT(p);
    // if (!p->getInstBaseAddress()){
    //     PRINT_ERROR("Cannot find an instrumentation point at the exit function");
    // }

    // entryFunc->addArgument(statsAddr);
    // entryFunc->addArgument(iiAddr);
    // entryFunc->addArgument(counterArrayEntries);
    // entryFunc->addArgument(resultArray);
    // p = addInstrumentationPoint(getProgramEntryBlock(), entryFunc, InstrumentationMode_tramp);
    // ASSERT(p);
    // if (!p->getInstBaseAddress()){
    //     PRINT_ERROR("Cannot find an instrumentation point at the entry function");
    // }

    uint32_t slot = 0;    
    //Create dummy zero/"other" entry
    {
	const char* name = "__lp_unresolved";
	uint64_t nameAddr = myReserveDataOffset(strlen(name) + 1);
	Result r;

	r.ip = 0;
	r.p  = 0;
	r.callCount = 0;
	r.inc = 0;
	r.context_switches = 0;
	r.interrupts = 0;
	r.nameAddr = getInstDataAddress() + nameAddr;
	initializeReservedData(getInstDataAddress() + nameAddr, strlen(name) + 1, (void*)name);
	initializeReservedData(getInstDataAddress() + resultArray + slot*sizeof(Result), sizeof(Result), &r);
    }
    slot++;

    //Create entries for each function
    for (uint32_t i = 0; i < allFunctions.size(); i++) {
    	createFunctionEntry(allFunctions[i], slot++);
    }

    {   //Find dynamic function entry points
	SymbolTable* dst = getElfFile()->getDynamicSymbolTable();
	RelocationTable* plt = getElfFile()->getPLTRelocationTable();
	std::map<uint64_t, uint64_t> gotMap;
	for (uint32_t i=0; i < got->getNumberOfEntries(); i++) {
	    uint64_t addr = got->getEntry(got->minIndex() + i);
	    if (!addr)
		continue;
	    addr -= Size__ProcedureLink_Intermediate;
	    gotMap[got->getEntryAddress(i)] = addr;
	}
	
	for (uint32_t i = 0; i < plt->getNumberOfRelocations(); i++) {
	    Relocation* r = plt->getRelocation(i);
	    uint64_t gotAddr = r->GET(r_offset);
	    if (gotMap.count(gotAddr)) {
		uint64_t fAddr = gotMap[gotAddr];
		createSymbolEntry(dst->getSymbol(r->getSymbol()), fAddr, slot++);
	    }
	}
    }

    numFuncs = getNumberOfExposedFunctions();
    for (uint32_t i = 0; i < numFuncs; i++) {
	Function* f = getExposedFunction(i);

	InstrumentationSnippet *entry;
    	buildEntrySnippet(f, &entry);
	
    	addInstrumentationPoint(f, entry, InstrumentationMode_inline,
				FlagsProtectionMethod_none, InstLocation_prior);
	

	uint32_t numInstr = f->getNumberOfInstructions();
	X86Instruction* instrs[numInstr];
	f->getAllInstructions(instrs, 0);

	for (uint32_t j = 0; j < numInstr; j++) {
	    X86Instruction* ins = instrs[j];

	    // if (ins->isReturn()) {
	    // 	InstrumentationSnippet *exit;
	    // 	buildExitSnippet(f, &exit);
	    // 	addInstrumentationPoint(ins, exit, InstrumentationMode_inline,
	    // 				FlagsProtectionMethod_none, InstLocation_prior);
	    // }

	    // if (ins->isFunctionCall()) {
	    // 	InstrumentationSnippet *exit, *rentry;
	    // 	buildCallSnippets(f, &exit, &rentry);
	    // 	addInstrumentationPoint(ins, exit, InstrumentationMode_inline,
	    // 				FlagsProtectionMethod_none, InstLocation_prior);
	    // 	addInstrumentationPoint(ins, rentry, InstrumentationMode_inline,
	    // 				FlagsProtectionMethod_none, InstLocation_after);
	    // }

	    // if (isExtJump(f, ins)) {
	    // 	InstrumentationSnippet *exit, *rentry;
	    // 	buildCallSnippets(f, &exit, &rentry);
	    // 	addInstrumentationPoint(ins, exit, InstrumentationMode_inline,
	    // 				FlagsProtectionMethod_full, InstLocation_prior);
	    // }
	}
    }

    TIMER(t2 = timer();PRINT_INFOR("___timer: markup  : %.2f seconds",t2-t1);t1=t2);
}

void InstrMutator::createSymbolEntry(Symbol* s, uint64_t address, uint32_t slot) {
    uint64_t nameAddr = myReserveDataOffset(strlen(s->getSymbolName()) + 1);
    Result r;

    r.ip = address;
    r.p  = 0;
    r.callCount = 0;
    r.inc = 0;
    r.context_switches = 0;
    r.interrupts = 0;
    r.nameAddr = getInstDataAddress() + nameAddr;
    initializeReservedData(getInstDataAddress() + nameAddr, strlen(s->getSymbolName()) + 1,
			   (void*)s->getSymbolName());
    initializeReservedData(getInstDataAddress() + resultArray + slot*sizeof(Result), sizeof(Result), &r);
    funcSlots[r.ip] = slot;

    //printf("Symbol Entry(%3u): %p, %s\n", slot, (void*)r.ip, s->getSymbolName());
}

void InstrMutator::createFunctionEntry(Function* f, uint32_t slot) {
    uint64_t nameAddr = myReserveDataOffset(strlen(f->getName()) + 1);
    Result r;

    r.ip = f->getBaseAddress();
    r.p  = 0;
    r.callCount = 0;
    r.inc = 0;
    r.context_switches = 0;
    r.interrupts = 0;
    r.nameAddr = getInstDataAddress() + nameAddr;
    initializeReservedData(getInstDataAddress() + nameAddr, strlen(f->getName()) + 1, (void*)f->getName());
    initializeReservedData(getInstDataAddress() + resultArray + slot*sizeof(Result), sizeof(Result), &r);
    funcSlots[f->getBaseAddress()] = slot;

    //printf("Function Entry(%3u): %p, %s\n", slot, (void*)r.ip, f->getName());
}

#define MAX_ASM 1024
extern "C" void dummy_nocall_end(void);
static void insFromCode(void* buf, map<uint32_t, uint32_t> addrmap, 
			vector<X86Instruction*>& ivec) {
    ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_input_buffer(&ud_obj, (uint8_t*)buf, MAX_ASM);
    ud_set_mode(&ud_obj, 64);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);
    
    while (ud_disassemble(&ud_obj)) {
	if (ud_obj.mnemonic == UD_Icall) {
	    void* tgt = (void*)(5 + ud_obj.operand[0].lval.sdword + (uint64_t)ud_obj.insn_offset + (uint64_t)buf);
	    if (tgt == dummy_nocall_end)
		break;
	}

	unsigned int ilen = ud_insn_len(&ud_obj);
	char     ibuf[32];
	memcpy(ibuf, ud_insn_ptr(&ud_obj), ilen);

	for (int i=0; i<3; i++) {
	    if (ud_obj.operand[i].type == UD_OP_MEM ||
		(ud_obj.operand[i].type == UD_OP_IMM &&
		 ud_obj.operand[i].size == 32)) {
		uint32_t ptr = ud_obj.operand[i].lval.udword;
		if (addrmap.count(ptr)) { 
		    for (int j=0; j<=(ilen-4); j++) {
			uint32_t* a = (uint32_t*)(&ibuf[j]);
			if (*a == (uint32_t)ptr) {
			    *a = (uint32_t)addrmap[ptr];
			    // printf("Replaced\n");
			}
		    }
		}
	    }
	}

	X86Instruction* ins = new X86Instruction(NULL, 0, (char*)ibuf,
						 ByteSource_Instrumentation, 0, true, ilen);

	ivec.push_back(ins);
	// printf("\t%s\n", ud_insn_asm(&ud_obj));
	// printf("\t%s\n", ud_insn_hex(&ud_obj));
    }
    // printf("\n");
}

#define MAP_OFFSET(A,V,S,F)			\
    amap[(uint64_t)(A) + offsetof(S, F)] = (uint64_t)((V) + offsetof(S, F));
//    printf("%25s, %p, %p\n", #F, (void*)((uint64_t)(A) + offsetof(S, F)), (void*)((V) + offsetof(S, F)));

void InstrMutator::pop_amap(Function*f, map<uint32_t, uint32_t>& amap) {
    uint64_t callerAddr = f->getBaseAddress();
    uint64_t callerSlot = 0;
    if (funcSlots.count(callerAddr) && callerAddr != 0) {
	callerSlot = funcSlots[callerAddr];
    }
    uint64_t callerResult = getInstDataAddress() + resultArray 
	+ callerSlot*sizeof(Result);

    MAP_OFFSET(__func_info, callerResult, Result, ip);
    MAP_OFFSET(__func_info, callerResult, Result, nameAddr);
    MAP_OFFSET(__func_info, callerResult, Result, p);
    MAP_OFFSET(__func_info, callerResult, Result, callCount);
    MAP_OFFSET(__func_info, callerResult, Result, inc);
    MAP_OFFSET(__func_info, callerResult, Result, interrupts);
    MAP_OFFSET(__func_info, callerResult, Result, context_switches);
    
    uint64_t statsA = getInstDataAddress() + statsAddr;
    MAP_OFFSET(__stats, statsA, struct lprof_stats, rdpmc_inprogress);
    MAP_OFFSET(__stats, statsA, struct lprof_stats, context_switches);
    MAP_OFFSET(__stats, statsA, struct lprof_stats, timer_interrupts);
    MAP_OFFSET(__stats, statsA, struct lprof_stats, last[1]);
}

void InstrMutator::buildCallSnippets(Function* f,
				     InstrumentationSnippet** exit,
				     InstrumentationSnippet** rentry) {
    vector<X86Instruction*> ivec;

    uint64_t callerAddr = f->getBaseAddress();
    uint64_t callerSlot = 0;
    if (funcSlots.count(callerAddr) && callerAddr != 0) {
	callerSlot = funcSlots[callerAddr];
    }
    uint64_t callerResult = getInstDataAddress() + resultArray 
	+ callerSlot*sizeof(Result);
    
    *rentry = new InstrumentationSnippet();
    *exit = new InstrumentationSnippet();

    if (is64Bit()){
	map<uint32_t, uint32_t> amap;
	pop_amap(f, amap);
	
	ivec.clear();
	insFromCode((void*)func_rentry64, amap, ivec);
	for (int i=0; i<ivec.size(); i++) {
	    (*rentry)->addSnippetInstruction(ivec[i]);
	}

	ivec.clear();
	insFromCode((void*)func_exit64, amap, ivec);
	for (int i=0; i<ivec.size(); i++) {
	    (*exit)->addSnippetInstruction(ivec[i]);
	}
    } else {
	ASSERT(NULL && "32-bit targets not supported yet");
    }

    addInstrumentationSnippet(*rentry);
    addInstrumentationSnippet(*exit);
}

void InstrMutator::buildExitSnippet(Function* f,
				    InstrumentationSnippet** exit) {
    *exit = new InstrumentationSnippet();

    if (is64Bit()){
	map<uint32_t, uint32_t> amap;
	pop_amap(f, amap);

	vector<X86Instruction*> ivec;
	insFromCode((void*)func_exit64, amap, ivec);
	for (int i=0; i<ivec.size(); i++) {
	    (*exit)->addSnippetInstruction(ivec[i]);
	}
    } else {
	ASSERT(NULL && "32-bit targets not supported yet");
    }

    addInstrumentationSnippet(*exit);
}

void InstrMutator::buildEntrySnippet(Function* f,
				     InstrumentationSnippet** entry) {
    vector<X86Instruction*> ivec;

    uint64_t callerAddr = f->getBaseAddress();
    uint64_t callerSlot = 0;
    if (funcSlots.count(callerAddr) && callerAddr != 0) {
	callerSlot = funcSlots[callerAddr];
    }
    uint64_t callerResult = getInstDataAddress() + resultArray 
	+ callerSlot*sizeof(Result);
    
    *entry = new InstrumentationSnippet();

    if (is64Bit()){
	map<uint32_t, uint32_t> amap;
	pop_amap(f, amap);

	ivec.clear();
	insFromCode((void*)func_entry64, amap, ivec);
	for (int i=0; i<ivec.size(); i++) {
	    (*entry)->addSnippetInstruction(ivec[i]);
	}
    } else {
	ASSERT(NULL && "32-bit targets not supported yet");
    }

    addInstrumentationSnippet(*entry);
}
