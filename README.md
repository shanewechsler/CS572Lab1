# Author
Shane Wechsler
REDID: 823526399

# accumSim

## Dependencies: 

* `Simulator.h`
* `Simulator.cpp`
* `accumSim.cpp`

## Compilation:

makefile provided
run command `make` to compile all targets

## Running the code:
`./accumSim accumCode.s`

## How it works:

Based on 5 accumulator instuctions, and MIPS formatting.
LOAD X -> loads value at address `X` into accumulator.
STO Y -> stores accumulator's value into address `Y`.
ADD X -> adds value at address `X` to accumulator's value and stores into accumulator.
MUL X -> multiplies the value at address `X` by accumulator and stores into accumulator.
END -> signifies the end of code, stop reading instructions.

PARSING STEPS:
-> Opens code file
-> Reads code file line by line
    -> Split operands
    -> If `.data` or `.text` found, switch reading modes and continue.
    -> If in data mode, read first op as variable name and second op as value. Store mapping and store value in next address open in userData.
    -> If in text mode, read first op as instr and second op as variable name. Combine instr and operand address mapping and make binary machine code, store 64 bit instr in next open address in userText. 

EXECUTION STEPS:
-> Set PC to base address of userText
-> Set userMode to true to begin exection
    -> Read PC address
    -> Translate machine code from PC, seperate opcode and possible address mapping.
    -> Execute
-> User mode set to false when END instr found, complete.
-> Display result

# stackSim

* `Simulator.h`
* `Simulator.cpp`
* `stackSim.cpp`

## Compilation:

makefile provided
run command `make` to compile all targets

## Running the code:
`./stackSim stackCode.s`

## How it works:

Based on 5 accumulator instuctions, and MIPS formatting.
LOAD X -> loads value at address `X` into accumulator.
STO Y -> stores accumulator's value into address `Y`.
ADD X -> adds value at address `X` to accumulator's value and stores into accumulator.
MUL X -> multiplies the value at address `X` by accumulator and stores into accumulator.
END -> signifies the end of code, stop reading instructions.

PARSING STEPS:
-> Opens code file
-> Reads code file line by line
    -> Split operands
    -> If `.data` or `.text` found, switch reading modes and continue.
    -> If in data mode, read first op as variable name and second op as value. Store mapping and store value in next address open in userData.
    -> If in text mode, read first op as instr and second op as variable name. Combine instr and operand address mapping and make binary machine code, store 64 bit instr in next open address in userText. 

EXECUTION STEPS:
-> Set PC to base address of userText
-> Set userMode to true to begin exection
    -> Read PC address
    -> Translate machine code from PC, seperate opcode and possible address mapping.
    -> Execute
-> User mode set to false when END instr found, complete.
-> Display result
