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

PARSING:
Uses ascii encoded instructions to direct memory store and instruction handling.
`.data` signifies data mode, we read the next lines as variable names and values, and store them in user data.
`.text` signifies instruction mode, we read the next lines after as instructions, and use the variable names as mappings(second operands) and instruction codes as directives(first operands)

# stackSim

* `Simulator.h`
* `Simulator.cpp`
* `stackSim.cpp`

## Compilaion:

makefile provided
run command `make` to compile all targets

## Running the code:
`./stackSim stackCode.s`

## How it works:

Based on 5 accumulator instuctions, and MIPS formatting.
PUSH X -> push the value at address `X` to the stack.
POP Y -> pop the value at the top of the stack and store it to address `Y`
ADD -> pops the top 2 values of the stack, adds them, and then stores the result at the top of the stack.
MUL -> pops the top 2 vales of the stack, multiplies them, and then stores the result at the top of the stack.
END -> signifies the end of code, stop reading instructions.

PARSING:
Uses ascii encoded instructions to direct memory store and instruction handling.
`.data` signifies data mode, we read the next lines as variable names and values, and store them in user data.
`.text` signifies instruction mode, we read the next lines after as instructions, and use the variable names as mappings(second operands) and instruction codes as directives(first operands)
