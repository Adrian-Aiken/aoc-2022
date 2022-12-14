#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isTreeVisible(vector<vector<int>> grid, int x, int y)
{
    // Edge checks: edge trees are always visible
    if (x == 0 || y == 0 || x == (grid.size()-1) || y == (grid[x].size()-1))
        return true;

    int tree = grid[x][y], maxCheck;

    // Left of row check
    maxCheck = 0;
    for (int i = 0; i < x; i++) 
        maxCheck = max(maxCheck, grid[i][y]);
    if (maxCheck < tree) return true;

    // Right of row check
    maxCheck = 0;
    for (int i = x+1; i < grid.size(); i++) maxCheck = max(maxCheck, grid[i][y]);
    if (maxCheck < tree) return true;

    // Above row check
    maxCheck = 0;
    for (int i = 0; i < y; i++) maxCheck = max(maxCheck, grid[x][i]);
    if (maxCheck < tree) return true;

    // Below row check
    maxCheck = 0;
    for (int i = y+1; i < grid[x].size(); i++) maxCheck = max(maxCheck, grid[x][i]);
    if (maxCheck < tree) return true;

    return false;
}

int main()
{
    string line;
    ifstream input;

    input.open("sample.txt");

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
    int visibleCount = 0;
    for (int i = 0; i < grid.size(); i++)
    for (int j = 0; j < grid[i].size(); j++)
    {
        if (isTreeVisible(grid, i, j)) visibleCount++;
    }

    cout << "Visible trees: " << visibleCount << endl;
}