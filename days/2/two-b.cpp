#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int score = 0;

    while (!input.eof())
    {
        getline(input, line);
        
        switch(line[0]) {
            case 'A':
                switch(line[2]) {
                    case 'X': score += 3; break;
                    case 'Y': score += 4; break;
                    case 'Z': score += 8; break;
                }
                break;

            case 'B':
                switch(line[2]) {
                    case 'X': score += 1; break;
                    case 'Y': score += 5; break;
                    case 'Z': score += 9; break;
                }
                break;

            case 'C':
                switch(line[2]) {
                    case 'X': score += 2; break;
                    case 'Y': score += 6; break;
                    case 'Z': score += 7; break;
                }
                break;
        }
    }
    
    cout << "Score: " << score << endl;
}