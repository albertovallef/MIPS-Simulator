#include <iostream>
#include <fstream>
#include <string>
#include "decoder.h"

using namespace std;

// Functions implemented
string fetch(string textFile);

// Global variables
int pc = 4;
int next_pc =  pc + 4;

int main()
{
    // Get the name of the text file with instructions
    string textFile = "sample_part1.txt";
    // cin >> textFile;

    // Fetch the instruction from the text file
    string instruction = fetch(textFile);
    cout << instruction << endl;

    // Decode instruction 
    decode(instruction);
}

string fetch(string textFile) { 
    string instruction;
    fstream InstructionFile(textFile, ios::in);

    // Open file 
    if (InstructionFile.is_open())
    {
        int i = 0;
        // Iterate over the lines in the file
        while ( InstructionFile.good() )
        {
            // Get the current PC instruction
            getline(InstructionFile, instruction);
            if (pc == 0){
                pc += 4;
                return instruction;
            }
            else if(pc/4 == i){
                pc += 4;
                return instruction;
            }
            i++;
        }
        // Close the file
        InstructionFile.close();
    }
    return "Failed to open file";
}