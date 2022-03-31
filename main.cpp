#include <iostream>
#include <stdint.h>
#include "decode.h"
#include "fetch.h"

using namespace std;

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

    // testing
    // int num = 0xf;
    // cout << std::hex << num << endl;
}
