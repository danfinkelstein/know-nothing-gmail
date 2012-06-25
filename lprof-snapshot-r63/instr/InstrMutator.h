#ifndef _InstrMutator_h_
#define _InstrMutator_h_

#include <map>
#include <vector>

#include <linux/lprof.h>
#include <ElfFileInst.h>
#include "common.h"

class InstrMutator: public ElfFileInst {
private:
    InstrumentationFunction* entryFunc;
    InstrumentationFunction* exitFunc;
    uint64_t iiAddr;
    uint64_t statsAddr;
    uint64_t resultArray;
    std::map<uint64_t, uint64_t> funcSlots;

    uint64_t myReserveDataOffset(uint64_t sz);
    void pop_amap(Function*f, std::map<uint32_t, uint32_t>& amap);
    void buildEntrySnippet(Function* f, InstrumentationSnippet** entry);
    void buildExitSnippet(Function* f, InstrumentationSnippet** exit);
    void buildCallSnippets(Function* f,
			   InstrumentationSnippet** exit,
			   InstrumentationSnippet** rentry);
    void createFunctionEntry(Function* f, uint32_t slot);
    void createSymbolEntry(Symbol* f, uint64_t addresss, uint32_t slot);
    void setupII(InstrumentationInfo& ii);
    void cs_setup(void (*begin)(void), void (*end)(void), void** addrs);

public:
    std::vector<uint64_t> dataAddresses;

    InstrMutator(ElfFile* elf);
    ~InstrMutator() { }

    virtual void declare();
    virtual void instrument();
    virtual void usesModifiedProgram() { }

    virtual const char* briefName() { return "LProf Instrumentation Mutator"; }
};

#endif
