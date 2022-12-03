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
        getline(input, line);

        set<char> comp1;
        int size = line.length();

        for (int i = 0; i < size/2; i++) comp1.insert(line[i]);
        for (int j = size/2; j < size; j++) {
            if (comp1.find(line[j]) != comp1.end()) {
                sum += getPriority(line[j]);
                break;
            }
        }
    }
    
    cout << "Sum of missing items: " << sum << endl;
}