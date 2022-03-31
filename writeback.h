#ifndef WRITEBACK_H
#define WRITEBACK_H

using namespace std;

int total_clock_cycles = 0;

void writeback(int value_changed){
    total_clock_cycles++;
    cout << "total_clock_cycles " + to_string(total_clock_cycles) << endl;
    cout << std::hex << "... is modified to 0x" + to_string(value_changed) << endl;   
}

#endif