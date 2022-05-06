#ifndef FETCH_H
#define FETCH_H

extern int pc;
extern int next_pc;

#include "execute.h"
#include "writeback.h"

std::string fetch(std::string textFile) { 
    std::string instruction;
    fstream InstructionFile(textFile, ios::in);

    // Open file 
    if (InstructionFile.is_open())
    {
        int i = 0;
        // Case when BEQ is taken 
        if(alu_zero) {
            pc = pc + jump_next;
            // Print but do not update register file or mem
            writeback("none", 0); 
        }
        // Case when JR isntruction
        else if(jump_jr) {
            pc = registerfile["$ra"]; // pc uses the value in $ra (from JAL)
            jump_jr = false;
            // Print but do not update register file or mem
            writeback("none", 0);
        }
        // Case when J instruction
        else if(jump_target != 0) {
            pc = jump_target; // pc uses the value in the address (from binary instruction)
            jump_target = 0;
            // Print but do not update register file or mem
            writeback("none", 0);
        }

        // Iterate over the lines in the file (Normal case or cycle)
        while ( InstructionFile.good() )
        {
            // Get the current PC instruction
            getline(InstructionFile, instruction);
            if (pc == 0){
                pc += 4;
                return instruction;
            }
            // Divide over 4 to get the current integer instruction
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

