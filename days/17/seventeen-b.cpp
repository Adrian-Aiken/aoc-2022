#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

#define NEW_ROOM "......."
#define NEW_SPACE 3
#define START_COL 2

void printRoom(vector<string> room)
{
    for (auto iter = room.rbegin(); iter != room.rend(); iter++) cout << '|' << *iter << '|' << endl;
    cout << "+-------+" << endl << endl;
}

int clearanceNeeded(vector<string> room)
{
    int i = NEW_SPACE;
    auto iter = room.rbegin();
    while (iter != room.rend() && *iter == NEW_ROOM) { i--; iter++; }
    return i;
}

int main()
{
    string jets;
    ifstream input;
    vector<string> room;
    vector<vector<string>> pieces;
    pieces.push_back(vector<string>({ "####" }));
    pieces.push_back(vector<string>({ ".#.", "###", ".#." }));
    pieces.push_back(vector<string>({ "###", "..#", "..#" }));
    pieces.push_back(vector<string>({ "#", "#", "#", "#" }));
    pieces.push_back(vector<string>({ "##", "##" }));
    int jetIndex = 0, nextPiece = 0;    
    uint64_t remaining = 1000000000000, cycleStart;
    set<pair<int, int>> seenCombo;

    input.open("input.txt");
    getline(input, jets);

    int pastResult = 0;
    bool inCycle = false, finishing = false;
    pair<int, int> cycle;
    uint64_t height;
    for (; remaining > 0; remaining--)
    {
        int clearance = clearanceNeeded(room);
        
        // Adjust to 3 clear rows
        if (clearance > 0) 
            for (int i = 0; i < clearance; i++) room.push_back(NEW_ROOM);
        else if (clearance < 0)
            for (int i = clearance; i < 0; i++) room.pop_back();
            

        // Full cycle found, start computing end state!!
        if (inCycle && !finishing && nextPiece == cycle.first && jetIndex == cycle.second)
        {
            uint64_t cycleHeight = room.size() - pastResult;
            uint64_t cycleLength = cycleStart - remaining;
            cout << "Cycle: [" << cycleHeight << "," << cycleLength << "] " << remaining << endl;

            height = cycleHeight * (remaining/cycleLength);
            remaining %= cycleLength;
            finishing = true;

            remaining += 1;
            continue;
        }

        // Mark known cycle
        if (!inCycle && !seenCombo.emplace(pair<int, int>(nextPiece, jetIndex)).second)
        {
            inCycle = true;
            cycle = pair<int, int>(nextPiece, jetIndex);
            pastResult = room.size();
            cycleStart = remaining;
            cout << "FOUND AN ITERATION" << endl;
        }
        
        vector<string> piece = pieces[nextPiece];        
        nextPiece = (nextPiece + 1) % pieces.size();

        // Add rows for new piece
        for (int i = 0; i < piece.size(); i++) room.push_back(NEW_ROOM);
            
        string bottom = piece.front();
        int row = room.size()-piece.size(), col = START_COL;   

        // Piece falling
        bool fall = false;
        while (true)
        {
            if (fall)
            {
                // Hit bottom; done falling
                if (row <= 0) break;

                // Test below
                bool collision = false;
                for (int r = 0; r < piece.size(); r++)
                for (int c = 0; c < bottom.size(); c++)
                    if (piece[r][c] == '#' && room[row+r-1][col+c] == '#')
                        collision = true;

                if (collision) break;
                row--;
            }
            else
            {
                // Move via jet
                bool collide = false;
                int dir = 0;
                switch (jets[jetIndex++])
                {
                    case '<': 
                        if (col-1 >= 0) dir = -1;
                        break;

                    case '>':
                        if (col+bottom.size() < room[0].size()) dir = 1;
                        break;
                }
                jetIndex %= jets.size();
                if (dir != 0)
                {
                    for (int r = 0; r < piece.size(); r++)
                    for (int c = 0; c < bottom.size(); c++)
                        if (piece[r][c] == '#' && room[row+r][col+c+dir] == '#')
                            collide = true;

                    if (!collide) col += dir;
                }
            }
            fall = !fall;
        }

        // Commit piece to board
        for (int r = 0; r < piece.size(); r++)
        for (char c = 0; c < piece[r].size(); c++)
        {
            if (piece[r][c] == '.') continue;
            room[row+r][col+c] = '#';
        }
    }

    // Remove final bit of empty space at the top
    while (*room.rbegin() == NEW_ROOM) room.pop_back();
    
    cout << endl << "Final height: " << room.size() + height << endl;
}