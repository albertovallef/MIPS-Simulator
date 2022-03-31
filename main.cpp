#include <iostream>
#include <stdint.h>
#include<tuple>
#include "decode.h"
#include "fetch.h"
#include "execute.h"

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
        return 0;
    }
    cout << "Fetched instruction: " + instruction << endl;

    // DECODE
    cout << "DECODE instruction: " << endl;
    int readData1, readData2, alu_op;
    tie(readData1, readData2, alu_op) = decode(instruction);

    // EXECUTE
    int alu_result = execute(readData1, readData2, alu_op);
    cout << alu_result << endl;
    }
}
