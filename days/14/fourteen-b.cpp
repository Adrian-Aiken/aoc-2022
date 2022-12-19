#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define Coord pair<int, int>
#define Line vector<Coord>
#define START_X 500
#define START_Y 0

vector<string> split(string s, string delim)
{
    vector<string> output;
    while (s.find(delim) != string::npos)
    {
        size_t pos = s.find(delim);
        output.push_back(s.substr(0, pos));
        s.erase(0, pos + delim.length());
    }
    output.push_back(s);
    return output;
}

void printMap(vector<string> map) { for (string s: map) cout << s << endl; }

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    int xmax = 0;
    int ymax = 0;

    vector<Line> lines;
    vector<string> map;

    // Parse input
    while (!input.eof())
    {
        getline(input, line);

        vector<string> tokens = split(line, " -> ");
        Line line;
        for (string s: tokens)
        {
            vector<string> sCoord = split(s, ",");
            int x = stoi(sCoord[0]);
            int y = stoi(sCoord[1]);
            line.push_back(Coord(x, y));
            xmax = max(xmax, x);
            ymax = max(ymax, y);
        }
        lines.push_back(line);
    }

    // Prepare and draw map
    for (int i = 0; i <= ymax+1; i++)
    {
        string s = "";
        for (int j = 0; j <= xmax*2; j++) s += ".";
        map.push_back(s);
    }
    // Add extra space and floor
    string hardFloor = "";
    for (int j = 0; j <= xmax*2; j++) hardFloor += "#";
    map.push_back(hardFloor);

    for (Line line: lines)
    {
        Coord dir, from, to = line[0];
        for (int i = 1; i < line.size(); i++)
        {
            from = to;
            to = line[i];

            if      (from.first  < to.first)  dir = Coord( 1, 0);
            else if (from.first  > to.first)  dir = Coord(-1, 0);
            else if (from.second < to.second) dir = Coord( 0, 1);
            else if (from.second > to.second) dir = Coord( 0,-1);

            map[from.second][from.first] = '#';
            while (from != to)
            {
                from.first += dir.first;
                from.second += dir.second;                
                map[from.second][from.first] = '#';
            }
        }
    }

    // Perform physics
    int count = 0;
    while(true)
    {
        int grain = START_X;

        // Drop grain
        int i = 0;
        for (; i < map.size(); i++)
        {
            // Check directly below
            if (map[i+1][grain] == '.') continue;

            // Check down-left
            if (map[i+1][grain-1] == '.' ) { grain--; continue; }

            // Check down-right
            if (map[i+1][grain+1] == '.') { grain++; continue; }

            break;
        }
        
        count++;        
        map[i][grain] = 'o';
        if (i == 0)  break;
    }    

    cout << "Grain count: " << count << endl;
}

