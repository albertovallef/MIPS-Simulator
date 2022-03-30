#ifndef DECODER_H
#define DECODER_H

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
int jump_next = 0;

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
    int decimalNumber = 0;
    int exponent = binary.length() - 1;

    for(int i = 0; i < binary.length(); i++){
        if(binary[i] == '1') {
            decimalNumber = decimalNumber + pow(2, exponent);
        }
        exponent--;
    }
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

#endif