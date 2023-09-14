#include "Simulator.h"

unsigned int Memory::ReadAddress(unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    return this->memoryEntries[index];
}

void Memory::WriteToAddress(unsigned int word, unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    this->memoryEntries[index] = word;
}

unsigned int Memory::ConvertAddressToIndex(unsigned int address){
    return address - this->baseAddress >> 2;
}

unsigned int Memory::ConvertIndexToAddress(unsigned int index){
    return index + this->baseAddress << 2;
}