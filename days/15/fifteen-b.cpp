#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define RANGE_MAX 4000000

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

    for (int row = 0; row < RANGE_MAX; row++)
    {
        // Generate line segments
        vector<pair<int, int>> segments;
        for (Circle b: beacons)
        {
            int offset = b.r - abs(b.y - row);
            if (offset < 0) continue;

            int smin = max(b.x-offset, 0);
            int smax = min(b.x+offset, RANGE_MAX);

            segments.push_back(pair<int, int>(smin, smax));
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

        // Check end condition
        if (segments.size() > 1)
        {
            int64_t x = segments[0].second+1;
            int64_t frequency = x * RANGE_MAX;
            frequency += row;
            cout << "Found coordinates [" << x << "," << row << "]" << endl;
            cout << " Tuning frequency: " << frequency << endl;
            return 0;
        }
    }

    cout << "No answer found" << endl;
}