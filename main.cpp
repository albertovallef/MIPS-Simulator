#include <iostream>
#include <stdint.h>
#include <tuple>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>

// Custom functions
#include "control_unit.h"
#include "decode.h"
#include "fetch.h"
#include "execute.h"
#include "writeback.h"

using namespace std;

int main()
{
    // Get the name of the text file with instructions
    string textFile = "sample_part1.txt";
    // cin >> textFile;

    while(true){
    // FETCH
    string instruction = fetch(textFile);
    // If no instruction, terminate program
    if(instruction == ""){
        cout << endl;
        cout << "program terminated:" << endl;  
        cout << "total execution time is " + to_string(total_clock_cycles) + " cycles" << endl;
        return 0;
    }
    // cout << "Fetched instruction: " + instruction << endl;
    cout << endl;

    // DECODE
    int readData1, readData2;
    string destReg;
    bool memtoReg, memWrite;
    tie(destReg, readData1, readData2, memtoReg, memWrite) = decode(instruction);

    // CONTROL UNIT
    int opcode = binaryToDecimal(instruction.substr(0, 6));
    int funct = binaryToDecimal(instruction.substr(26, 6));
    int ALUControl_result = controlUnit(opcode, funct);;

    // EXECUTE
    int alu_result = execute(readData1, readData2, ALUControl_result);

    // No WRITEBACK
    if(destReg == "none") {
        continue;
    }
    writeback(destReg, alu_result, memtoReg, memWrite);

    }
}
