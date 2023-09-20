#include "Simulator.h"
#include <cstring>

void Memory::incrementWordsInMem(){
    this->wordsInMemory++;
}

int Memory::getWordsInMem(){
    return this->wordsInMemory;
}

unsigned int Memory::getBaseAddress(){
    return this->baseAddress;
}

unsigned int Memory::ReadAddress(unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    return this->memoryEntries[index];
}

void Memory::WriteToAddress(int word, unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    this->memoryEntries[index] = word;
}

unsigned int Memory::ConvertAddressToIndex(unsigned int address){
    return (address - this->baseAddress) >> 2; //32 bit addresses are in bytes, but we're storing words so divide by 4
}

unsigned int Memory::ConvertIndexToAddress(unsigned int index){
    return (index + this->baseAddress) << 2;
}

void DataLoader::storeData(Memory &data, std::string variableName, unsigned int value){
    unsigned int address = data.getBaseAddress() + (data.getWordsInMem() * 4); //find the next address open for writing in `data`
    this->dataMappings[variableName] = address;
    data.WriteToAddress(value, address);
    data.incrementWordsInMem();
}

unsigned int DataLoader::getMapping(std::string variableName){
    return this->dataMappings[variableName];
}


