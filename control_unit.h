#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

using namespace std;

bool RegWrite = false, RegDst = false, Branch = false, ALUSrc = false, InstType = false, 
MemWrite = false, MemtoReg = false, MemRead = false, Jump = false;

int ALUControl(int ALUop, int funct);
void resetConstrolUnitSignals();

void resetConstrolUnitSignals() {
    RegWrite = false;
    RegDst = false;
    Branch = false;
    ALUSrc = false;
    InstType = false; 
    MemWrite = false;
    MemtoReg = false;
    MemRead = false;
    Jump = false;
}

int controlUnit(int opcode, int funct) {
    resetConstrolUnitSignals();
    switch(opcode) {
        case 0x0:
        // R-Format
            // jr operation
            if(funct == 0x8){
                Jump = true;
            }
            else {
              RegDst = true;
              RegWrite = true;  
            }
            return ALUControl(2, funct);
        case 0x23:
        // lw operation
            ALUSrc = true;
            MemtoReg = true;
            RegWrite = true;
            MemRead = true;
            return ALUControl(0, funct);
        case 0x2b:
        // sw operation
            ALUSrc = true;
            MemWrite = true;
            return ALUControl(0, funct);
        case 0x4:
        // beq operation
            Branch = true;
            return ALUControl(1, funct);
        case 0x3:
        // jal operation
            Jump = true;
            return ALUControl(0, funct);
        case 0x2:
        // j operation
            Jump = true;
            return ALUControl(0, funct);
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
        else if(funct == 0x27){
            // NOR
            return 0xc;
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