#ifndef SIMULATOR_H
#define SIMULATOR_H

#define USER_TEXT_BASE  0x00400000
#define USER_DATA_BASE  0x01000000

#include <stack>
#include <string>
#include <fstream>
#include <map>

class Memory{
    private:
        unsigned int baseAddress;
        
        int memoryEntries[1024];

    public:
        Memory(){
            this->baseAddress = 0x0;
        }

        Memory(unsigned int baseAddress){
            this->baseAddress = baseAddress;
        };

        unsigned int getBaseAddress();

        unsigned int ReadAddress(unsigned int address);

        void WriteToAddress(int word, unsigned int address);

        unsigned int ConvertAddressToIndex(unsigned int address);

        unsigned int ConvertIndexToAddress(unsigned int index);
};

class DataLoader{
    private:
        std::map<std::string, unsigned int> dataMappings;

        unsigned int wordsInMem = 0;

        const char *delimiters = " \t\r\n\v\f ./:";

    public:
        void storeData(Memory &data, std::string variableName, unsigned int value);

        unsigned int getMapping(std::string variableName);
    
};

#endif //SIMULATOR_H