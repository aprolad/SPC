# SPC8
8-bit processor with MISC architecture.

Instruction set:


Two most significant bits in instruction:

00 - ALU

01 - COPY register-to-register

10 - JMP if reg0 equal zero

11 - Load/Store from/to RAM


If ALU operation, next 2 bits is OPCODE, next 4 is CONST that added to the result of ALU

if COPY next 3 bits is source register, after that 3 bits of destination register

if JMP next 6 bits is adress to jump

if Load/Store next 1 bit is select Load or store, next 3 source or destination register, last 2 are unused


ALU OPCODES:

00 - ADD 

01 - SUB

10 - XOR

11 - NAND
