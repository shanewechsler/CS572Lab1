#include "Simulator.h"
#include <iostream>

Memory userText = Memory(USER_TEXT_BASE);
Memory userData = Memory(USER_DATA_BASE);

int accumulator;

void LOAD(unsigned int address){
    accumulator = userData.ReadAddress(address);
}

void STO(unsigned int address){
    userData.WriteToAddress(accumulator, address);
}

void ADD(unsigned int address){
    accumulator += userData.ReadAddress(address);
}

void MUL(unsigned int address){
    accumulator *= userData.ReadAddress(address);
}

int main(){
    DataLoader dataM = DataLoader();

    dataM.loadData(userData, "X", USER_DATA_BASE, 0x3);
    dataM.loadData(userData, "A", USER_DATA_BASE+4, 0x7);
    dataM.loadData(userData, "B", USER_DATA_BASE+8, 0x5);
    dataM.loadData(userData, "C", USER_DATA_BASE+12, 0x4);
    dataM.loadData(userData, "D", USER_DATA_BASE+16, 0x0);

    unsigned int X = dataM.getMapping("X");
    unsigned int A = dataM.getMapping("A");
    unsigned int B = dataM.getMapping("B");
    unsigned int C = dataM.getMapping("C");
    unsigned int D = dataM.getMapping("D");

    LOAD(X);
    MUL(X);
    MUL(A);
    STO(D);
    LOAD(B);
    MUL(X);
    ADD(C);
    ADD(D);
    STO(D);

    std::cout << userData.ReadAddress(D) << std::endl;

}