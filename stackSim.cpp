#include <stack>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include "Simulator.h"

using namespace std;

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

unsigned int InstructionMode(char *accumInst){
    if(strcmp(accumInst,"push") == 0){
        return PUSH_SIG;
    }else if(strcmp(accumInst, "pop") == 0){
        return POP_SIG;
    }else if(strcmp(accumInst, "add") == 0){
        return ADD_SIG;
    }else if(strcmp(accumInst, "mul") == 0){
        return MUL_SIG;
    }else{
        return END_SIG;
    }
}

int main(int argc, char **argv){
    DataLoader dataM = DataLoader();

    bool dataMode = false;

    ifstream codeFile(argv[1]);

    string instruction;

    const char *delimiters = " \t\r\n\v\f ./:";

    while(getline(codeFile, instruction)){
        char instr_c[instruction.length()];
        char *operands[2];

        /*converts ctring line into c string */
        strcpy(instr_c, instruction.c_str());

        char *newToken = strtok(instr_c, delimiters);
        char *instr;
        char *operand;

        int i = 0;
        while(newToken != nullptr && i < 2){
            operands[i] = newToken;
            newToken = strtok(NULL, delimiters);
            i++;
        }
        
        switch(i){
            case 0:
                continue;
            case 1:
                if(strcmp(operands[0], "data") == 0){
                    dataMode = true;
                    continue;
                }else if(strcmp(operands[0], "text") == 0){
                    dataMode = false;
                    continue;
                }else{
                    instr = operands[1];
                }
            case 2:
                instr = operands[0];
                operand = operands[1];
        }

        if(dataMode){
            dataM.storeData(userData, instr, atoi(operand));
        }else{
            unsigned int address;
            switch(InstructionMode(instr)){
                case PUSH_SIG:
                    address = dataM.getMapping(operand);
                    PUSH(address);
                    break;
                case POP_SIG:
                    address = dataM.getMapping(operand);
                    POP(address);
                    break;
                case ADD_SIG:
                    ADD();
                    break;
                case MUL_SIG:
                    MUL();
                    break;
                case END_SIG:
                    break;
            }
        }
    }
    cout << "Result: " << userData.ReadAddress(dataM.getMapping("D")) << endl;
}
