#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <sstream>
#include <ctime>

using namespace std;

#define MINUTES 32

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

enum BOT_TYPE { NONE = 0, ORE = 1, CLAY = 2, OBSIDIAN = 3, GEODE = 4 };
struct BotState
{
    int oreBots = 1, clayBots = 0, obsBots = 0, geoBots = 0;
    int ore = 0, clay = 0, obs = 0, geo = 0;
    int minutes = 0;
    BOT_TYPE nextBot = NONE;

    string toString(){
        stringstream ss;
        ss << oreBots << '|';
        ss << clayBots << '|';
        ss << obsBots << '|';
        ss << geoBots << '|';
        ss << ore << '|';
        ss << clay << '|';
        ss << obs << '|';
        ss << geo << '|';
        ss << minutes;
        return ss.str();
    }
};

BotState* CopyBot(const BotState& old)
{
    BotState* b = new BotState();
    b->ore = old.ore;
    b->clay = old.clay;
    b->obs = old.obs;
    b->geo = old.geo;
    b->oreBots = old.oreBots;
    b->clayBots = old.clayBots;
    b->obsBots = old.obsBots;
    b->geoBots = old.geoBots;
    b->minutes = old.minutes;
}

inline bool operator<(const BotState& l, const BotState& r)
{
    return l.ore < r.ore
        || l.clay < r.clay
        || l.obs < r.obs
        || l.geo < r.geo
        || l.oreBots < r.oreBots
        || l.clayBots < r.clayBots
        || l.obsBots < r.obsBots
        || l.geoBots < r.obsBots
        || l.nextBot < r.nextBot
        || l.minutes < r.minutes;
}

int main()
{
    string line;
    ifstream input;
    int result = 1, i = 0;
    time_t startTime = time(NULL);

    input.open("input.txt");

    while (!input.eof())
    {
        i++; if (i > 3) break;
        time_t bStartTime = time(NULL);
        getline(input, line);
        auto rawInput = split(line, " ");
        
        int oreCost = stoi(rawInput[6]);
        int clayCost = stoi(rawInput[12]);
        int obsCostO = stoi(rawInput[18]);
        int obsCostC = stoi(rawInput[21]);
        int geoCostO = stoi(rawInput[27]);
        int geoCostOb = stoi(rawInput[30]);

        int maxOreNeeded = max(max(oreCost, clayCost), max(obsCostO, geoCostO));

        queue<BotState*> q;
        q.push(new BotState());

        int maxGeodes = 0, maxMinute = 0;
        set<string> seenStates;
        while (!q.empty())
        {
            BotState* s = q.front(); q.pop();

            // Check end state
            if (s->minutes == MINUTES) continue;

            // Build robot
            switch (s->nextBot)
            {
                case BOT_TYPE::ORE:
                    s->ore -= oreCost;
                    break;

                case BOT_TYPE::CLAY:
                    s->ore -= clayCost;
                    break;

                case BOT_TYPE::OBSIDIAN:
                    s->ore  -= obsCostO;
                    s->clay -= obsCostC;
                    break;

                case BOT_TYPE::GEODE:
                    s->ore -= geoCostO;
                    s->obs -= geoCostOb;
                    break;
            }

            // Collect resources
            s->ore += s->oreBots;
            s->clay += s->clayBots;
            s->obs += s->obsBots;
            s->geo += s->geoBots;

            // Finish building robot
            switch (s->nextBot)
            {
                case BOT_TYPE::ORE:      s->oreBots++;  break;
                case BOT_TYPE::CLAY:     s->clayBots++; break;
                case BOT_TYPE::OBSIDIAN: s->obsBots++;  break;
                case BOT_TYPE::GEODE:    s->geoBots++;  break;
            }

            // If less than max known geodes so far, no point in continuing
            maxGeodes = max(maxGeodes, s->geo);
            if (s->geo < maxGeodes-1) continue;            

            // Prepare next iteration
            s->nextBot = BOT_TYPE::NONE;
            s->minutes++;
            if (seenStates.find(s->toString()) != seenStates.end()) continue;
            seenStates.insert(s->toString());

            /// For each type, see if it makes sense to construct, and add it to the queue if so
            int dt = MINUTES - s->minutes;            
            
            // None - default
            BotState* noneState = CopyBot(*s);
            noneState->nextBot = BOT_TYPE::NONE;
            q.push(noneState);

            // Ore
            if (s->oreBots < maxOreNeeded // If we can gather enough to build a bot each minute
                && ((s->oreBots * dt) + s->ore) < (maxOreNeeded * dt) // If we have enough stores 
                && s->ore >= oreCost) // If we have the resources currently
            {
                BotState* oreState = CopyBot(*s);
                oreState->nextBot = BOT_TYPE::ORE;
                q.push(oreState);
            }

            // Clay
            if (s->clayBots < obsCostC
                && ((s->clayBots * dt) + s->clay) < (obsCostC * dt)
                && s->ore >= clayCost)
            {
                BotState* clayState = CopyBot(*s);
                clayState->nextBot = BOT_TYPE::CLAY;
                q.push(clayState);
            }

            // Obsidian
            if (s->obsBots < geoCostOb
                && ((s->obsBots * dt) + s->obs) < (geoCostOb * dt)
                && s->ore >= obsCostO
                && s->clay >= obsCostC)
            {
                BotState* obsState = CopyBot(*s);
                obsState->nextBot = BOT_TYPE::OBSIDIAN;
                q.push(obsState);
            }

            // Geode
            if (s->ore >= geoCostO
                && s->obs >= geoCostOb) {
                BotState* geoState = CopyBot(*s);
                geoState->nextBot = BOT_TYPE::GEODE;
                q.push(geoState);
            }
        }

        cout << "[" << i << "]: " << maxGeodes << " [" << time(NULL) - bStartTime << "s]" <<endl;
        result *= maxGeodes;
    }
    
    cout << "Result: " << result << endl;
    cout << "[Took: " << time(NULL) - startTime << " seconds]" << endl;
}