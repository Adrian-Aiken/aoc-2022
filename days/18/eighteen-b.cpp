#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <queue>

using namespace std;

#define DROP_SIZE 20
#define COORD tuple<int, int, int>

vector<int> splitInt(string s, string delim)
{
    vector<int> output;
    while (s.find(delim) != string::npos)
    {
        size_t pos = s.find(delim);
        output.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + delim.length());
    }
    output.push_back(stoi(s));
    return output;
}

int main()
{
    string line;
    ifstream input;
    vector<vector<vector<bool>>> drop;
    set<COORD> outside;
    queue<COORD> outCheck;

    // Init droplet vector
    for (int i = 0; i < DROP_SIZE; i++)
    {
        vector<vector<bool>> dropSlice;
        for (int j = 0; j < DROP_SIZE; j++)
            dropSlice.push_back(vector<bool>(DROP_SIZE, false));
        drop.push_back(dropSlice);
    }

    // Fill out droplet
    input.open("input.txt");
    while (!input.eof())
    {
        getline(input, line);
        auto p = splitInt(line, ",");
        drop[p[0]][p[1]][p[2]] = true;
    }

    // Cache 'outside' spaces
    outCheck.push(COORD(0, 0, 0));
    while (!outCheck.empty())
    {
        auto c = outCheck.front(); outCheck.pop();
        if (!outside.insert(c).second) continue;

        int x = get<0>(c), y = get<1>(c), z = get<2>(c);

        if (x+1 < DROP_SIZE && !drop[x+1][y][z]) outCheck.push(COORD(x+1, y, z));
        if (x   > 0         && !drop[x-1][y][z]) outCheck.push(COORD(x-1, y, z));
        if (y+1 < DROP_SIZE && !drop[x][y+1][z]) outCheck.push(COORD(x, y+1, z));
        if (y   > 0         && !drop[x][y-1][z]) outCheck.push(COORD(x, y-1, z));
        if (z+1 < DROP_SIZE && !drop[x][y][z+1]) outCheck.push(COORD(x, y, z+1));
        if (z   > 0         && !drop[x][y][z-1]) outCheck.push(COORD(x, y, z-1));
    }

    // Fill in air pockets
    for (int x = 0; x < DROP_SIZE; x++)
    for (int y = 0; y < DROP_SIZE; y++)
    for (int z = 0; z < DROP_SIZE; z++)
    {
        if (drop[x][y][z]) continue;
        if (outside.find(COORD(x, y, z)) != outside.end()) continue;

        drop[x][y][z] = true;
    }

    // Calculate surface area
    uint64_t surfaceArea = 0;
    for (int x = 0; x < DROP_SIZE; x++)
    for (int y = 0; y < DROP_SIZE; y++)
    for (int z = 0; z < DROP_SIZE; z++)
    {
        if (!drop[x][y][z]) continue;
        
        surfaceArea += 6;
        if (x+1 < DROP_SIZE && drop[x+1][y][z]) surfaceArea--;
        if (x   > 0         && drop[x-1][y][z]) surfaceArea--;
        if (y+1 < DROP_SIZE && drop[x][y+1][z]) surfaceArea--;
        if (y   > 0         && drop[x][y-1][z]) surfaceArea--;
        if (z+1 < DROP_SIZE && drop[x][y][z+1]) surfaceArea--;
        if (z   > 0         && drop[x][y][z-1]) surfaceArea--;
    }
    
    cout << "Surface Area: " <<  surfaceArea << endl;
}