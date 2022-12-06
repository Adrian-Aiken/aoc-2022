#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

#define WINDOW_SIZE 4

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");    
    getline(input, line);

    int start = 0;
    while(true)
    {
        set<char> window;
        for (int i = 0; i < WINDOW_SIZE; i++)
        {
            window.insert(line[start+i]);
        }
        
        if (window.size() == WINDOW_SIZE) break;
        start++;
    }
    
    cout << "Packet start: " << start + WINDOW_SIZE << endl;
}