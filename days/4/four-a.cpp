#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int count;
    while (!input.eof())
    {
        pair<int, int> left, right;
        getline(input, line, '-'); left.first  = stoi(line);
        getline(input, line, ','); left.second = stoi(line); 
        getline(input, line, '-'); right.first  = stoi(line);
        getline(input, line);      right.second = stoi(line);

        // Check if Left is contained in Right
        if (left.first >= right.first && left.second <= right.second) { count++; continue; }
        if (right.first >= left.first && right.second <= left.second) { count++; continue; }
    }
    
    cout << "Overlapping pairs: " << count << endl;
}