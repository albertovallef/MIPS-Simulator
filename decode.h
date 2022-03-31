#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <math.h>
#include <iomanip>
#include <map>

using namespace std;

#define OPCODE(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(0, 6))))
#define RS(instruction) (to_string(binaryToDecimal(instruction.substr(6, 5))))
#define RT(instruction) (to_string(binaryToDecimal(instruction.substr(11, 5))))
#define RD(instruction) (to_string(binaryToDecimal(instruction.substr(16, 5))))
#define ADDRESS(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(6, 26))))
#define IMMEDIATE(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(16, 16))))
#define FUNCT(instruction) (decimalToHexa(binaryToDecimal(instruction.substr(26, 6))))
#define SHAMT(instruction) (to_string(binaryToDecimal(instruction.substr(21, 5))))

template<typename T>
string decimalToHexa(T value);
string getInstructionType(string opcode);
int binaryToDecimal(string binary);
void decodeRtypeInstruction(string instruction);
void decodeItypeInstruction(string instruction);
void decodeJtypeInstruction(string instruction);
string signExtend(string offset);
int jump_next = 0;
map<string, int> registerfile = {
        {"$0", 0,},
        {"$1", 0,},
        {"$2", 0,}, {"$3", 0,},
        {"$4", 0,},{"$5", 0,},{"$6", 0,},{"$7", 0,},
        {"$8", 0,},{"$9", 0,},{"$10", 0,},{"$11", 0,},{"$12", 0,},{"$13", 0,},{"$14", 0,},{"$15", 0,},
        {"$16", 0,},{"$17", 0,},{"$18", 0,},{"$19", 0,},{"$20", 0,},{"$21", 0,},{"$22", 0,},{"$23", 0,},
        {"$24", 0,},{"$25", 0,},{"$26", 0,},{"$27", 0,}, 
        {"$28", 0,},
        {"$29", 0,},
        {"$30", 0,},
        {"$31", 0,},
        };

void decode(string instruction)
{
    string instructionType = getInstructionType(OPCODE(instruction));
    if(instructionType == "R"){
        decodeRtypeInstruction(instruction);
    }
    else if(instructionType == "I"){
        decodeItypeInstruction(instruction);
    }
    else {
        decodeJtypeInstruction(instruction);
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
    cout << "Rs: $" + RS(instruction) << endl;
    cout << "Rt: $" + RT(instruction) << endl;
    cout << "Rd: $" + RD(instruction) << endl;
    cout << "Shamt: " + SHAMT(instruction) << endl;
    cout << "Funct: 0x" + FUNCT(instruction)<< endl;
}

void decodeItypeInstruction(string instruction){
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
    cout << "Operation: " + operationTable[OPCODE(instruction)]<< endl;
    cout << "Rs: $" + RS(instruction) << endl;
    cout << "Rt: $" + RT(instruction) << endl;
    cout << "Immediate: 0x" + IMMEDIATE(instruction)<< endl;
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

string signExtend(string offset) {
    cout << offset[0]<< endl;
    return "";
}

#endif