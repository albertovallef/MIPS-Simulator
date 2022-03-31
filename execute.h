#ifndef EXECUTE_H
#define EXECUTE_H

#include <iostream>
#include <fstream>
#include <string>
#include "mem.h"

int alu_zero = 0;
int branch_target = 0;

int execute(int readData1, int readData2, int alu_op) {
    switch(alu_op) {
    case 0:
        break;
    case 1:
        // 0001 do OR
        break;
    case 2:
        // 0010 do add
        return read_dmem(readData1 + readData2);
    case 5:
        // 0110 do substract
        break;
    case 6:
        // 0111 do set-on-less-than
        break;
    default:
        // 1100 do NOR
        break;
    }
    return 0;
}

#endif