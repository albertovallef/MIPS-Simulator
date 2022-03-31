#ifndef FETCH_H
#define FETCH_H

#include <iostream>
#include <fstream>
#include <string>

// Global variables
int pc = 0;
int next_pc =  pc + 4;

std::string fetch(std::string textFile) { 
    std::string instruction;
    fstream InstructionFile(textFile, ios::in);

    // Open file 
    if (InstructionFile.is_open())
    {
        int i = 0;
        // Iterate over the lines in the file
        while ( InstructionFile.good() )
        {
            // Get the current PC instruction
            getline(InstructionFile, instruction);
            if (pc == 0){
                pc += 4;
                return instruction;
            }
            else if(pc/4 == i){
                pc += 4;
                return instruction;
            }
            i++;
        }
        // Close the file
        InstructionFile.close();
    }
    return "Failed to open file";
}

#endif

