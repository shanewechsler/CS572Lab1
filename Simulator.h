#ifndef SIMULATOR_H
#define SIMULATOR_H

#define USER_TEXT_BASE  0x00400000
#define USER_DATA_BASE  0x01000000

#define MEMORY_ENTRY_COUNT 0x0800

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

        unsigned int ReadAddress(unsigned int address); // "load", reads the data @address

        void WriteToAddress(int word, unsigned int address); //"store", stores word @address

        unsigned int ConvertAddressToIndex(unsigned int address); //converts 32 bit address into an array index for memoryEntries

        unsigned int ConvertIndexToAddress(unsigned int index); //converts memoryEntries index to a 32 bit address. 
};

class DataLoader{
    private:
        std::map<std::string, unsigned int> dataMappings; // variableName -> address

    public:
        void storeData(Memory &data, std::string variableName, unsigned int value); //store value at next open memory block in `data` and maps the variable name to that address. 

        unsigned int getMapping(std::string variableName); //returns the address name that corresponds to the variable name
    
};
#endif //SIMULATOR_H