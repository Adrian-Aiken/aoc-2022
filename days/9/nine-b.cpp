#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#define NUM_KNOTS 10

using namespace std;

bool cellsAdjacent(pair<int, int> left, pair<int, int> right)
{
    return (abs(left.first-right.first) <= 1) && (abs(left.second-right.second) <= 1);
}

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    set<pair<int, int>> visited;
    vector<pair<int, int>> knots;
    for (int i = 0; i < NUM_KNOTS; i++) knots.push_back(pair<int, int>(0, 0));

    while (!input.eof())
    {
        getline(input, line, ' ');
        char dir = line[0];
        getline(input, line);
        int steps = stoi(line);
        
        for (int i = 0; i < steps; i++)
        {
            // Move Head
            switch (dir)
            {
                case 'R': knots[0].second += 1; break;
                case 'L': knots[0].second -= 1; break;
                case 'U': knots[0].first  += 1; break;
                case 'D': knots[0].first  -= 1; break;
            }

            // Move remaining knots
            for (int j = 1; j < NUM_KNOTS; j++)
            {
                if (cellsAdjacent(knots[j-1], knots[j])) break;
                
                if (knots[j-1].first  > knots[j].first ) knots[j].first++;
                if (knots[j-1].first  < knots[j].first ) knots[j].first--;
                if (knots[j-1].second > knots[j].second) knots[j].second++;
                if (knots[j-1].second < knots[j].second) knots[j].second--;
            }
            
            // Record tail position
            visited.insert(pair<int, int>(knots[NUM_KNOTS-1].first, knots[NUM_KNOTS-1].second));
        }
    }
    
    cout << "Spaces visited: " << visited.size() << endl;
}