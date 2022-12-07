#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define MAX_DIR_SIZE 100000

struct File {
    string name;
    int64_t size;
    File(string, int64_t);
};
File::File(string name, int64_t size) { this->name = name; this->size = size; }

struct Dir {
    string name;
    Dir* parent;
    map<string, Dir*> subDirs;
    vector<File*> files;
    Dir(string, Dir*);
};
Dir::Dir(string name, Dir* parent) { this->name = name; this->parent = parent; }

int64_t calculateSize(Dir dir)
{
    int64_t size = 0;
    for (File* f: dir.files) size += f->size;
    for (pair<string, Dir*> d: dir.subDirs) size += calculateSize(*d.second);
    return size;
};

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    Dir* rootDir = new Dir("/", NULL);
    Dir* currentDir = rootDir;

    while (!input.eof())
    {
        getline(input, line);

        switch(line[0])
        {
            case '$':
                {
                    if (line == "$ ls") break;
                    
                    if (line == "$ cd ..") 
                    {
                        currentDir = currentDir->parent;
                        break; // Handle going up one
                    }

                    if (line == "$ cd /")
                    {
                        currentDir = rootDir;
                        break;
                    }

                    currentDir = currentDir->subDirs[line.substr(5)];
                    break;
                }

            case 'd':
                {
                    Dir* newDir = new Dir(line.substr(4), currentDir);
                    currentDir->subDirs[newDir->name] = newDir;
                    break;
                }

            default: // Assumed file
                {
                    int split = line.find(" ");
                    File* newFile = new File(line.substr(split+1), stoi(line.substr(0, split)));
                    currentDir->files.push_back(newFile);
                    break;
                }
        }
    }
    
    int64_t totalSum = 0;
    queue<Dir*> dirs;
    dirs.push(rootDir);

    while (dirs.size() > 0)
    {
        Dir* dir = dirs.front();
        dirs.pop();

        for (pair<string, Dir*> d: dir->subDirs) dirs.push(d.second);
        int64_t dirSize = calculateSize(*dir);
        cout << "["<< dir->name << "] " << dirSize;
        if (dirSize <= MAX_DIR_SIZE)
        {
            totalSum += dirSize;
            cout << " - ADDED";
        }
        cout << endl;
    }

    cout << "-----------------------" << endl << "Directory sum: " << totalSum << endl;
}