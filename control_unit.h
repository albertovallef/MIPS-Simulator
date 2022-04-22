#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

using namespace std;


int RegWrite = 0, RegDst = 0, Branch = 0, ALUSrc = 0, InstType = 0, 
MemWrite = 0, MemtoReg = 0, MemRead = 0, Jump = 0, ALUop = 0;

int ALUControl(int ALUop, int funct);
void resetConstrolUnitSignals();

void resetConstrolUnitSignals() {
    RegWrite = 0;
    RegDst = 0;
    Branch = 0;
    ALUSrc = 0;
    InstType = 0; 
    MemWrite = 0;
    MemtoReg = 0;
    MemRead = 0;
    Jump = 0;
}

int controlUnit(int opcode, int funct) {
    resetConstrolUnitSignals();
    switch(opcode) {
        case 0x0:
        // R-Format
            RegDst = 1;
            RegWrite = 1;
            return ALUControl(2, funct);
        case 0x23:
        // lw operation
            ALUSrc = 1;
            MemtoReg = 1;
            RegWrite = 1;
            MemRead = 1;
            return ALUControl(0, funct);
        case 0x2b:
        // sw operation
            ALUSrc = 1;
            MemWrite = 1;
            ALUop = 0;
            return ALUControl(0, funct);
        case 0x4:
        // beq operation
            Branch = 1;
            return ALUControl(1, funct);
        default:
        // Error
            return 10000;
    }
}

int ALUControl(int ALUop, int funct) {
    if(ALUop == 0){
        // 0010 add
        return 2;
    }
    else if(ALUop == 1){
        // 0110 substract
        return 6; 
    }
    else if(ALUop == 2){
        if(funct == 0x20){
            // 0010 add
            return 2;
        }
        else if(funct == 0x22){
            // 0110 substract
            return 6;
        }
        else if(funct == 0x24){
            // 0000 AND
            return 0;
        }
        else if(funct == 0x25){
            // 0001 OR
            return 1;
        }
        else {
            // 0111 set on less than
            return 7;
        }
    }
    // Error
    return 10000;
}
#endif