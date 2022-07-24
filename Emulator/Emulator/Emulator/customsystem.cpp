//
//  customsystem.cpp
//  Emulator
//
//  Created by Rishin Amin on 13/04/2016.
//  Copyright © 2016 Rishin Amin. All rights reserved.
//

// LOG FUNCTION - prints time and status of all registers whenever called

#include "customsystem.hpp"
#include <fstream>
#include <string>

#define DEBUGGER // comment this out to disable 'DEBUGGER' mode

using namespace std;

customsystem::customsystem()
{
    
}

customsystem::~customsystem()
{
    
}

void customsystem::initialise()
{
    
    PC = 0;         // Reset Program Counter
    IR = 0;         // clear instruction register
    ACC = 0;        // clear accumulator
    INPUT = 0;      // clear user input register
    
    // reset the flags
    flags.halt = 0;
    flags.overflow = 0;
    flags.underflow = 0;
    
    
    // clear memory
    for(int i =0; i <  MEMORY; ++i)
        mem[i] = 0;
    
    // reset curent instruction
    instruct.opcode = 0;
    instruct.operand = 0;
}

void customsystem::showregistersandflags()
{
    bool valid = 0; // checks if input for 'DEBUGGER' mode are valid

    while (!valid)
    {
        cout << "DEBUGGER: Would you like to reveal contents of all the registers and status of flags? y/n" << endl;
        cin >> yesorno;
        cout  << endl;
        if (yesorno == 'y' || yesorno == 'Y')
        {
            valid = 1;
            cout << "---------------------------------------" << endl;
            cout << "DEBUGGER: -----------REGISTERS---------" << endl;
            cout << "DEBUGGER: PC: 0x" << PC << endl;
            cout << "DEBUGGER: IR: 0x" << IR << endl;
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            cout << "DEBUGGER: INPUT: 0x" << INPUT << endl;
            cout << "DEBUGGER: OUTPUT: 0x"<< OUTPUT << endl;
            
            cout << "DEBUGGER: -----------FLAGS-------------" << endl;
            cout << "DEBUGGER: Overlflow: " << flags.overflow<< endl;
            cout << "DEBUGGER: Underflow: " << flags.underflow << endl;
            cout << "DEBUGGER: Halt: " << flags.halt << endl;
            cout << "---------------------------------------" << endl << endl;

        }
        else
        {
            if (yesorno == 'n' || yesorno == 'N')
                valid = 1;
            else
                cout << "Invalid response, please try again" << endl;
        }
    }
}

void customsystem::showmemory()
{
    bool valid = 0; // checks if input for 'DEBUGGER' mode are valid
    
    while (!valid)
    {
        cout << "DEBUGGER: Would you like to reveal contents of all memory locations y/n" << endl;
        cin >> yesorno;
        cout  << endl;
        if (yesorno == 'y' || yesorno == 'Y')
        {
            valid = 1;
            cout << "---------------------------------------" << endl;
            cout << "DEBUGGER: -----------MEMORY------------" << endl;
            for (int i = 0; i < MEMORY; i++)
                cout << "DEBUGGER: Memory location 0x" << i << ": " << std::hex << "0x" << mem[i] << endl;
            cout << "---------------------------------------" << endl << endl;
            
        }
        else
        {
            if (yesorno == 'n' || yesorno == 'N')
                valid = 1;
            else
                cout << "Invalid response, please try again" << endl;
        }
    }

}

void customsystem::fetch()  // 'Fetches' the instructions stored in the system memory and increments the program counter to point to the next instruction
{
    #ifdef DEBUGGER
    cout << "\n------------------------------------------------------------------" << endl;
    cout << "DEBUGGER: Fetching instruction..." << endl;
    cout << "DEBUGGER: PC: 0x" << std::hex << PC << endl;
    #endif

    IR = mem[PC];   // Loads the instruction to the instruction register
    PC ++;  // Increments the Program counter
    
    #ifdef DEBUGGER
    cout << "DEBUGGER: Instruction fetched! IR: 0x" << std::hex << IR << endl;
    cout << "DEBUGGER: PC incremented to: 0x" << PC << endl << endl;
    cout << "Press enter to continue" << endl;
    cin.ignore();
    cin.ignore();
    #endif
    
    
    
}

void customsystem::decode_execute() // 'Decodes' the instruction in the instruction register and executes it
{
    #ifdef DEBUGGER
    cout << "DEBUGGER: Decoding instuction..." << endl;
    #endif

    instruct.opcode = ((IR & 0xF000) >> 12);
    instruct.operand = IR & 0x0FFF;
    
    #ifdef DEBUGGER
    cout << "DEBUGGER: Opcode: 0x" << instruct.opcode << endl;
    cout << "DEBUGGER: Operand: 0x" << std::hex << instruct.operand << endl << endl;
    #endif
    
    switch(instruct.opcode)
    {
        case 0x0:   //HLT
            // end the program by setting the halt flag high
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'HLT' - Program end" << endl;
            #endif
 
            flags.halt = 1;
            #ifdef DEBUGGER
            cout << "DEBUGGER: halt flag set high\n" << endl;
            showregistersandflags();
            #endif
            break;
            
        case 0x1:   // ADD
            // Add contents of mem[operand] to contents of accumulator
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'ADD' " << endl;
            cout << "DEBUGGER: Adding 0x" << ACC << " to: 0x" << mem[instruct.operand] << endl;
            #endif
 
            ACC = ACC + mem[instruct.operand];
            
            #ifdef DEBUGGER
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif

            // Check for overflow
            if(ACC + mem[instruct.operand] > 255)
            {
                flags.overflow = 1;
                #ifdef DEBUGGER
                cout << "DEBUGGER: Overflow Detected! - flag set high" << endl;
                #endif
            }
            else
                flags.overflow = 0;
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
        
        case 0x2:   // SUB
            // Sub contents of mem[operand] from contents of accumulator
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'SUB' " << endl;
            cout << "DEBUGGER: Subtracting: 0x" << mem[instruct.operand] << " from: 0x" << ACC << endl;
            #endif
            
            // update status of underflow flag
            if(ACC - mem[instruct.operand] < 0)
            {
                flags.underflow = 1;
                #ifdef DEBUGGER
                cout << "DEBUGGER: Underrflow Detected! - flag set high" << endl;
                #endif
            }
            else
                flags.underflow = 0;
            ACC = ACC - mem[instruct.operand];
            
            #ifdef DEBUGGER
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
            

            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
        
        case 0x3:   // STA
            // Store contents of accumulator in mem[operand]
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'STA' " << endl;
            cout << "DEBUGGER: Storing: 0x" << ACC << " to memory location: 0x" << instruct.operand << endl;
            #endif
            
            mem[instruct.operand] = ACC;
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
        
        case 0x4:    // LDA
            // Load contents of mem[operand] to the accumulator
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'LDA' " << endl;
            cout << "DEBUGGER: Loading: 0x" << mem[instruct.operand] << " to ACC " << endl;
            #endif
            
            ACC = mem[instruct.operand];
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
            
        case 0x5:   // BRA (Unconditional Branch)
            // Set the Program counter to the operand
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'BRA' " << endl;
            cout << "DEBUGGER: Setting PC from: 0x" << PC << " to: 0x" << instruct.operand <<  endl;
            #endif
            
            PC = instruct.operand;
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
            
        case 0x6:   // BRZ (Branch if equal to Zero)
            // If contents of accumulator = 0 and overflow/ underflow flags are 0, set program counter to operand
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'BRZ' " << endl;
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
            
            if ((ACC == 0) && (!flags.underflow) && (!flags.overflow))
            {
                #ifdef DEBUGGER
                cout << "DEBUGGER: Coniditon met - ACC = 0 " << endl;
                cout << "DEBUGGER: Setting PC from: 0x" << PC << " to: 0x" << instruct.operand <<  endl;
                #endif
                PC = instruct.operand;
            }
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
            
        case 0x7:    // BRP (Branch if positive)
            // If the underflow flag is zero or the contents of the accumulator = 0, set the program counter to operand
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'BRP' " << endl;
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
            
            if (!flags.underflow || (ACC==0))
            {
                #ifdef DEBUGGER
                cout << "DEBUGGER: Condition met - ACC > 0 (underflow flag is inactive)" << endl;
                cout << "DEBUGGER: Setting PC from: 0x" << PC << " to: 0x" << instruct.operand << endl;
                #endif
                PC = instruct.operand;
                
            }
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
        
        case 0x8:   // INP
            // Set the contents of the accumulator to the contents of the user input register
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'INP' " << endl;
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
            
            INPUT = 256;
            while (INPUT > 255)
            {
                cout << "Input requested please input data in decimal (max 255)..." << endl; // Emulation is console based so input must be provided in this way
                cin >> INPUT;
                if ((INPUT > 255) | !(cin))
                {
                    cout << "Invalid input, please try again" << endl;
                }
            }
            
            #ifdef DEBUGGER
            cout << "DEBUGGER: Loading: " << INPUT << " to ACC..." << endl;
            #endif
            
            ACC = INPUT;
            
            #ifdef DEBUGGER
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
        
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
        
        case 0x9:   // OUT
            // Load contents of the accumulator to the output register
            #ifdef DEBUGGER
            cout << "DEBUGGER: Executing 'OUT' " << endl;
            cout << "DEBUGGER: ACC: 0x" << ACC << endl;
            #endif
            
            OUTPUT = ACC;
            cout << std::dec << "OUTPUT: " << OUTPUT << std::hex << endl;
            
            #ifdef DEBUGGER
            cout << "DEBUGGER: Loading ACC to OUTPUT..." << endl;
            cout << "DEBUGGER: OUT: 0x" << ACC << endl;
            #endif
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
            
        default:
            cout << "Illegal Op-Code: 0x" << instruct.opcode << " Found at Instruction: 0x" << PC << endl << " Ending Program" << endl;
            mem[PC++] = HLT; // next instruction is overridden as a halt
            
            #ifdef DEBUGGER
            showregistersandflags();
            showmemory();
            #endif
            break;
    }

}


void customsystem::loadProgram(char program)    // loads predefined prgrams into memory
{
    initialise();
    cout << " loading program: " << program << " to memory..." << endl;
    switch (program)
    {
        case 'a': // program takes in user input then outputs the number 42 that number of times
            
            mem[0] = INP;       //takes in user input
            mem[1] = STA | 10;  // store the result in address 10
            mem[2] = LDA | 10;  // load contents of address 10
            mem[3] = BRZ | 9;   // if acc = 0 end the program
            mem[4] = SUB | 11;  // subtract 1 from acc
            mem[5] = STA | 10;  // store result in address 10
            mem[6] = LDA | 12;  // load the number 42 to acc
            mem[7] = OUT;       // output the number 42
            mem[8] = BRA | 2;   // go to instruction 2 (repeat the process)
            mem[9] = HLT;       // end the program
            mem[10] = 0;
            mem[11] = 1;
            mem[12] = 42;
            
            break;
            
        case 'b': // program takes in user input and outputs one if the number is even and 0 if its odd
            
            mem[0] = INP;
            mem[1] = STA | 16;
            mem[2] = LDA | 16;
            mem[3] = SUB | 15;
            mem[4] = BRZ | 10;
            mem[5] = STA | 16;
            mem[6] = BRP | 2;
            mem[7] = LDA | 13;
            mem[8] = OUT;
            mem[9] = BRA | 12;
            mem[10] = LDA | 14;
            mem[11] = OUT;
            mem[12] = HLT;
            mem[13] = 0;
            mem[14] = 1;
            mem[15] = 2;
            mem[16] = 0; // input
            
            break;
            
        case 'c': // program takes in two numbers and adds them together
            
            mem[0] = INP;
            mem[1] = STA | 6;
            mem[2] = INP;
            mem[3] = ADD | 6;
            mem[4] = OUT;
            mem[5] = HLT;
            mem[6] = 0;
            
            break;
            
    }

    
}

void customsystem::run()    // run the emulator
{
    #ifdef DEBUGGER
    cout << "Running the program in 'DEBUGGER' mode" << endl;
    #endif
    //initialise();
    
    //showmemory();
    // Begin emulation cycle...
    while(!flags.halt)
    {
        fetch();
        decode_execute();
    }
    
}
