#include <iostream>
#include <stdint.h>
#include <tuple>
#include <fstream>
#include <string>
#include <iomanip>
#include <map>

// Custom function
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
        cout << "program terminated:" << endl;  
        cout << "total execution time is " + to_string(total_clock_cycles) + " cycles" << endl;
        return 0;
    }
    cout << "Fetched instruction: " + instruction << endl;

    // DECODE
    int readData1, readData2, alu_op;
    string destReg;
    bool wbMux;
    tie(destReg, readData1, readData2, alu_op, wbMux) = decode(instruction);
    // cout << "readData1: " + to_string(readData1) << endl;
    // cout << "readData1: " + to_string(readData2) << endl;
    // cout << "alu_op: " + to_string(alu_op) << endl;

    // CONTROL UNIT
    // int alu_op = controlunit(?);

    // EXECUTE
    int alu_result = execute(readData1, readData2, alu_op);

    // No WRITEBACK
    if(destReg == "none") {
        continue;
    }
    // WRITEBACK
    // if(OPCODE(instruction) == )
    writeback(destReg, alu_result, wbMux);

    }
}
