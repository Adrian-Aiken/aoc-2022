#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream input;

    input.open("sample.txt");

    int score = 0;

    while (!input.eof())
    {
        getline(input, line);
        
        switch(line[0]) {
            case 'A':
                switch(line[2]) {
                    case 'X': score += 4; break;
                    case 'Y': score += 8; break;
                    case 'Z': score += 3; break;
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
                    case 'X': score += 7; break;
                    case 'Y': score += 2; break;
                    case 'Z': score += 6; break;
                }
                break;
        }
    }
    
    cout << "Score: " << score << endl;
}