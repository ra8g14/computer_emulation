//
//  customsystem.hpp
//  Emulator
//
//  Created by Rishin Amin on 13/04/2016.
//  Copyright © 2016 Rishin Amin. All rights reserved.
//

#ifndef customsystem_hpp
#define customsystem_hpp

#define MEMORY 128 // 128 blocks of memory, each block is 2 bytes long


//-------- OPCODE DEFINITIONS ---------

#define HLT 0x0011     // End the program by setting the halt flag high
#define ADD 0x1000     // Add contents of mem[operand] to contents of accumulator
#define SUB 0x2000     // Sub contents of mem[operand] from contents of accumulator
#define STA 0x3000     // Store contents of accumulator in mem[operand]
#define LDA 0x4000     // Load contents of mem[operand] to the accumulator
#define BRA 0x5000     // Set the Program counter to operand
#define BRZ 0x6000     // If contents of accumulator = 0 and overflow/ underflow flags are 0, set program counter to operand
#define BRP 0x7000     // If the underflow flag is zero or the contents of the accumulator = 0, set the program counter to operand
#define INP 0x8000     // Set the contents of the accumulator to the contents of the user input register
#define OUT 0x9000     // Output contents of the accumulator to the console

//-------------------------------------



#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

class customsystem
{
public:
    
    customsystem();
    ~customsystem();
    
    /* Instructions are broken down in the following way... */
    /*
        15             12 11                                  0
        |----OpCode-----| |---------------Operand-------------|
    */
    
    struct instruction
    {
        unsigned opcode:4;
        unsigned operand:12;
    } instruct;
    
    
    void debugger();
    void fetch();
    void decode_execute();
    void loadProgram(char program);
    void run();


private:
    
    char yesorno; // for user input when in 'DEBUGGER' mode
    
    struct flag
    {
        bool overflow;      // goes high when overflow is detected
        bool underflow;     // goes high when underflow has been detected
        bool halt;          // goes high when the program has reached its end
    } flags;

    
    uint16_t PC;     // program counter
    uint16_t ACC;    // Accumulator register
    uint16_t IR;     // instruction register
    uint16_t INPUT;  // stores values from a user input
    uint16_t OUTPUT; // stores values from system output
    uint16_t mem[MEMORY];    // 64 bytes of memory
    
    void showregistersandflags();   // used in debug mode to show contents of all registers and status of flags
    void showmemory();  // used in debug mode to show contents of all memory locaitons
    void initialise();  // initialise the system by setting all values to defaults
    
};

#endif /* customsystem_hpp */
