#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define COORD pair<int, int>
#define MOVE_LIST map<COORD, vector<COORD>>

int main()
{
    string line;
    ifstream input;
    vector<string> field;
    vector<char> dirs {'N','S','E','W'};
    MOVE_LIST moves;
    int blocked, iterations = 0;

    input.open("input.txt");

    while (!input.eof())
    {
        getline(input, line);
        field.push_back(line);
    }

    do {
        blocked = 0;
        moves = MOVE_LIST();

        /// Add additional space
        // North
        if (field.front().find('#') != string::npos)
            field.insert(field.begin(), string(field[0].size(), '.'));
        // South
        if (field.back().find('#') != string::npos)
            field.push_back(string(field[0].size(), '.'));
        // East
        for (string s: field)
            if (s.front() == '#') 
            {
                for (string &s: field)
                    s.insert(s.begin(), '.');
                break;
            }
        // West
        for (string s: field)
            if (s.back() == '#')
            {
                for (string &s: field) s.push_back('.');
                break;
            }

        /// Record move proposals
        for (int row = 1; row < field.size()-1; row++)
        for (int col = 1; col < field[0].size()-1; col++)
        {
            // Elf Check
            if (field[row][col] == '.') continue;

            // Clear check
            bool clear = true;
            for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0) continue;
                if (field[row+i][col+j] == '#')
                {
                    clear = false;
                    break;
                }
            }
            if (clear) continue;
            
            // Move proposal
            bool canMove = false;
            for (char d: dirs)
            {
                if (canMove) break;
                switch(d)
                {
                    case 'N':
                        if (   field[row-1][col-1] == '.'
                            && field[row-1][col  ] == '.'
                            && field[row-1][col+1] == '.')
                            {
                                moves[COORD(row-1, col)].push_back(COORD(row, col));
                                canMove = true;
                            }
                        break;

                    case 'S':
                        if (   field[row+1][col-1] == '.'
                            && field[row+1][col  ] == '.'
                            && field[row+1][col+1] == '.')
                            {
                                moves[COORD(row+1, col)].push_back(COORD(row, col));
                                canMove = true;
                            }
                        break;

                    case 'E':
                        if (   field[row+1][col-1] == '.'
                            && field[row  ][col-1] == '.'
                            && field[row-1][col-1] == '.')
                            {
                                moves[COORD(row, col-1)].push_back(COORD(row, col));
                                canMove = true;
                            }
                        break;

                    case 'W':
                        if (   field[row+1][col+1] == '.'
                            && field[row  ][col+1] == '.'
                            && field[row-1][col+1] == '.')
                            {
                                moves[COORD(row, col+1)].push_back(COORD(row, col));
                                canMove = true;
                            }
                        break;                    
                }
            }

            if (!canMove) blocked++;
        }
        rotate(dirs.begin(), dirs.begin()+1, dirs.end());

        /// Perform moves
        for (auto proposal: moves)
        {
            if (proposal.second.size() > 1) continue;
            field[proposal.first.first][proposal.first.second] = '#';
            field[proposal.second[0].first][proposal.second[0].second] = '.';
        }
    } while (++iterations < 10);

    //****************************
    // For part one: Remove excess space
    while (field.front().find('#') == string::npos)
        field.erase(field.begin());
    // South
    while (field.back().find('#') == string::npos)
        field.pop_back();
    // East
    int eCount;
    do
    {
        eCount = 0;
        for (string s: field) if (s.front() == '#') eCount++;
        if (eCount == 0)
            for (string &d: field) d.erase(d.begin());
    } while (eCount == 0);
    // West
    do
    {
        eCount = 0;
        for (string s: field) if (s.back() == '#') eCount++;
        if (eCount == 0)
            for (string &d: field) d.pop_back();
    } while (eCount == 0);

    // Count empty spaces
    eCount = 0;
    for (string s: field)
    for (char c: s)
        if (c == '.')
            eCount++;
    
    cout << "Empty tiles: " << eCount << endl;
}