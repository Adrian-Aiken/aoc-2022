#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getSenicScore (vector<vector<int>> grid, int x, int y)
{
    // Edge checks: edge trees always have a score of 0
    if (x == 0 || y == 0 || x == (grid.size()-1) || y == (grid[x].size()-1))
        return 0;

    int tree = grid[x][y], dist, score;

    // Calculate left score
    dist = 0;
    for (int i = x-1; i >= 0; i--)
    {
        dist++;
        if (grid[i][y] >= tree) break;
    }
    score = dist;

    // Calculate right score
    dist = 0;
    for (int i = x+1; i < grid.size(); i++)
    {
        dist++;
        if (grid[i][y] >= tree) break;
    }
    score *= dist;

    // Calculate up score
    dist = 0;
    for (int i = y-1; i >= 0; i--)
    {
        dist++;
        if (grid[x][i] >= tree) break;
    }
    score *= dist;

    // Calculate down score
    dist = 0;
    for (int i = y+1; i < grid[x].size(); i++)
    {
        dist++;
        if (grid[x][i] >= tree) break;
    }
    score *= dist;

    return score;
}

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    vector<vector<int>> grid;

    // Parse input
    while (!input.eof())
    {
        getline(input, line);
        vector<int> row;

        for (char c : line)
        {
            row.push_back(c-'0');
        }

        grid.push_back(row);
    }

    // Generate count
    int maxScore = 0;
    for (int i = 0; i < grid.size(); i++)
    for (int j = 0; j < grid[i].size(); j++)
    {
        maxScore = max(maxScore, getSenicScore(grid, i, j));
    }

    cout << "Most senic value: " << maxScore << endl;
}