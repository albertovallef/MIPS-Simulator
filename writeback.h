#ifndef WRITEBACK_H
#define WRITEBACK_H

using namespace std;

int total_clock_cycles = 0;

void writeback(string destReg, int alu_result, bool memtoReg, bool memWrite){
    total_clock_cycles++;
    cout << "total_clock_cycles " + to_string(total_clock_cycles) << endl;
    if(destReg == "none") {
        cout << "pc is modified to 0x" << std::hex << pc << endl;
    }
    else {
        if(memtoReg){
            registerfile[destReg] = alu_result;
            cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl;
        }
        else{
            if(memWrite) {
                write_dmem(alu_result, registerfile[destReg]);
                cout << "memory 0x" << std::hex << alu_result << " is modified to 0x" << std::hex << registerfile[destReg] << endl; 
            }
            else {
               registerfile[destReg] = read_dmem(alu_result);
               cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl; 
            }
        }
        cout << "pc is modified to 0x" << std::hex << pc << endl;
    }  
}

#endif