#ifndef _Function_h_
#define _Function_h_

#include <BitSet.h>
#include <X86Instruction.h>
#include <TextSection.h>
#include <Vector.h>

class BasicBlock;
class BinaryInputFile;
class BinaryOutputFile;
class FlowGraph;
class InstrumentationPoint;
class Symbol;
class TextObject;

class Function : public TextObject {
private:
    const static uint32_t recursivedisasmMask     = 0x1;
    const static uint32_t instrumentationfuncMask = 0x2;
    const static uint32_t jumptableMask           = 0x4;
    const static uint32_t disasmfailMask          = 0x8;
    const static uint32_t relocatedMask           = 0x10;

protected:
    FlowGraph* flowGraph;
    HashCode hashCode;
    uint64_t badInstruction;
    uint64_t flags;
    uint32_t stackSize;

    Vector<X86Instruction*>* digestRecursive();
public:

    Function(TextSection* text, uint32_t idx, Symbol* sym, uint32_t sz);
    ~Function();

    uint32_t getStackSize() { return stackSize; }
    uint32_t findStackSize();

    bool hasLeafOptimization();

    bool isRecursiveDisasm()          { return (flags & recursivedisasmMask); }
    bool isInstrumentationFunction()  { return (flags & instrumentationfuncMask); }
    bool isJumpTable()                { return (flags & jumptableMask); }
    bool isDisasmFail()               { return (flags & disasmfailMask); }
    bool isRelocated()                { return (flags & relocatedMask); }

    void setRecursiveDisasm()         { flags |= recursivedisasmMask; }
    void setInstrumentationFunction() { flags |= instrumentationfuncMask; }
    void setJumpTable()               { flags |= jumptableMask; }
    void setDisasmFail()              { flags |= disasmfailMask; }
    void setRelocated()               { flags |= relocatedMask; }

    uint64_t getBadInstruction() { return badInstruction; }
    void setBadInstruction(uint64_t addr) { badInstruction = addr; }

    bool hasCompleteDisassembly();
    bool containsCallToRange(uint64_t lowAddr, uint64_t highAddr);

    bool callsSelf();
    bool hasSelfDataReference();
    bool refersToInstruction();
    bool containsReturn();

    uint32_t bloatBasicBlocks(Vector<InstrumentationPoint*>* instPoints);
    uint32_t addSafetyJump(X86Instruction* tgtInstruction);

    void setBaseAddress(uint64_t newBaseAddress);

    Symbol* getFunctionSymbol() { return symbol; }
    uint32_t generateCFG(Vector<X86Instruction*>* instructions, Vector<AddressAnchor*>* addressAnchors);

    FlowGraph* getFlowGraph() { return flowGraph; }
    uint32_t getNumberOfBasicBlocks();
    BasicBlock* getBasicBlock(uint32_t idx);
    X86Instruction* getInstructionAtAddress(uint64_t addr);
    BasicBlock* getBasicBlockAtAddress(uint64_t addr);

    uint32_t getNumberOfInstructions();
    uint32_t getNumberOfBytes();

    uint32_t getAllInstructions(X86Instruction** allinsts, uint32_t nexti);

    void printInstructions();

    uint32_t digest(Vector<AddressAnchor*>* addressAnchors);
    void dump (BinaryOutputFile* binaryOutputFile, uint32_t offset);
    bool verify();
    void print();

    const char* briefName() { return "Function"; }
    HashCode getHashCode() { return hashCode; }

    Vector<X86Instruction*>* swapInstructions(uint64_t addr, Vector<X86Instruction*>* replacements);
    uint64_t findInstrumentationPoint(uint64_t addr, uint32_t size, InstLocations loc);

    void printDisassembly(bool instructionDetail);
};

#endif /* _Function_h_ */
