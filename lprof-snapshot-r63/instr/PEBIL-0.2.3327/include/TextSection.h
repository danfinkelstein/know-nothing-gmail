#ifndef _TextSection_h_
#define _TextSection_h_

#include <Base.h>
#include <X86Instruction.h>
#include <RawSection.h>
#include <SymbolTable.h>
#include <Vector.h>

class BasicBlock;
class BinaryInputFile;
class BinaryOutputFile;
class Block;
class ElfFile;
class Function;
class X86Instruction;
class TextSection;

class TextObject : public Base {
protected:
    TextSection* textSection;
    uint32_t index;
    Symbol* symbol;

    Vector<X86Instruction*>* digestLinear();
public:
    TextObject(PebilClassTypes typ, TextSection* text, uint32_t idx, Symbol* sym, uint64_t addr, uint32_t sz);
    ~TextObject() {}

    uint32_t getIndex() { return index; }
    uint64_t getBaseAddress() { return baseAddress; }
    bool inRange(uint64_t addr);
    char* charStream();
    bool isFunction();

    virtual uint32_t getNumberOfInstructions() { __SHOULD_NOT_ARRIVE; }
    TextSection* getTextSection() { return textSection; }
    uint64_t getSymbolValue() { return symbol->GET(st_value); }

    virtual uint32_t getAllInstructions(X86Instruction** allinsts, uint32_t nexti) { __SHOULD_NOT_ARRIVE; }

    virtual void dump(BinaryOutputFile* binaryOutputFile, uint32_t offset) { __SHOULD_NOT_ARRIVE; }
    virtual const char* getName();
    virtual uint32_t digest(Vector<AddressAnchor*>* addressAnchors) { __SHOULD_NOT_ARRIVE; }
    virtual void printDisassembly(bool instructionDetail) { __SHOULD_NOT_ARRIVE; }

    virtual void print() { __SHOULD_NOT_ARRIVE; }
};

class FreeText : public TextObject {
protected:
    Vector<Block*> blocks;
    bool usesInstructions;

public:
    FreeText(TextSection* text, uint32_t idx, Symbol* sym, uint64_t addr, uint32_t sz, bool usesI);
    ~FreeText();

    void dump(BinaryOutputFile* binaryOutputFile, uint32_t offset);
    uint32_t digest(Vector<AddressAnchor*>* addressAnchors);

    uint32_t getAllInstructions(X86Instruction** allinsts, uint32_t nexti);

    Block* getBlock(uint32_t idx) { return blocks[idx]; }
    uint32_t getNumberOfInstructions();
    void printDisassembly(bool instructionDetail);

    void print();
};

class TextSection : public RawSection {
protected:
    uint32_t index;
    Vector<TextObject*> sortedTextObjects;

    ByteSources source;
public:
    TextSection(char* filePtr, uint64_t size, uint16_t scnIdx, uint32_t idx, ElfFile* elf, ByteSources src);
    ~TextSection();

    void printInstructions();
    Vector<Symbol*> discoverTextObjects();

    Function* replaceFunction(uint32_t idx, Function* replacementFunction);

    ByteSources getByteSource();
    void setByteSource(ByteSources src) { source = src; }
    uint32_t setSizeInBytes(uint32_t sz) { sizeInBytes = sz; }
    uint32_t readNoFile();
    uint32_t getIndex() { return index; }
    uint32_t disassemble();
    uint32_t generateCFGs(Vector<AddressAnchor*>* addressAnchors);
    uint32_t printDisassembly(bool instructionDetail);
    uint32_t read(BinaryInputFile* b);
    uint32_t disassemble(BinaryInputFile* b);

    uint64_t findInstrumentationPoint(uint64_t addr, uint32_t size, InstLocations loc);

    bool verify();

    void dump (BinaryOutputFile* binaryOutputFile, uint32_t offset);

    BasicBlock* getBasicBlockAtAddress(uint64_t addr);
    X86Instruction* getInstructionAtAddress(uint64_t addr);
    uint32_t getAllInstructions(X86Instruction** allinsts, uint32_t nexti);

    uint64_t getBaseAddress();
    bool inRange(uint64_t addr);

    uint32_t getNumberOfTextObjects() { return sortedTextObjects.size(); }
    TextObject* getTextObject(uint32_t idx) { return sortedTextObjects[idx]; }

    uint32_t getNumberOfBasicBlocks();
    uint32_t getNumberOfMemoryOps();
    uint32_t getNumberOfFloatOps();
    uint32_t getNumberOfInstructions();

    Vector<X86Instruction*>* swapInstructions(uint64_t addr, Vector<X86Instruction*>* replacements);

    void printLoops();
    uint32_t buildLoops();
};


#endif /* _TextSection_h_ */

