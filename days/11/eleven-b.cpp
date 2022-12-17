#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>

#define MONKEY_ROUNDS 10000

using namespace std;

struct Monkey
{
    deque<long long>* items;
    char operand;
    int numerand, divTest, trueTarget, falseTarget, inspections = 0;
};

int main()
{
    string line, word;
    ifstream input;

    input.open("input.txt");

    vector<Monkey*> bunch;
    long long bigDiv = 1;

    // Parse input
    while (!input.eof())
    {
        Monkey* m = new Monkey();
        m->items = new deque<long long>();
        getline(input, line); // Monkey N:

        getline(input, line); //   Starting items: N, N, N...
        stringstream ss(line.substr(18));
        while (!ss.eof()) {
            getline(ss, word, ',');
            m->items->push_back(stoi(word));
        }

        getline(input, line); //   Operation: new = old [operand] [numerand]
        m->operand = line[23];
        m->numerand = line[25] == 'o' ? -1 : stoi(line.substr(25)); // o = old, otherwise positive integer

        getline(input, line); //   Test: divisible by N
        m->divTest = stoi(line.substr(21));
        bigDiv *= m->divTest;

        getline(input, line); //     If true: throw to monkey N
        m->trueTarget = stoi(line.substr(29));

        getline(input, line); //     If false: throw to monkey N
        m->falseTarget = stoi(line.substr(30));

        bunch.push_back(m);

        // Correction for newline between monkeys
        if (!input.eof()) getline(input, line); 
    }

    // Do monkey buisness
    for (int round = 0; round < MONKEY_ROUNDS; round++)
    {
        for (int i = 0; i < bunch.size(); i++)
        while (bunch[i]->items->size() > 0)
        {
            Monkey* m = bunch[i];
            long long item = m->items->at(0);
            m->items->pop_front();

            int numerand = (m->numerand == -1) ? item : m->numerand;
            switch (m->operand)
            {
                case '+': item += numerand; break;
                case '*': item *= numerand; break;
            }

            item %= bigDiv;
            int target = item % m->divTest == 0 ? m->trueTarget : m->falseTarget;
            bunch[target]->items->push_back(item);

            m->inspections++;
        }
    }
    
    vector<long long> output;
    for (int i = 0; i < bunch.size(); i++)
    {
        cout << "Monkey " << i << ": " << bunch[i]->inspections << endl;
        output.push_back(bunch[i]->inspections);
    }

    sort(output.begin(), output.end(), greater<long long>());
    cout << endl << "Monkey Buisness: " << output[0]*output[1] << endl;
}