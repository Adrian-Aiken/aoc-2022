#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

#define UP_LIMIT 1

using namespace std;

struct PathPoint
{
    public:
    int x, y, length;
    PathPoint(int x, int y, int length) { this->x = x; this->y = y; this->length = length; }
};

class PathComparitor
{
    public:
    int operator() (const PathPoint& p1, const PathPoint& p2)
    {
        return p1.length > p2.length;
    }
};

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    vector<string> map;
    vector<pair<int, int>> starts;
    pair<int, int> end;
    vector<int> pathLengths;

    // Parse input
    int row = 0;
    while (!input.eof())
    {
        getline(input, line);

        // Find starts
        for (int i = 0; i < line.length(); i++)
            if (line[i] == 'S' || line[i] == 'a')
                starts.push_back(pair<int, int>(row, i));

        int ePos = line.find('E');
        if (ePos != string::npos) end = pair<int, int>(row, ePos);

        map.push_back(line);

        row++;
    }

    for (pair<int, int> start : starts)
    {
        priority_queue<PathPoint, vector<PathPoint>, PathComparitor> queue;
        set<pair<int, int>> visited;

        queue.push(PathPoint(start.first, start.second, 0));
        visited.insert(start);

        auto canClimb = [&](int x, int y, char c)
        {
            if (x < 0 || x >= map.size()) return false;
            if (y < 0 || y >= map[0].size()) return false;

            if (visited.find(pair<int, int>(x, y)) != visited.end()) return false;

            if (c == 'S') c = 'a';
            if (c == 'E') c = 'z';
            char t = map[x][y] == 'E' ? 'z' : map[x][y];

            return (t - c) <= UP_LIMIT;
        };

        while (queue.size() > 0)
        {
            PathPoint p = queue.top(); queue.pop();

            if (pair<int, int>(p.x, p.y) == end)
            {
                pathLengths.push_back(p.length);
                break;    
            }

            // Test down
            if (canClimb(p.x+1, p.y, map[p.x][p.y]))
            {
                visited.insert(pair<int, int>(p.x+1, p.y));
                queue.push(PathPoint(p.x+1, p.y, p.length+1));
            }

            // Test up
            if (canClimb(p.x-1, p.y, map[p.x][p.y]))
            {
                visited.insert(pair<int, int>(p.x-1, p.y));
                queue.push(PathPoint(p.x-1, p.y, p.length+1));
            }

            // Test right
            if (canClimb(p.x, p.y+1, map[p.x][p.y]))
            {
                visited.insert(pair<int, int>(p.x, p.y+1));
                queue.push(PathPoint(p.x, p.y+1, p.length+1));
            }

            // Test right
            if (canClimb(p.x, p.y-1, map[p.x][p.y]))
            {
                visited.insert(pair<int, int>(p.x, p.y-1));
                queue.push(PathPoint(p.x, p.y-1, p.length+1));
            }
        }            
    }

    sort(pathLengths.begin(), pathLengths.end());
    cout << "Shortest path: " << pathLengths[0] << endl;
}