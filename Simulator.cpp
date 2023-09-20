#include "Simulator.h"
#include <cstring>

unsigned int Memory::ReadAddress(unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    return this->memoryEntries[index];
}

void Memory::WriteToAddress(int word, unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    this->memoryEntries[index] = word;
}

unsigned int Memory::ConvertAddressToIndex(unsigned int address){
    return (address - this->baseAddress) >> 2;
}

unsigned int Memory::ConvertIndexToAddress(unsigned int index){
    return (index + this->baseAddress) << 2;
}

unsigned int Memory::getBaseAddress(){
    return this->baseAddress;
}

void DataLoader::storeData(Memory &data, std::string variableName, unsigned int value){
    unsigned int address = data.getBaseAddress() + (wordsInMem * 4);
    this->dataMappings[variableName] = address;
    data.WriteToAddress(value, address);
    wordsInMem++;
}

unsigned int DataLoader::getMapping(std::string variableName){
    return this->dataMappings[variableName];
}


