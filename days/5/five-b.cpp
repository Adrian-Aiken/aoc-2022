#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    string line;
    ifstream input;
    int numStacks;
    vector<deque<char>> dock;

    input.open("input.txt");    
    getline(input, line);

    numStacks = (line.length() + 1) / 4; // Stack width
    dock.assign(numStacks, deque<char>());

    // Step 1: Parse stacks
    while (!input.eof())
    {    
        // Check for stack number line; no more parsing
        if (line[1] == '1') {
            getline(input, line);
            break;
        }

        for (int i = 0; i < line.length(); i += 4)
        {
            if (line[i+1] == ' ') continue;

            dock[i/4].push_front(line[i+1]);
        }
        
        getline(input, line);
    }

    // Step 2: Run movement operations
    while (!input.eof())
    {
        int num, source, destination;
        getline(input, line, ' '); // move
        getline(input, line, ' '); // num
        num = stoi(line); 
        getline(input, line, ' '); // from
        getline(input, line, ' '); // source
        source = stoi(line) - 1;
        getline(input, line, ' '); // to
        getline(input, line     ); // destination
        destination = stoi(line) - 1;

        deque<char> temp;
        for (int i = 0; i < num; i++)
        {
            temp.push_back(dock[source].back());
            dock[source].pop_back();
        }
        for (int i = 0; i < num; i++)
        {
            dock[destination].push_back(temp.back());
            temp.pop_back();
        }
    }
    
    cout << "Top crates: ";
    for (deque<char> stack : dock) cout << stack.back();
    cout << endl;
}