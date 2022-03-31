#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <math.h>
#include <iomanip>
#include <map>
#include<tuple>

using namespace std;

#define OPCODE(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(0, 6))))
#define RS(instruction) (binaryToDecimal(instruction.substr(6, 5)))
#define RT(instruction) (binaryToDecimal(instruction.substr(11, 5)))
#define RD(instruction) (binaryToDecimal(instruction.substr(16, 5)))
#define ADDRESS(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(6, 26))))
#define IMMEDIATE(instruction) (binaryToDecimal(instruction.substr(16, 16)))
#define FUNCT(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(26, 6))))
#define SHAMT(instruction) (to_string(binaryToDecimal(instruction.substr(21, 5))))

template<typename T>
string decimalToHexa(T value);
string getInstructionType(string opcode);
int binaryToDecimal(string binary);
int sign_extend(int binary, int bits);
int jump_next = 0;
void decodeRtypeInstruction(string instruction);
tuple<int, int, int> decodeItypeInstruction(string instruction);
void decodeJtypeInstruction(string instruction);
map<string, int> registerfile = {
        {"$0", 0,}, // $zero
        {"$1", 0,}, // $at
        {"$2", 0,}, {"$3", 0,}, // $v0-$v1
        {"$4", 0,},{"$5", 0,},{"$6", 0,},{"$7", 0,}, // $a1-$a3
        {"$8", 0,},{"$9", 0,},{"$10", 0,},{"$11", 0,},{"$12", 0,},{"$13", 0,},{"$14", 0,},{"$15", 0,}, // $t0-$t7
        {"$16", 0,},{"$17", 0,},{"$18", 0,},{"$19", 0,},{"$20", 0,},{"$21", 0,},{"$22", 0,},{"$23", 0,}, // $s0-$s7
        {"$24", 0,},{"$25", 0,}, // $t8-$t9
        {"$26", 0,},{"$27", 0,}, // $k0-$k1
        {"$28", 0,}, // $gp
        {"$29", 0,}, // $sp
        {"$30", 0,}, // $fp
        {"$31", 0,}, // $ra
        };

tuple<int, int, int> decode(string instruction)
{
    string instructionType = getInstructionType(OPCODE(instruction));
    if(instructionType == "R"){
        decodeRtypeInstruction(instruction);
        return make_tuple(1, 2, 3);
    }
    else if(instructionType == "I"){
        return decodeItypeInstruction(instruction);
    }
    else {
        decodeJtypeInstruction(instruction);
        return make_tuple(1, 2, 3);
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

void decodeRtypeInstruction(string instruction){
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

    cout << "Instruction Type: R" << endl;
    cout << "Operation: " + operationTable[FUNCT(instruction)]<< endl;
    cout << "Rs: $" + to_string(RS(instruction)) << endl;
    cout << "Rt: $" + to_string(RT(instruction)) << endl;
    cout << "Rd: $" + to_string(RD(instruction)) << endl;
    cout << "Shamt: " + SHAMT(instruction) << endl;
    cout << "Funct: 0x" + FUNCT(instruction)<< endl;
}

tuple<int, int, int> decodeItypeInstruction(string instruction){
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

    cout << "Instruction Type: I" << endl;
    // cout << "Operation: " + operationTable[OPCODE(instruction)]<< endl;
    // cout << "Rs: $" + to_string(RS(instruction)) << endl;
    // cout << "Rt: $" + to_string(RT(instruction)) << endl;
    // cout << std::hex << "Immediate: 0x" + to_string(sign_extend(IMMEDIATE(instruction), 32))<< endl;
    if(operationTable[OPCODE(instruction)] == "lw"){
        int alu_op = 2;
        int readData1 = registerfile[to_string(RS(instruction))];
        int readData2 = sign_extend(IMMEDIATE(instruction), 32);
        return make_tuple(readData1, readData2, alu_op); // ADD for alu_op
    }
    return make_tuple(1, 2, 3);

}

void decodeJtypeInstruction(string instruction){
    map<string, string> operationTable = {
        {"2", "j",},
        {"3", "jal",}
        };

    cout << "Instruction Type: J" << endl;
    cout << "Operation: " + operationTable[OPCODE(instruction)]<< endl;
    cout << "Immediate: 0x" + ADDRESS(instruction) << endl;
}

int sign_extend(int binary, int bits) {
    int m = 1;
    m <<= bits - 1;
    return (binary ^ m) - m;
}

#endif