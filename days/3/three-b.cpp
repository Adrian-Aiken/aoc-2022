#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int getPriority(char c)
{
    if (c >= 'a' && c <= 'z'){
        return 1 + (c - 'a');
    } else {
        return 27 + (c - 'A');
    }
}

int main() {
    string line;
    ifstream input;

    input.open("input.txt");

    int sum = 0;
    while (!input.eof())
    {
        set<char> bag1, bag2;
        
        getline(input, line);
        for (int i = 0; i < line.length(); i++) bag1.insert(line[i]);

        getline(input, line);        
        for (int i = 0; i < line.length(); i++) bag2.insert(line[i]);

        getline(input, line);
        for (int i = 0; i < line.length(); i++) {
            if (bag1.find(line[i]) != bag1.end() && bag2.find(line[i]) != bag2.end()) {
                sum += getPriority(line[i]);
                break;
            }
        }
    }
    
    cout << "Sum of badges: " << sum << endl;
}