#include <stack>
#include <vector>
#include <iostream>
#include "Simulator.h"

Memory userText = Memory(USER_TEXT_BASE);
Memory userData = Memory(USER_DATA_BASE);

std::stack<int> userStack;

void PUSH(unsigned int address){
    userStack.push(userData.ReadAddress(address));
}

bool POP(unsigned int address){
    if(!userStack.empty()){
        int data = userStack.top();
        userStack.pop();
        userData.WriteToAddress(data, address);
        return true;
    }else{
        return false;
    }
}

bool ADD(){
    if(userStack.size() >= 2){
         int topFirst = userStack.top();
        userStack.pop();
        int topSecond = userStack.top();
        userStack.pop();
        int result = topFirst +topSecond;
        userStack.push(result);
        return true;
    }else{
        return false;
    }
}

bool MUL(){
    if(userStack.size() >= 2){
        int topFirst = userStack.top();
        userStack.pop();
        int topSecond = userStack.top();
        userStack.pop();
        int result = topFirst * topSecond;
        userStack.push(result);
        return true;
    }else{
        return false;
    }
}

int main(){
    DataLoader dataM = DataLoader();

    dataM.loadData(userData, "X", USER_DATA_BASE, 0x3);
    dataM.loadData(userData, "A", USER_DATA_BASE+4, 0x7);
    dataM.loadData(userData, "B", USER_DATA_BASE+8, 0x5);
    dataM.loadData(userData, "C", USER_DATA_BASE+12, 0x4);

    unsigned int X = dataM.getMapping("X");
    unsigned int A = dataM.getMapping("A");
    unsigned int B = dataM.getMapping("B");
    unsigned int C = dataM.getMapping("C");

    PUSH(X);
    PUSH(X);
    MUL();
    PUSH(A);
    MUL();
    PUSH(B);
    PUSH(X);
    MUL();
    ADD();
    PUSH(C);
    ADD();
    POP(USER_DATA_BASE+16);

    std::cout << userData.ReadAddress(USER_DATA_BASE+16) << std::endl;
}
