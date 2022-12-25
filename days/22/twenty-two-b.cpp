#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define EDGE_SIZE 50
#define D_RIGHT 0
#define D_DOWN 1
#define D_LEFT 2
#define D_UP 3

vector<string> map;
struct NewDir { int c, r, d; };
int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
int sides[6][2] = { {0,1}, {0,2}, {1,1}, {2,0}, {2,1}, {3,0} };
int edge[6][4] =
{
    {1,2,3,5},
    {4,2,0,5},
    {1,4,3,0},
    {4,5,0,2},
    {1,5,3,2},
    {4,1,0,3}
};

// Directions are up, right, down, left

int getSide(int r, int c)
{
    if (r < 0 || c < 0) return -1;

    int xCoord = r/EDGE_SIZE, yCoord = c/EDGE_SIZE;

    for (int i = 0; i < 6; i++)
        if (sides[i][0] == xCoord && sides[i][1] == yCoord)
            return i;

    return -1;
}

NewDir getWarpedCoord(const int r, const int c, const int di)
{
    int dr = r+dir[di][0]; if (dr < 0) dr = map.size()-1;
    int dc = c+dir[di][1];
    int ddi = di;
    
    int oldSide = getSide(r, c);
    int newSide = getSide(dr, dc);

    if (oldSide != newSide)
    {
        newSide = edge[oldSide][di];
        cout << "From [" << oldSide << "] to [" << newSide << "]" << endl;

        int x = r%EDGE_SIZE;
        int y = c%EDGE_SIZE;

        // Note: key is RC, or (row*10)+col
        switch ((oldSide*10)+newSide)
        {
            case 01: break;

            case 02: break;

            case 03:
                ddi = D_RIGHT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - x - 1);
                dc = (sides[newSide][1] * EDGE_SIZE);
                break;

            case 05:
                ddi = D_RIGHT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (y);
                dc = (sides[newSide][1] * EDGE_SIZE);
                break;

            case 10: break;

            case 12:
                ddi = D_LEFT;
                dr = (sides[newSide][0] * EDGE_SIZE) + y;
                dc = (sides[newSide][1] * EDGE_SIZE) + (EDGE_SIZE - 1);
                break;

            case 14:
                ddi = D_LEFT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - x - 1);
                dc = (sides[newSide][1] * EDGE_SIZE) + (EDGE_SIZE - 1);
                break;

            case 15:
                ddi = D_UP;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - 1);
                dc = (sides[newSide][1] * EDGE_SIZE) + (y);
                break;

            case 20: break;

            case 21:
                ddi = D_UP;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - 1);
                dc = (sides[newSide][1] * EDGE_SIZE) + (x);
                break;

            case 23:
                ddi = D_DOWN;
                dr = (sides[newSide][0] * EDGE_SIZE);
                dc = (sides[newSide][1] * EDGE_SIZE) + (x);
                break;

            case 24: break;

            case 30:
                ddi = D_RIGHT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - x - 1);
                dc = (sides[newSide][1] * EDGE_SIZE);
                break;

            case 32:
                ddi = D_RIGHT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (y);
                dc = (sides[newSide][1] * EDGE_SIZE);
                break;

            case 34: break;

            case 35: break;

            case 41:
                ddi = D_LEFT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - x - 1);
                dc = (sides[newSide][1] * EDGE_SIZE) + (EDGE_SIZE - 1);
                break;

            case 42: break;

            case 43: break;

            case 45:
                ddi = D_LEFT;
                dr = (sides[newSide][0] * EDGE_SIZE) + (y);
                dc = (sides[newSide][1] * EDGE_SIZE) + (EDGE_SIZE - 1);
                break;

            case 50:
                ddi = D_DOWN;
                dr = (sides[newSide][0] * EDGE_SIZE);
                dc = (sides[newSide][1] * EDGE_SIZE) + (x);
                break;

            case 51:
                ddi = D_DOWN;
                dr = (sides[newSide][0] * EDGE_SIZE);
                dc = (sides[newSide][1] * EDGE_SIZE) + (y);
                break;

            case 53: break;

            case 54:
                ddi = D_UP;
                dr = (sides[newSide][0] * EDGE_SIZE) + (EDGE_SIZE - 1);
                dc = (sides[newSide][1] * EDGE_SIZE) + (x);
                break;

            default:
                cout << "FIGURE OUT SIDES" << endl;
                std::_Exit(0);
        }
    }

    NewDir nd; nd.r = dr; nd.c = dc; nd.d = ddi;
    return nd;
}

int main()
{
    string line, directions;
    ifstream input;
    int row = 0, col = 0, di = 0, maxRow = 0;
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
        //cout << dist << endl;

        for (int j = 0; j < dist; j++)
        {
            auto coordWarp = getWarpedCoord(row, col, di);
            int r = coordWarp.r, c = coordWarp.c;

            switch(map[r][c])
            {
                case '.': row = r; col = c; di = coordWarp.d; break;
                case '#': j = dist; break;
                //default: cout << "SOMETHING WENT WRONG" << endl; break;
            }
        }
    }

    cout << "Password: " << ((row+1)*1000) + ((col+1)*4) + (di) << endl;
}
