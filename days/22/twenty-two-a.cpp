#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int main()
{
    string line, directions;
    ifstream input;
    vector<string> map;
    int row = 0, col = 0, di = 0, ra = 0, ca = 0, maxRow = 0;
    size_t i = 0;

    input.open("input.txt");
    
    // Parse input
    getline(input, line);
    while (line != "")
    {
        maxRow = max(maxRow, (int)line.size());
        map.push_back(line);
        getline(input, line);
    }
    getline(input, directions);

    // Prepare board
    while (map[0][col] != '.') col++;
    for (int i = 0; i < map.size(); i++)
    for (int j = map[i].size(); j < maxRow; j++)
        map[i].push_back(' ');

    // Get directions
    while (i < directions.size())
    {
        if (directions[i] == 'R') { di = (di+1) % 4; i++; continue; }
        if (directions[i] == 'L') { di = (di+3) % 4; i++; continue; }

        directions = directions.substr(i);
        int dist = stoi(directions, &i);

        for (int j = 0; j < dist; j++)
        {
            // Current row + direction + adjustment (for wrapping around the map)
            int r = ra == -1 ? row + dir[di][0] : ra;
            int c = ca == -1 ? col + dir[di][1] : ca;
            ra = -1; ca = -1;

            if (r >= (int)map.size()) r = 0;
            if (r < 0) r = map.size()-1;
            if (c >= (int)map[row].size()) c=  0;
            if (c < 0) c = map[r].size()-1;

            switch(map[r][c])
            {
                case '.': row = r; col = c; break;
                case '#': j = dist; break;
                case ' ': 
                    if (dir[di][0] != 0)
                    {
                        ra = r;
                        while (map[ra][c] == ' ')
                        {
                            ra += dir[di][0];
                            if (ra < 0)           ra = map.size() - 1;
                            if (ra >= map.size()) ra = 0;
                        }
                    }
                    else
                    {        
                        ca = c;                
                        while (map[r][ca] == ' ')
                        {
                            ca += dir[di][1];
                            if (ca < 0)              ca = map[r].size() - 1;
                            if (ca >= map[r].size()) ca = 0;
                        }
                    }
                    j--;
                    break;
            }
        }
    }

    cout << "Password: " << ((row+1)*1000) + ((col+1)*4) + (di) << endl;
}
