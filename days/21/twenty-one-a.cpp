#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define ROOT_MONKEY "root"

struct Monkey;
map<string, Monkey> bunch;

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

struct Monkey {
    int64_t answer;
    char operation;
    string left, right;
};

int64_t GetMonkeyNumber(string name)
{
    Monkey m = bunch[name];
    if (m.answer != -1) return m.answer;

    int64_t l = GetMonkeyNumber(m.left);
    int64_t r = GetMonkeyNumber(m.right);

    int64_t result;
    switch(m.operation)
    {
        case '+': result = l + r; break;
        case '-': result = l - r; break;
        case '*': result = l * r; break;
        case '/': result = l / r; break;
    }

    return result;
}

int main()
{
    string line;
    ifstream input;

    input.open("input.txt");

    // Parse input
    while (!input.eof())
    {
        string name;
        Monkey monkey;        
        getline(input, name, ':');
        getline(input, line);

        // Number monkey
        if (line[1] < 'a')
        {
            monkey.answer = stoi(line);
        }
        // Math monkey
        else
        {
            auto s = split(line, " ");
            monkey.left = s[1];
            monkey.operation = s[2][0];
            monkey.right = s[3];
            monkey.answer = -1;
        }

        bunch[name] = monkey;
    }

    int64_t result = GetMonkeyNumber(ROOT_MONKEY);
    
    cout << "MONKEE: " << result << endl;
}