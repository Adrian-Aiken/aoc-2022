#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define CHECK_ROW 2000000

struct Circle { int x, y, r; };

bool sortPairsByFirst(const pair<int,int> &a, const pair<int,int> &b) { return a.first < b.first; }

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    vector<Circle> beacons;

    while (!input.eof())
    {
        int sx, sy, bx, by;
        getline(input, line, '=');
        getline(input, line, ',');
        sx = stoi(line);
        getline(input, line, '=');
        getline(input, line, ':');
        sy = stoi(line);
        getline(input, line, '=');
        getline(input, line, ',');
        bx = stoi(line);
        getline(input, line, '=');
        getline(input, line     );
        by = stoi(line);

        beacons.push_back(Circle{ sx, sy, abs(sx-bx) + abs(sy-by) });
    }

    // Generate line segments
    vector<pair<int, int>> segments;
    for (Circle b: beacons)
    {
        int offset = b.r - abs(b.y - CHECK_ROW);
        if (offset < 0) continue;

        segments.push_back(pair<int, int>(b.x-offset, b.x+offset));
    }

    sort(segments.begin(), segments.end(), sortPairsByFirst);

    // Merge line segments
    int i = 0;
    while (i < segments.size()-1)
    {
        // If this and next overlap
        if (segments[i].second >= segments[i+1].first)
        {
            // use max to handle case where next segment fully within first segment
            segments[i].second = max(segments[i].second, segments[i+1].second);
            segments.erase(segments.begin()+i+1);
        }
        else i++;
    }

    int sum = 0;
    for (pair<int, int> s: segments)
        sum += s.second - s.first;
    
    cout << "There are [" << sum << "] valid positions" << endl;
}