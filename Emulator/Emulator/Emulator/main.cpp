//
//  main.cpp
//  Emulator
//
//  Created by Rishin Amin on 12/04/2016.
//  Copyright © 2016 Rishin Amin. All rights reserved.
//
/*
 
 -------------------------ABOUT THE EMULATOR-------------------------
 
        - specification:
            - 256 Bytes of memory (128 blocks - 2 bytes per block)
            - 5 Registers - IR, ACC, PC, INPUT, OUTPUT
            - 3 System flags - halt, overflow, underflow
            - Von Neumann architechture
 
        - instruction set:
            - 10 instructions supported 
            - see 'customsystem.hpp' for descriptions of each instruction
            
        - Debugger mode:
            - To diable 'DEBUGGER' mode comment out '#define DEBUGGER' in 'customsystem.cpp'
 
 ----------------------------------------------------------------------
 
 */


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "customsystem.hpp"

using namespace std;

customsystem emulatedsystem;


void showhelp()
{
    cout << "----------------------HELP------------------------\n";
    cout << " Use the following commands to use this program...." << endl;
    cout << " - a Use Program 'a' at runtime (default)" << endl;
    cout << " - b Use Program 'b' at runtime" << endl;
    cout << " - c Use Program 'c' at runtime" << endl;
    cout << " - p Show description of the available programs" << endl;
    cout << " - r Runs the emulator using selected options then quits the program" << endl;
    cout << " - q Quit the program" << endl;
    cout << " - h Show this help menu" << endl << endl;
}

void showprogdescription(char selection)
{
    switch (selection)
    {
        case 'a':
            cout << "----------------------PROGRAM A------------------------\n" << endl;
            cout << "Program takes in an input and outputs the number 42 that number of times." << endl;
            cout << "-------------------------------------------------------\n" << endl;
            break;
            
        case 'b':
            cout << "----------------------PROGRAM B------------------------\n" << endl;
            cout << "Program takes in an input and outputs 1 if it is even and 0 if it is odd" << endl;
            cout << "-------------------------------------------------------\n" << endl;
            break;
            
        case 'c':
            cout << "----------------------PROGRAM C------------------------\n" << endl;
            cout << "Program takes in two numbers and multiplies them together" << endl;
            cout << "-------------------------------------------------------\n" << endl;
            break;
            
    }
}

int main()

{
    char menuSelect;
    char progSelect = 'a';
    char progSelectdescript;
    
    cout << "****************************************************\n";
    cout << "****************************************************\n";
    cout << "*********** Welcome to Rishin's Emulator! **********\n";
    cout << "****************************************************\n";
    cout << "****************************************************\n" << endl << endl;

    showhelp();

    while (1)
    {
        cin >> menuSelect;
        switch (menuSelect)
        {

            case 'a':
                progSelect = 'a';
                cout << "Program 'a' will be loaded to the system memory at runtime" << endl;
                break;
                
            case 'b':
                progSelect = 'b';
                cout << "Program 'b' will be loaded to the system memory at runtime" << endl;
                break;
                
            case 'c':
                progSelect = 'c';
                cout << "Program 'c' will be loaded to the system memory at runtime" << endl;
                break;
                
            case 'p':
                cout << "Which program would you like a description of?" << endl;
                cin >> progSelectdescript;
                showprogdescription(progSelectdescript);
                showhelp();
                break;
                
            case 'r':
                emulatedsystem.loadProgram(progSelect);
                emulatedsystem.run();
                return 0;
                break;
                
            case 'h':
                showhelp();
                break;
            case 'q':
                return 0;
                break;
                
            default:
                cout << menuSelect << " is not a valid option, please try again" << endl;
                break;
            
        }
    }
    
    return 0;
}

