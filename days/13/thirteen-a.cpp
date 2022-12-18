#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PacketList {
    public:    
        enum Type { Number, List } type;
        int num;
        vector<PacketList> items;

        PacketList(int n) { type = Number; num = n; }
        PacketList(string s)
        {
            type = List;

            // Strip outermost brackets
            s = s.substr(1, s.size()-2);
            int i = 0;

            while (i < s.size())
            {
                switch(s[i])
                {                    
                    // Somehow a comma, just move on
                    case ',': i++; break;

                    // If list, find matching close bracket and call recursively
                    case '[': 
                    {
                        int bracketCount = 1, j = i + 1;
                        while (bracketCount > 0)
                        {
                            switch (s[j++])
                            {
                                case '[': bracketCount++; continue;
                                case ']': bracketCount--; continue;
                            }
                        }
                        items.push_back(PacketList(s.substr(i, j-i)));
                        i = j+1;
                        break;
                    }

                    // Assumed digit
                    default:
                        {
                            int t = 0;
                            while (i < s.size() && s[i] != ',')
                            {
                                t *= 10;
                                t += s[i] - '0';
                                i++;
                            }
                            items.push_back(PacketList(t));
                            i++;
                            break;
                        }
                }
            }
        }

        void convert() { 
            if (type == List) return;
            type = List;
            items.push_back(PacketList(num));
        }
};

// -1 == false, 1 == true, 0 == continue
int Compare (PacketList left, PacketList right)
{
    int i = 0;
    while(i < left.items.size())
    {
        if (right.items.size() <= i) return -1;

        PacketList l = left.items[i];
        PacketList r = right.items[i];

        // Convert number to list, if necessary
        if (l.type != r.type) { l.convert(); r.convert(); }

        switch (l.type)
        {
            case PacketList::Type::Number:
                if (l.num < r.num) return 1;
                if (l.num > r.num) return -1;
                i++;
                continue;

            case PacketList::Type::List:
                {
                    int result = Compare(l, r);
                    if (result > 0) return 1;
                    if (result < 0) return -1;
                    i++;
                    continue;
                }
        }
    }

    if (left.items.size() < right.items.size()) return 1;
    return 0;
}

int main()
{
    string leftString, rightString, _;
    ifstream input;

    input.open("input.txt");

    int i = 1, goodSum = 0;
    while (!input.eof())
    {
        getline(input, leftString);
        getline(input, rightString);
        if (!input.eof()) getline(input, _); // Blank line toss

        PacketList left = PacketList(leftString);
        PacketList right = PacketList(rightString);

        //cout << "Packet " << i << " is " << result << endl;
        if (Compare(left, right) == 1) goodSum += i;
        i++;
    }
    
    cout << "Output: " << goodSum << endl;
}