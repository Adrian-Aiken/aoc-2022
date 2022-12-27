#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <set>

using namespace std;

#define COORD pair<int, int>

char du[8] = { '^', 'a', 'b', 'c', 'g', 'h', 'i', 'k' };
char dr[8] = { '>', 'a', 'd', 'e', 'g', 'h', 'j', 'k' };
char dd[8] = { 'v', 'b', 'd', 'f', 'g', 'i', 'j', 'k' };
char dl[8] = { '<', 'c', 'e', 'f', 'h', 'i', 'j', 'k' };

char combineChar(char cur, char dir)
{
    switch (cur)
    {
        case '.':
            switch(dir){
                case '^': return '^';
                case '>': return '>';
                case 'v': return 'v';
                case '<': return '<';
            }

        case '^':
            switch(dir){
                case '^': return '^';
                case '>': return 'a';
                case 'v': return 'b';
                case '<': return 'c';
            }

        case '>':
            switch(dir){
                case '^': return 'a';
                case '>': return '>';
                case 'v': return 'd';
                case '<': return 'e';
            }

        case 'v':
            switch(dir){
                case '^': return 'b';
                case '>': return 'd';
                case 'v': return 'v';
                case '<': return 'f';
            }

        case '<':
            switch(dir){
                case '^': return 'c';
                case '>': return 'e';
                case 'v': return 'f';
                case '<': return '<';
            }

        case 'a':
            switch(dir){
                case '^': return 'a';
                case '>': return 'a';
                case 'v': return 'g';
                case '<': return 'h';
            }            

        case 'b':
            switch(dir){
                case '^': return 'b';
                case '>': return 'g';
                case 'v': return 'b';
                case '<': return 'i';
            }

        case 'c':
            switch(dir){
                case '^': return 'c';
                case '>': return 'h';
                case 'v': return 'i';
                case '<': return 'c';
            }

        case 'd':
            switch(dir){
                case '^': return 'g';
                case '>': return 'd';
                case 'v': return 'd';
                case '<': return 'j';
            }

        case 'e':
            switch(dir){
                case '^': return 'h';
                case '>': return 'e';
                case 'v': return 'j';
                case '<': return 'e';
            }

        case 'f':
            switch(dir){
                case '^': return 'i';
                case '>': return 'j';
                case 'v': return 'f';
                case '<': return 'f';
            }

        case 'g':
            switch(dir){
                case '^': return 'g';
                case '>': return 'g';
                case 'v': return 'g';
                case '<': return 'k';
            }

        case 'h':
            switch(dir){
                case '^': return 'h';
                case '>': return 'h';
                case 'v': return 'k';
                case '<': return 'h';
            }            

        case 'i':
            switch(dir){
                case '^': return 'i';
                case '>': return 'k';
                case 'v': return 'i';
                case '<': return 'i';
            }

        case 'j':
            switch(dir){
                case '^': return 'k';
                case '>': return 'j';
                case 'v': return 'j';
                case '<': return 'j';
            }

        case 'k':
            switch(dir){
                case '^': return 'k';
                case '>': return 'k';
                case 'v': return 'k';
                case '<': return 'k';
            }
    }

    return '.';
}

int main()
{
    string line;
    ifstream input;
    vector<string> valley, blank;
    vector<vector<string>> cycles;
    queue<vector<COORD>> searches;
    set<pair<int, COORD>> visited;
    int maxIterations, searchCycle = 1;

    input.open("input.txt");

    // Parse input
    while (!input.eof())
    {
        getline(input, line);
        valley.push_back(line);
    }

    // Prepare state
    cycles.push_back(valley);
    maxIterations = lcm(valley[0].size() - 2, valley.size() - 2);
    for (string s: valley)
    {
        string t;
        for (char c: s)
        {
            if (c == '<' || c == '^' || c == '>' || c == 'v') t.push_back('.');
            else (t.push_back(c));
        }
        blank.push_back(t);
    }

    // Generate valley configurations
    for (int iter = 1; iter < maxIterations; iter++)
    {   
        vector<string> &cur = cycles.back();
        vector<string> next = blank;

        for (int i = 1; i < cur.size(); i++)
        for (int j = 1; j < cur[i].size(); j++)
        {
            if (cur[i][j] == '#') continue;
            if (cur[i][j] == '.') continue;

            auto isUp    = find(begin(du), end(du), cur[i][j]) != end(du);
            auto isDown  = find(begin(dd), end(dd), cur[i][j]) != end(dd);
            auto isLeft  = find(begin(dl), end(dl), cur[i][j]) != end(dl);
            auto isRight = find(begin(dr), end(dr), cur[i][j]) != end(dr);

            if (isUp) 
            {            
                int nextRow = i-1 == 0 ? valley.size()-2 : i-1;
                next[nextRow][j] = combineChar(next[nextRow][j], '^');
            }
            if (isDown) 
            {            
                int nextRow = i+2 == valley.size() ? 1 : i+1;
                next[nextRow][j] = combineChar(next[nextRow][j], 'v');
            }
            if (isLeft)
            {
                int nextCol = j-1 == 0 ? valley[0].size()-2 : j-1;
                next[i][nextCol] = combineChar(next[i][nextCol], '<');
            }
            if (isRight)
            {
                int nextCol = j+2 == valley[0].size() ? 1 : j+1;
                next[i][nextCol] = combineChar(next[i][nextCol], '>');
            }
        }
        
        cycles.push_back(next);
    }

    // Perform search
    int maxLen = 0;
    searches.push(vector<COORD>({ COORD(0, 1) }));
    while (!searches.empty())
    {
        vector<COORD> curPath = searches.front(); searches.pop();
        COORD curSpot = curPath.back();
        vector<string> curMap = cycles[curPath.size() % cycles.size()];

        if (visited.find(pair<int, COORD>(curPath.size(), curSpot)) != visited.end()) continue;
        visited.emplace(pair<int, COORD>(curPath.size(), curSpot));

        if (curPath.size() > maxLen)
        {
            maxLen = curPath.size();
            cout << "Searching paths length: " << maxLen << "\t[Q: " << searches.size() << "]" << endl;
        }

        // Check end condition
        if (curSpot.first == valley.size()-1
            && curSpot.second == valley[0].size()-2)
        {
            cout << "Takes " << curPath.size()-1 << " minutes" << endl;
            break;
        }

        // Up - extra condition to prevent rentering to the entrance
        if (curSpot.first > 1 && curMap[curSpot.first-1][curSpot.second] == '.')
        {
            vector<COORD> newPath = curPath;
            newPath.push_back(COORD(curSpot.first-1, curSpot.second));
            searches.push(newPath);
        }

        // Down
        if (curMap[curSpot.first+1][curSpot.second] == '.')
        {
            vector<COORD> newPath = curPath;
            newPath.push_back(COORD(curSpot.first+1, curSpot.second));
            searches.push(newPath);
        }

        // Left
        if (curMap[curSpot.first][curSpot.second-1] == '.')
        {
            vector<COORD> newPath = curPath;
            newPath.push_back(COORD(curSpot.first, curSpot.second-1));
            searches.push(newPath);
        }

        // Right
        if (curMap[curSpot.first][curSpot.second+1] == '.')
        {
            vector<COORD> newPath = curPath;
            newPath.push_back(COORD(curSpot.first, curSpot.second+1));
            searches.push(newPath);
        }        

        // Wait in place
        if (curMap[curSpot.first][curSpot.second] == '.')
        {
            vector<COORD> newPath = curPath;
            newPath.push_back(COORD(curSpot.first, curSpot.second));
            searches.push(newPath);
        }
    }
}