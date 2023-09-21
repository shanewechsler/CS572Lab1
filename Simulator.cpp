#include "Simulator.h"
#include <cstring>
#include <iostream>



void Memory::incrementWordsInMem(){
    this->wordsInMemory++;
}

int Memory::getWordsInMem(){
    return this->wordsInMemory;
}

unsigned int Memory::getBaseAddress(){
    return this->baseAddress;
}

long Memory::ReadAddress(unsigned int address){
    unsigned int index = ConvertAddressToIndex(address);
    return this->memoryEntries[index];
}

void Memory::WriteToAddress(long word, unsigned int address){ //just longs and not ulongs becase I wanted to be able to store negative values in data
    unsigned int index = ConvertAddressToIndex(address);
    this->memoryEntries[index] = word;
}

unsigned int Memory::ConvertAddressToIndex(unsigned int address){
    return (address - this->baseAddress) >> 2; //32 bit addresses are in bytes, but we're storing words so divide by 4
}

unsigned int Memory::ConvertIndexToAddress(unsigned int index){
    return (index + this->baseAddress) << 2;
}

void DataLoader::storeText(Memory &data, unsigned long machineCode){ //storeText and storeData use pass by reference to *actually* store data/instructions
    unsigned int address = data.getBaseAddress() + (data.getWordsInMem() * 4); //should be the address of the next open slot in memory
    data.WriteToAddress(machineCode, address);
    data.incrementWordsInMem();
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

unsigned int Assembler::instrCode(char *instr){
    return this->opcodes[instr]; //returns corresponding mapping, 32 bit address
}

unsigned long Assembler::assembleCode(char *instr){
    return ulong(this->instrCode(instr)) << OPERAND_LENGTH; //for opcodes that don't have an operands
}

unsigned long Assembler::assembleCode(DataLoader mapper, char *instr, std::string variableName){
    unsigned int address = mapper.getMapping(variableName);
    unsigned int opcode = this->instrCode(instr);
    unsigned long assemCode = ulong(opcode) << OPERAND_LENGTH; //puts the opcode infront of the operand, need a long because operands are 32 bits. 
    assemCode += address; //add the address to fill the last 32 bits
    return assemCode;
}

unsigned int Assembler::machineToOp(unsigned long machineCode){
    return (0xFF00000000 & machineCode) >> OPERAND_LENGTH;
}

unsigned int Assembler::machineToAddress(unsigned long machineCode){
    return uint(0x00FFFFFFFF & machineCode);
}


void StackAssembler::initMap(){
    this->opcodes["push"] = 0x0;
    this->opcodes["pop"] = 0x1;
    this->opcodes["add"] = 0x2;
    this->opcodes["mul"] = 0x3;
    this->opcodes["end"] = 0x4;
}

void AccumAssembler::initMap(){
    this->opcodes["load"] = 0x0;
    this->opcodes["sto"] = 0x1;
    this->opcodes["add"] = 0x2;
    this->opcodes["mul"] = 0x3;
    this->opcodes["end"] = 0x4;
}
