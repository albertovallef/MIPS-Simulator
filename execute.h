#ifndef EXECUTE_H
#define EXECUTE_H

#include "mem.h"

bool alu_zero = false;
int branch_target = 0;

int execute(int readData1, int readData2, int alu_op) {
    alu_zero = false;
    switch(alu_op) {
    case 0:
        break;
    case 1:
        // 0001 do OR
        break;
    case 2:
        // 0010 do add
        return readData1 + readData2;
    case 5:
        // 0110 do substract
        // cout << "HERE!!!" << endl;
        // cout << readData1 - readData2 << endl;
        if(readData1 - readData2 == 0) {
            alu_zero = true;
        }
        return readData1 - readData2;
    case 6:
        // 0111 do set-on-less-than
        if (readData1 < readData2){
            return 1;
        }
        return 0;
    default:
        // 1100 do NOR
        break;
    }
    return 0;
}

#endif