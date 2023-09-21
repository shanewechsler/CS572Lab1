#ifndef SIMULATOR_H
#define SIMULATOR_H

#define USER_TEXT_BASE  0x00400000
#define USER_DATA_BASE  0x01000000

#define MEMORY_ENTRY_COUNT 0x0800 //2048 memory entries is PLENTY for this assignment

#define OPERAND_LENGTH 32

#define INSTR_IDX 0
#define OPERAND_IDX 1

#define PUSH_SIG 0
#define POP_SIG 1
#define LOAD_SIG 0 
#define STO_SIG 1

#define ADD_SIG 2 
#define MUL_SIG 3
#define END_SIG 4

#include <stack>
#include <string>
#include <fstream>
#include <map>

class Memory{
    private:
        unsigned int baseAddress;
        
        long memoryEntries[MEMORY_ENTRY_COUNT]; 

        int wordsInMemory = 0;

    public:
        Memory(){
            this->baseAddress = 0x0;
        }

        Memory(unsigned int baseAddress){
            this->baseAddress = baseAddress;
        };

        void incrementWordsInMem();

        int getWordsInMem();

        unsigned int getBaseAddress();

        long ReadAddress(unsigned int address); // "load", reads the data @address

        void WriteToAddress(long word, unsigned int address); //"store", stores double word @address

        unsigned int ConvertAddressToIndex(unsigned int address); //converts 32 bit address into an array index for memoryEntries

        unsigned int ConvertIndexToAddress(unsigned int index);
};

class DataLoader{
    private:
        std::map<std::string, unsigned int> dataMappings; // variableName -> address

    public:
        void storeText(Memory &data, unsigned long machineCode);

        void storeData(Memory &data, std::string variableName, unsigned int value); //store value at next open memory block in `data` and maps the variable name to that address. 

        unsigned int getMapping(std::string variableName); //returns the address that corresponds to the variable name
    
};

class Assembler{
    protected:
        std::map<std::string, unsigned int> opcodes;

    public:
        void initMap();

        unsigned int instrCode(char *instr); //returns the int opcode mapped with the ascii value

        unsigned long assembleCode(char *instr); //for no operand instructions, no need to map an address

        unsigned long assembleCode(DataLoader mapper, char *instr, std::string variableName); //pass the data loader(has the variable names -> address mappings)

        unsigned int machineToOp(unsigned long machineCode);

        unsigned int machineToAddress(unsigned long machineCode);
};

class StackAssembler : public Assembler{ //only differences between the StackAssembler and AccumAssembler are the mappings
    public:
        StackAssembler(){
            initMap();
        }
        void initMap();
};

class AccumAssembler : public Assembler{
    public:
        AccumAssembler(){
            initMap();
        }

        void initMap();
};
#endif //SIMULATOR_H