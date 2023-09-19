#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

Memory userData = Memory(USER_DATA_BASE);

int accumulator;

using namespace std;

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

unsigned int InstructionMode(char *accumInst){
    if(strcmp(accumInst,"load") == 0){
        return 0;
    }else if(strcmp(accumInst, "sto") == 0){
        return 1;
    }else if(strcmp(accumInst, "add") == 0){
        return 2;
    }else if(strcmp(accumInst, "mul") == 0){
        return 3;
    }else{
        return 4;
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
                }else{
                    dataMode = false;
                    continue;
                }
            case 2:
                instr = operands[0];
                operand = operands[1];
        }

        if(dataMode){
            dataM.storeData(userData, instr, atoi(operand));
        }else{
            unsigned int address = dataM.getMapping(operand);
            switch(InstructionMode(instr)){
                case 0:
                    LOAD(address);
                    break;
                case 1:
                    STO(address);
                    break;
                case 2:
                    ADD(address);
                    break;
                case 3:
                    MUL(address);
                    break;
                case 4:
                    break;
            }
        }
    }

    cout << accumulator << endl;
    //LOAD(X);
    // MUL(X);
    // MUL(A);
    // STO(D);
    // LOAD(B);
    // MUL(X);
    // ADD(C);
    // ADD(D);
    // STO(D);

}