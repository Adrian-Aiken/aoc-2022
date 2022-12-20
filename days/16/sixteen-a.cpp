#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

#define START_VALVE "AA"
#define START_TIME 30

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

struct Valve
{
    string name;
    int flowRate;
    vector<string> neighbors;    
    bool open = false;
};

struct ActionStep
{
    string curNode;
    set<string> opened;
    int timeRemaining, pressureReleased;

    string toString() const
    { 
        ostringstream ss;
        ss << curNode << timeRemaining << ":" << pressureReleased;
        for (string s: opened) ss << s;
        return ss.str();
    }
};

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    map<string, Valve> maze;
    queue<ActionStep> searchQueue;
    set<string> states;
    int openable = 0, maxFlow = 0;

    while (!input.eof())
    {
        getline(input, line, ';');
        string name = line.substr(6, 2);
        int rate = stoi(line.substr(23));
        if (rate > 0) openable++;
        getline(input, line);
        // Fix for "tunnel/tunnels" issue
        int delimIndex = line.find("tunnels") == string::npos ? 23 : 24;
        vector<string> neighbors = split(line.substr(delimIndex), ", ");

        maze[name] = Valve { name, rate, neighbors };
    }

    // Initialize queue
    searchQueue.push(ActionStep { START_VALVE, set<string>(), START_TIME, 0 });

    map<string, int> distMemo;
    auto getDist = [&](string start, string end)
    {
        if (start == end) return 0;
        if (distMemo.find(start+end) != distMemo.end()) return distMemo[start+end];

        queue<pair<string, int>> distQueue;
        distQueue.push(pair<string, int>(maze[start].name, 0));
        set<string> visited;
        visited.insert(start);
        while (!distQueue.empty())
        {
            pair<string, int> curSpot = distQueue.front(); distQueue.pop();
            for (string neighbor: maze[curSpot.first].neighbors)
            {
                if (visited.find(neighbor) != visited.end()) continue;
                visited.insert(neighbor);
                if (neighbor == end)
                {
                    distMemo[start+end] = curSpot.second+1;
                    return curSpot.second+1;
                }
                distQueue.push(pair<string, int>(neighbor, curSpot.second+1));
            }
        }
        return INT_MAX;
    };

    while (!searchQueue.empty())
    {
        ActionStep curStep = searchQueue.front(); searchQueue.pop();

        // Visit all unopened valves
        for (pair<string, Valve> tPair: maze)
        {
            Valve target = tPair.second;
            if (target.name == curStep.curNode) continue;
            if (target.flowRate > 0 && curStep.opened.find(target.name) == curStep.opened.end())
            {
                int dist = getDist(curStep.curNode, target.name);
                if (dist >= curStep.timeRemaining) continue;

                ActionStep newStep;
                newStep.curNode = target.name;
                newStep.timeRemaining = curStep.timeRemaining - (dist + 1);
                newStep.pressureReleased = curStep.pressureReleased + (target.flowRate * newStep.timeRemaining);
                newStep.opened = set<string>(curStep.opened);
                newStep.opened.insert(target.name);
                searchQueue.push(newStep);

                maxFlow = max(maxFlow, newStep.pressureReleased);
            }
        }
    }
    
    cout << "Max Pressure Released: " << maxFlow << endl;
}
