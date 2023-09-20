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
        return LOAD_SIG;
    }else if(strcmp(accumInst, "sto") == 0){
        return STO_SIG;
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

        char *newToken = strtok(instr_c, delimiters); //splits the new line into operands
        char *instr;
        char *operand;

        int i = 0;
        while(newToken != nullptr && i < 2){
            operands[i] = newToken;
            newToken = strtok(NULL, delimiters);
            i++;
        }
        
        switch(i){
            case 0: //nothing in the line, read the next line
                continue;
            case 1: //only one "operand" found must be .data or .text
                if(strcmp(operands[0], "data") == 0){
                    dataMode = true;
                    continue;
                }else{
                    dataMode = false;
                    continue;
                }
            case 2:
                instr = operands[0]; //instruction comes before operand
                operand = operands[1];
        }

        if(dataMode){
            dataM.storeData(userData, instr, atoi(operand)); //uses "instr" as the variable name, and the operand as the immediate value
        }else{
            unsigned int address = dataM.getMapping(operand);
            switch(InstructionMode(instr)){
                case LOAD_SIG:
                    LOAD(address);
                    break;
                case STO_SIG:
                    STO(address);
                    break;
                case ADD_SIG:
                    ADD(address);
                    break;
                case MUL_SIG:
                    MUL(address);
                    break;
                case END_SIG:
                    break;
            }
        }

    }

    cout << "Result: " << userData.ReadAddress(dataM.getMapping("D")) << endl;
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