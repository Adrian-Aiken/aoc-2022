#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define ROOT_MONKEY "root"
#define HUM_MONKEY "humn"

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

bool HasHuman(string name)
{
    Monkey m = bunch[name];

    if (name == HUM_MONKEY) return true;
    if (m.answer != -1) return false;
    if (m.left == HUM_MONKEY || m.right == HUM_MONKEY) return true;

    return HasHuman(m.left) || HasHuman(m.right);
}

int64_t GetMonkeyNumber(string name)
{
    Monkey m = bunch[name];
    if (m.answer != -1) return m.answer;

    int64_t l = GetMonkeyNumber(m.left);
    int64_t r = GetMonkeyNumber(m.right);

    switch(m.operation)
    {
        case '+': m.answer = l + r; break;
        case '-': m.answer = l - r; break;
        case '*': m.answer = l * r; break;
        case '/': m.answer = l / r; break;
    }

    return m.answer;
}

int64_t GetHumanNumber(string name, int64_t target)
{
    if (name == HUM_MONKEY) return target;

    Monkey m = bunch[name];
    string known = m.left;
    string unknown = m.right;
    bool swapped;
    if (HasHuman(m.left)) { swapped = true; swap(known, unknown); };
    
    int64_t pair = GetMonkeyNumber(known);
    int64_t newTarget;
    switch(m.operation)
    {
        case '+': newTarget = target - pair; break;
        case '-': newTarget = swapped ? target + pair : -1*(target - pair); break;
        case '*': newTarget = target / pair; break;
        case '/': newTarget = swapped ? target * pair : pair / target; break;
    }

    return GetHumanNumber(unknown, newTarget);
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

    string known = bunch[ROOT_MONKEY].left;
    string unknown = bunch[ROOT_MONKEY].right;
    if (HasHuman(bunch[ROOT_MONKEY].left)) swap(known, unknown);

    int64_t target = GetMonkeyNumber(known);
    int64_t humanNum = GetHumanNumber(unknown, target);

    // Check work
    bunch[HUM_MONKEY].answer = humanNum;
    cout << "Left: " << GetMonkeyNumber(bunch[ROOT_MONKEY].left) << endl;
    cout << "Right: " << GetMonkeyNumber(bunch[ROOT_MONKEY].right) << endl;
    
    cout << "HUMAN: " << humanNum << endl;
}