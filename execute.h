#ifndef EXECUTE_H
#define EXECUTE_H

#include "mem.h"

bool alu_zero = false;
int branch_target = 0;

int execute(int readData1, int readData2, int alu_op) {
    alu_zero = false;
    switch(alu_op) {
    case 0:
        // 0000 do AND
        return (readData1 & readData2);
    case 1:
        // 0001 do OR
        return (readData1 | readData2);
    case 2:
        // 0010 do add
        return (readData1 + readData2);
    case 5:
        if(readData1 - readData2 == 0) {
            alu_zero = true;
        }
        return (readData1 - readData2);
    case 6:
        // 0111 do set-on-less-than
        if (readData1 < readData2){
            return 1;
        }
        return 0;
    case 12:
        // 1100 do NOR
        return (~(readData1 | readData2));
    default:
        return 0;
    }
    return 0;
}

#endif