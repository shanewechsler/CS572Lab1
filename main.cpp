#include "Simulator.h"
#include <iostream>

#define USER_DATA_BASE  0x10000000

int main(){
    Memory TEST = Memory(USER_DATA_BASE);

    TEST.WriteToAddress(0x1F, 0x10000000);
    TEST.WriteToAddress(0x2F, 0x10000004);
    TEST.WriteToAddress(0x3F, 0x10000008);
    TEST.WriteToAddress(0x4F, 0x1000000C);

    std::cout << TEST.ReadAddress(0x10000000) << std::endl;
    std::cout << TEST.ReadAddress(0x10000004) << std::endl;
    std::cout << TEST.ReadAddress(0x10000008) << std::endl;
    std::cout << TEST.ReadAddress(0x1000000C) << std::endl;
}