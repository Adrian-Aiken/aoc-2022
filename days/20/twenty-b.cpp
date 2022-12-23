#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define WIND_COUNT 1000
#define DECRYPT_KEY 811589153
#define ITERATIONS 10

struct Node
{
    int64_t value;
    uint32_t order;
    Node *next, *last;
};

int main()
{
    string line;
    ifstream input;
    Node *first, *previous;
    int count = 0;

    input.open("input.txt");

    getline(input, line);
    first = new Node();   
    first->order = count++;
    first->value = stoi(line);
    first->value *= DECRYPT_KEY;

    previous = first;
    while (!input.eof())
    {
        getline(input, line);

        Node* next = new Node();
        next->order = count++;
        next->value = stoi(line);
        next->value *= DECRYPT_KEY;
        next->last = previous;
        previous->next = next;

        previous = next;
    }

    previous->next = first;
    first->last = previous;

    for (int z = 0; z < ITERATIONS; z++)
    for (int i = 0; i < count; i++)
    {
        // Find element for current index
        Node *cur = first;
        while (cur->order != i)
        {
            cur = cur->next;
        }

        if (cur->value > 0)
            for (int j = cur->value % (count-1); j > 0; j--)
            {
                swap(cur->value, cur->next->value);
                swap(cur->order, cur->next->order);
                cur = cur->next;
            }

        else if (cur->value < 0)
            for (int j = cur->value % (count-1); j < 0; j++)
            {
                swap(cur->value, cur->last->value);
                swap(cur->order, cur->last->order);
                cur = cur->last;
            }
    }

    // Find zero node
    Node *cur = first;
    while (cur->value != 0) cur = cur->next;

    int64_t coordSum = 0;
    for (int i = 0; i < WIND_COUNT; i++) cur = cur->next;
    coordSum += cur->value; cout << cur->value << " ";
    for (int i = 0; i < WIND_COUNT; i++) cur = cur->next;
    coordSum += cur->value; cout << cur->value << " ";
    for (int i = 0; i < WIND_COUNT; i++) cur = cur->next;
    coordSum += cur->value; cout << cur->value << " " << endl;

    cout << "Coordinate sum: " << coordSum << endl;
} 