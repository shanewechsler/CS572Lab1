#include <stack>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include "Simulator.h"

using namespace std;

Memory userData = Memory(USER_DATA_BASE);
Memory userText = Memory(USER_TEXT_BASE);

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


int main(int argc, char **argv){
    DataLoader dataM = DataLoader();
    StackAssembler assem = StackAssembler();

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
            case PUSH_SIG:
                PUSH(address);
                break;
            case POP_SIG:
                POP(address);
                break;
            case ADD_SIG:
                ADD();
                break;
            case MUL_SIG:
                MUL();
                break;
            case END_SIG:
                userMode = false;
                break;
        }
    }
    cout << "Result: " << userData.ReadAddress(dataM.getMapping("D")) << endl;
}
