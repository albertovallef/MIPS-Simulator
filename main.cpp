#include <iostream>
#include <stdint.h>
#include "decode.h"
#include "fetch.h"

using namespace std;

int main()
{
    while(true){
    // Get the name of the text file with instructions
    string textFile = "sample_part1.txt";
    // cin >> textFile;

    // FETCH
    string instruction = fetch(textFile);
    // If no instruction, terminate program
    if(instruction == ""){
        return 0;
    }
    cout << "Fetched instruction: " + instruction << endl;

    // DECODE
    cout << "DECODE instruction: " << endl;
    decode(instruction);
    }
}
