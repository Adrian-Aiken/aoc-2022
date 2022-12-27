#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string line;
    ifstream input;
    int64_t total = 0;

    input.open("input.txt");

    cout << " SNAFU  Decimal" << endl;

    // Parse into numbers
    while (!input.eof())
    {
        int64_t n = 0;
        getline(input, line);

        for (char c: line)
        {
            n *= 5;
            switch(c)
            {
                case '0': break;
                case '1': n += 1; break;
                case '2': n += 2; break;
                case '-': n -= 1; break;
                case '=': n -= 2; break;
            }
        }

        total += n;
    }

    cout << endl << "Total: " << total;

    // Convert back to the strange fuel numbers
    string s;
    while (total > 0)
    {
        switch (((total+2)%5)-2)
        {
            case -2: s.insert(s.begin(), '='); total += 2; break;
            case -1: s.insert(s.begin(), '-'); total += 1; break;
            case  0: s.insert(s.begin(), '0');             break;
            case  1: s.insert(s.begin(), '1'); total -= 1; break;
            case  2: s.insert(s.begin(), '2'); total -= 2; break;
        }
        total /= 5;
    }

    cout << "[" << s << "]" << endl;
}