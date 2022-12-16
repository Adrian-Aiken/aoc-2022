#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define ROW_SIZE 40

int X = 1, c = 0;

void drawPoint()
{
    int pos = c++ % ROW_SIZE;

    if (pos == 0) cout << endl; // New row, newline

    char outchar = abs(pos-X) > 1 ? '.' : '#';
    cout << outchar;
}

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    while (!input.eof())
    {
        getline(input, line);
        drawPoint();

        switch (line[0])
        {
            case 'a': //addx
                drawPoint();
                X += stoi(line.substr(5));
                break;
            
            case 'n': // noop
                break;
        }
    }
}