#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

bool cellsAdjacent(int x1, int y1, int x2, int y2)
{
    return (abs(x1-x2) <= 1) && (abs(y1-y2) <= 1);
}

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    set<pair<int, int>> visited;
    int hx, hy, tx, ty;
    hx = hy = tx = ty = 0;

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
                case 'R': hy += 1; break;
                case 'L': hy -= 1; break;
                case 'U': hx += 1; break;
                case 'D': hx -= 1; break;
            }

            // Move Tail if necessary
            if (!cellsAdjacent(hx, hy, tx, ty))
            {
                switch (dir)
                {
                    case 'R': tx = hx; ty += 1; break;
                    case 'L': tx = hx; ty -= 1; break;
                    case 'U': ty = hy; tx += 1; break;
                    case 'D': ty = hy; tx -= 1; break;
                }
            }
            visited.insert(pair<int, int>(tx, ty));
        }
    }
    
    cout << "Spaces visited: " << visited.size() << endl;
}