#ifndef WRITEBACK_H
#define WRITEBACK_H

using namespace std;

int total_clock_cycles = 0;

void writeback(string destReg, int value, bool isToReg){
    total_clock_cycles++;
    cout << "total_clock_cycles " + to_string(total_clock_cycles) << endl;
    if(destReg == "none") {
        cout << "pc is modified to 0x" << std::hex << pc << endl;
    }
    else {
        if(isToReg){

            registerfile[destReg] = value;
        }
        else{
            registerfile[destReg] = read_dmem(value);
        }
        cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl;
        cout << "pc is modified to 0x" << std::hex << pc << endl;
    }  
}

#endif