#ifndef MEM_H
#define MEM_H

int dmem []= { 0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0x5, 0x10, 0, 0 };

int read_dmem(int i) {
    if (i == 0) {
        return dmem[0];
    }
    return dmem[i/4];
}

void write_dmem(int i, int val) {
    if (i == 0) {
        dmem[0] = val;
    }
    else{
        dmem[i/4] = val;
    }
    //TODO: Check if index out of bounds
}

#endif