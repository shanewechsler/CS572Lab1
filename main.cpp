#include "Simulator.h"
#include <iostream>


int main(){
    Memory TEST = Memory(USER_DATA_BASE);

    DataLoader dataMem = DataLoader();

    dataMem.loadData(TEST,"X", USER_DATA_BASE, 0x3);
    dataMem.loadData(TEST,"A", USER_DATA_BASE+4, 0x7);
    dataMem.loadData(TEST, "B", USER_DATA_BASE+8, 0x5);
    dataMem.loadData(TEST, "C", USER_DATA_BASE+12, 0x4);

    std::cout << dataMem.getMapping("X") << std::endl;
    std::cout << TEST.ReadAddress(USER_DATA_BASE) << std::endl;
    std::cout << TEST.ReadAddress(dataMem.getMapping("A")) << std::endl;
    std::cout << TEST.ReadAddress(dataMem.getMapping("B")) << std::endl;
    std::cout << TEST.ReadAddress(dataMem.getMapping("C")) << std::endl;
}