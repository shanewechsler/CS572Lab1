#include <stack>
#include <vector>
#include <iostream>
#include "Simulator.h"

#define USER_TEXT_BASE  0x00400000
#define USER_DATA_BASE  0x01000000

Memory userText = Memory(USER_TEXT_BASE);
Memory userData = Memory(USER_DATA_BASE);

std::stack<unsigned int> userStack;

void PUSH(unsigned int address){
    userStack.push(userData.ReadAddress(address));
}

bool POP(unsigned int address){
    if(!userStack.empty()){
        unsigned int data = userStack.top();
        userStack.pop();
        userData.WriteToAddress(data, address);
        return true;
    }else{
        return false;
    }
}

bool ADD(){
    if(userStack.size() >= 2){
        unsigned int topFirst = userStack.top();
        userStack.pop();
        unsigned int topSecond = userStack.top();
        userStack.pop();
        unsigned int result = topFirst +topSecond;
        userStack.push(result);
        return true;
    }else{
        return false;
    }
}

bool MUL(){
    if(userStack.size() >= 2){
        unsigned int topFirst = userStack.top();
        userStack.pop();
        unsigned int topSecond = userStack.top();
        userStack.pop();
        unsigned int result = topFirst * topSecond;
        userStack.push(result);
        return true;
    }else{
        return false;
    }
}

int main(){
    userData.WriteToAddress(0x3, USER_DATA_BASE);
    userData.WriteToAddress(0x7, USER_DATA_BASE+4);
    userData.WriteToAddress(0x5, USER_DATA_BASE+8);
    userData.WriteToAddress(0x4, USER_DATA_BASE+12);

    PUSH(USER_DATA_BASE);
    PUSH(USER_DATA_BASE+4);
    PUSH(USER_DATA_BASE+8);
    PUSH(USER_DATA_BASE+12);

    ADD();
    MUL();

    POP(USER_DATA_BASE+16);
    POP(USER_DATA_BASE+20);

    std::cout << userData.ReadAddress(USER_DATA_BASE+16) << std::endl;
    std::cout << userData.ReadAddress(USER_DATA_BASE+20) << std::endl;
}
