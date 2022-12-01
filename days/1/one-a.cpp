#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int mostCalories = 0, curCalories = 0;
    while (!input.eof())
    {
        getline(input, line);
        if (line == "") {
            if (curCalories > mostCalories) {
                mostCalories = curCalories;
            }
            curCalories = 0;
        } else {
            curCalories += stoi(line);
        }
    }
    
    cout << "Most calories: " << mostCalories;
}