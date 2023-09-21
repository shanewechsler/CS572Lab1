#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

Memory userData = Memory(USER_DATA_BASE);
Memory userText = Memory(USER_TEXT_BASE);

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

int main(int argc, char **argv){
    DataLoader dataM = DataLoader();
    AccumAssembler assem = AccumAssembler();

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
            case 1: //only one "operand" found check if it's .data or .text, if not store no operand instr in userText
                if(strcmp(operands[INSTR_IDX], "data") == 0){
                    dataMode = true;
                    continue;
                }else if(strcmp(operands[INSTR_IDX], "text") == 0){
                    dataMode = false;
                    continue;
                }else{
                    dataM.storeText(userText, assem.assembleCode(operands[INSTR_IDX]));
                    continue;
                }
            case 2:
                instr = operands[INSTR_IDX]; //instruction comes before operand
                operand = operands[OPERAND_IDX];
        }


        if(dataMode){
            dataM.storeData(userData, instr, atoi(operand)); //uses "instr" as the variable name, and the operand as the immediate value
        }else{
            dataM.storeText(userText, assem.assembleCode(dataM, instr, operand)); //create machine code for instr and store in in userText
        }
    }

    unsigned int PC = USER_TEXT_BASE;
    bool userMode = true;
    while(userMode){
        unsigned long machineInstr = userText.ReadAddress(PC);
        PC += 4;
        unsigned int opcode = assem.machineToOp(machineInstr);
        unsigned int address = assem.machineToAddress(machineInstr);
        switch(opcode){
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
                userMode = false;
                break;
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