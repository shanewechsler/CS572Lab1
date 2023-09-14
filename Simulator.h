#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stack>

class Memory{
    private:
        unsigned int baseAddress;
        
        unsigned int memoryEntries[256];

    public:
        Memory(unsigned int baseAddress){
            this->baseAddress = baseAddress;
        };

        unsigned int ReadAddress(unsigned int address);

        void WriteToAddress(unsigned int word, unsigned int address);

        unsigned int ConvertAddressToIndex(unsigned int address);

        unsigned int ConvertIndexToAddress(unsigned int index);
};

#endif //SIMULATOR_H