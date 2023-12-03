#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

using namespace std;
using coords = pair<int, int>;

bool is_adjacent(coords const &num, int num_len, coords const &ch)
{
    // Y differing more than one
    if (abs(num.second - ch.second) > 1)
        return false;

    // Symbol Not to the left
    if (num.first - ch.first > 1)
        return false;

    // Symbol Not to the right
    if (ch.first - num.first > num_len)
        return false;

    return true;
}

int main()
{

    ifstream ifs{"input.txt"};

    map<coords, int> numbers;
    map<coords, char> gears;

    int x, y{};
    string line;
    while (getline(ifs, line))
    {
        int curr_number{};
        stringstream ss{line};

        while (x < ss.str().size())
        {
            char c;
            c = ss.peek();
            // Number, make sure to include length of number to coords
            if (isdigit(c))
            {
                ss >> curr_number;
                numbers[make_pair(x, y)] = curr_number;
                x += to_string(curr_number).length();
            }
            // Wierd character
            else if (c == '*')
            {
                ss >> c;
                gears[make_pair(x, y)] = c;
                x += 1;
            }
            // Punct
            else
            {
                ss >> c;
                x += 1;
            }
        }

        y += 1;
        x = 0;
    }

    cout << "NUMBERS\n";
    for (auto const &pair : numbers)
    {
        cout << pair.second << ": " << pair.first.first << " " << pair.first.second << endl;
    }

    cout << "SYMBOLS\n";
    for (auto const &pair : gears)
    {
        cout << pair.second << ": " << pair.first.first << " " << pair.first.second << endl;
    }

    long int sum{};
    for (auto const &char_pair : gears)
    {
        int num_one{-1}, num_two{-1};
        for (auto const &num_pair : numbers)
        {
            if (is_adjacent(num_pair.first, to_string(num_pair.second).size(), char_pair.first))
            {
                if (num_one == -1)
                    num_one = num_pair.second;
                else
                {
                    num_two = num_pair.second;
                    sum += num_one * num_two;
                    break;
                }
            }
        }
    }
    cout << "SUM: " << sum << endl;
    return 0;
}