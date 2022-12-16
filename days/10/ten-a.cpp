#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Check_Cycles[7] = {20, 60, 100, 140, 180, 220, INT_MAX};

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int X = 1, clock = 0, i = 0, signalSums = 0;

    while (!input.eof())
    {
        getline(input, line);
        clock++;

        if (clock >= Check_Cycles[i]) signalSums += (X * Check_Cycles[i++]);       

        switch (line[0])
        {
            case 'a': //addx
                clock++;
                                
                if (clock >= Check_Cycles[i]) signalSums += (X * Check_Cycles[i++]);

                X += stoi(line.substr(5));
                break;
            
            case 'n': // noop
                break;
        }
    }
    
    cout << "Clock: " << clock << "\tX: " << X << endl;
    cout << "Signal Sums: " << signalSums << endl;
}