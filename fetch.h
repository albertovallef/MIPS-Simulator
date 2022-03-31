#ifndef FETCH_H
#define FETCH_H


// Global variables
int pc = 0;
int next_pc =  pc + 4;

#include "execute.h"
#include "writeback.h"

std::string fetch(std::string textFile) { 
    std::string instruction;
    fstream InstructionFile(textFile, ios::in);

    // Open file 
    if (InstructionFile.is_open())
    {
        int i = 0;
        if(alu_zero) {
            pc = pc + jump_next;
            writeback("none", 0, false); 
        }
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

