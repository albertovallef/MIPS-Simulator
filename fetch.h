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
        if(alu_zero) {
            pc = pc + jump_next;
            writeback("none", 0); 
        }
        else if(jump_jr) {
            pc = registerfile["$ra"];
            jump_jr = false;
            writeback("none", 0);
        }
        else if(jump_target != 0) {
            pc = jump_target;
            jump_target = 0;
            writeback("none", 0);
        }
        // else if(jump_target != 0) {
        //     pc = jump_target;
        //     cout << pc << endl;
        //     jump_target = 0;
        //     exit(3);
        // }
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

