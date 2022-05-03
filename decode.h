#ifndef DECODE_H
#define DECODE_H

using namespace std;

#define OPCODE(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(0, 6))))
#define RS(instruction) (getRegisterName(binaryToDecimal(instruction.substr(6, 5))))
#define RT(instruction) (getRegisterName(binaryToDecimal(instruction.substr(11, 5))))
#define RD(instruction) (getRegisterName(binaryToDecimal(instruction.substr(16, 5))))
#define ADDRESS(instruction) (binaryToDecimal(instruction.substr(6, 26)))
#define IMMEDIATE(instruction) (binaryToDecimal(instruction.substr(16, 16)))
#define FUNCT(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(26, 6))))
#define SHAMT(instruction) (to_string(binaryToDecimal(instruction.substr(21, 5))))

extern int pc;
extern int next_pc;

template<typename T>
string decimalToHexa(T value);
string getInstructionType(string opcode);
string getRegisterName(int registerNumber);
int binaryToDecimal(string binary);
int sign_extend(int binary, int bits);
int jump_next = 0;
int jump_jal = 0;
tuple<string, int, int> decodeRtypeInstruction(string instruction);
tuple<string, int, int> decodeItypeInstruction(string instruction);
tuple<string, int, int> decodeJtypeInstruction(string instruction);
map<string, int> registerfile = {
        {"$zero", 0,}, // $zero
        {"$at", 0,}, // $at
        {"$v0", 0,}, {"$v1", 0,}, // $v0-$v1
        {"$a0", 0x5,},{"$a1", 0x2,},{"$a2", 0,},{"$a3", 0xa,}, // $a0-$a3
        {"$t0", 0,},{"$t1", 0,},{"$t2", 0,},{"$t3", 0,},{"$t4", 0,},{"$t5", 0,},{"$t6", 0,},{"$t7", 0,}, // $t0-$t7
        {"$s0", 0x20,},{"$s1", 0,},{"$s2", 0,},{"$s3", 0,},{"$s4", 0,},{"$s5", 0,},{"$s6", 0,},{"$s7", 0,}, // $s0-$s7
        {"$t8", 0,},{"$t9", 0,}, // $t8-$t9
        {"$k0", 0,},{"$k1", 0,}, // $k0-$k1
        {"$gp", 0,}, // $gp
        {"$sp", 0,}, // $sp
        {"$fp", 0,}, // $fp
        {"$ra", 0,}, // $ra
        };

tuple<string, int, int> decode(string instruction)
{
    string instructionType = getInstructionType(OPCODE(instruction));
    if(instructionType == "R"){
        return decodeRtypeInstruction(instruction);
    }
    else if(instructionType == "I"){
        return decodeItypeInstruction(instruction);
    }
    else {
        decodeJtypeInstruction(instruction);
        // FAKE data, need to implement this
        string ran = "ads";
        return make_tuple(ran, 2, 3);
    }
}

int binaryToDecimal(string binary) {
	int decimalNumber = stoi(binary, 0, 2);
    return decimalNumber;
}

template<typename T >
string decimalToHexa( T value){
    std::stringstream stream;
    stream << std::hex << value;
    return stream.str();
}

string getInstructionType(string opcode){
    if(opcode == "0"){
        return "R";
    }
    else if (opcode == "2" || opcode == "3"){
        return "J";
    }
    else{
        return "I";
    }
}

tuple<string, int, int> decodeRtypeInstruction(string instruction){
    map<string, string> operationTable = {
        {"20", "add",}, 
        {"21", "addu",},
        {"24", "and",},
        {"8", "jr",},
        {"27", "nor",},
        {"25", "or",},
        {"2a", "slt",},
        {"2b", "sltu",},
        {"0", "sll",},
        {"2", "srl",},
        {"22", "sub",},
        {"23", "subu",}
        };
    // TODO: Need to clean this up
    if(operationTable[FUNCT(instruction)] == "jr"){
        int readData1 = 0;
        int readData2 = 0;
        string destReg = "None";
        return make_tuple(destReg, readData1, readData2);
    } 
    else {
        int readData1 = registerfile[RS(instruction)];
        int readData2 = registerfile[RT(instruction)];
        string destReg = RD(instruction);
        return make_tuple(destReg, readData1, readData2);
    }
}

tuple<string, int, int> decodeItypeInstruction(string instruction){
    map<string, string> operationTable = {
        {"8", "addi",},
        {"9", "addiu",},
        {"c", "andi",},
        {"4", "beq",},
        {"5", "bne",},
        {"24", "lbu",},
        {"25", "lhu",},
        {"30", "ll",},
        {"f", "lui",},
        {"23", "lw",},
        {"d", "ori",},
        {"a", "slti",},
        {"b", "sltiu",},
        {"28", "sb",},
        {"29", "sh",},
        {"2b", "sw",}
        };

    if(operationTable[OPCODE(instruction)] == "lw"){
        int readData1 = registerfile[RS(instruction)];
        int readData2 = sign_extend(IMMEDIATE(instruction), 32);
        string destReg = RT(instruction);
        return make_tuple(destReg, readData1, readData2); 
    }
    else if (operationTable[OPCODE(instruction)] == "beq") {
        int readData1 = registerfile[RS(instruction)];
        int readData2 = registerfile[RT(instruction)];
        jump_next = sign_extend(IMMEDIATE(instruction), 32);
        jump_next = jump_next << 2;
        string destReg = "none";
        return make_tuple(destReg, readData1, readData2); 
    }
    else if (operationTable[OPCODE(instruction)] == "sw") {
        int readData1 = registerfile[RS(instruction)];
        int readData2 = sign_extend(IMMEDIATE(instruction), 32);
        string destReg = RT(instruction);
        return make_tuple(destReg, readData1, readData2); 
    }
    string destReg = RT(instruction);
    return make_tuple(destReg, 1, 1);

}

tuple<string, int, int> decodeJtypeInstruction(string instruction){
    map<string, string> operationTable = {
        {"2", "j",},
        {"3", "jal",}
        };

    if(operationTable[OPCODE(instruction)] == "j"){
        //jump_next = jump_next << 4;
        string destReg = "none";
        return make_tuple(destReg, 0, 0); 
    }
    else if (operationTable[OPCODE(instruction)] == "jal") {
        registerfile["$ra"] = next_pc;
        pc = ADDRESS(instruction);
        string destReg = "$ra";
        return make_tuple(destReg, 0, 0); 
    }
    string destReg = RT(instruction);
    return make_tuple(destReg, 1, 1);
}

int sign_extend(int binary, int bits) {
    int m = 1;
    m <<= bits - 1;
    return (binary ^ m) - m;
}

string getRegisterName(int regNumber){
    switch(regNumber) {
    case 0: return "$zero";
    case 1: return "$at";
    case 2: return "$v0";
    case 3: return "$v1";
    case 4: return "$a0";
    case 5: return "$a1";
    case 6: return "$a2";
    case 7: return "$a3";
    case 8: return "$t0";
    case 9: return "$t1";
    case 10: return "$t2";
    case 11: return "$t3";
    case 12: return "$t4";
    case 13: return "$t5";
    case 14: return "$t6";
    case 15: return "$t7";
    case 16: return "$s0";
    case 17: return "$s1";
    case 18: return "$s2";
    case 19: return "$s3";
    case 20: return "$s4";
    case 21: return "$s5";
    case 22: return "$s6";
    case 23: return "$s7";
    case 24: return "$t8";
    case 25: return "$t9";
    case 26: return "$k0";
    case 27: return "$k1";
    case 28: return "$gp";
    case 29: return "$sp";
    case 30: return "$fp";
    case 31: return "$ra";
    default: return "$error";
    }
}

#endif