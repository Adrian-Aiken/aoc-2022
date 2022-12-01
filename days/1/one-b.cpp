#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int curCalories = 0;
    vector<int> calorieCount;
    while (!input.eof())
    {
        getline(input, line);
        if (line == "") {
            calorieCount.push_back(curCalories);
            curCalories = 0;
        } else {
            curCalories += stoi(line);
        }
    }

    sort(calorieCount.begin(), calorieCount.end(), std::greater<>());

    int fullCalories = 0;
    fullCalories += calorieCount[0];
    fullCalories += calorieCount[1];
    fullCalories += calorieCount[2];
    
    for (int i: calorieCount) {
        cout << "calorie: " << i << "\n";
    }

    cout << "Top 3 calories: " << fullCalories;
}