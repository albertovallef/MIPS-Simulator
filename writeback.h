#ifndef WRITEBACK_H
#define WRITEBACK_H

using namespace std;

int total_clock_cycles = 0;

void writeback(string destReg, int alu_result){
    total_clock_cycles++;
    cout << "total_clock_cycles " + to_string(total_clock_cycles) << endl;

    // R-type
    if(RegDst && RegWrite){ 
        registerfile[destReg] = alu_result;
        cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl;
    }
    else if(ALUSrc && !Branch) { // I-type (sw or lw)
        if(MemWrite){ // (sw)
            write_dmem(alu_result, registerfile[destReg]);
            cout << "memory 0x" << std::hex << alu_result << " is modified to 0x" << std::hex << registerfile[destReg] << endl;
        }
        else if(MemRead) { // (lw)
            registerfile[destReg] = read_dmem(alu_result);
            cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl;
        }
    }
    else {
        if(Jump && destReg != "none") {
            registerfile["$ra"] = alu_result;
            cout << destReg + " is modified to 0x" << std::hex << registerfile[destReg] << endl;
        }
    }
    cout << "pc is modified to 0x" << std::hex << pc << endl;  
}

#endif