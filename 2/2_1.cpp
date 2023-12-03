#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    ifstream ifs{"input.txt"};

    map<string, int> cubes_left = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}};

    string line, trash;
    int sum{};
    while (getline(ifs, line))
    {
        int id{};
        stringstream ss{line};
        ss >> trash >> id;

        string::size_type pos;

        line = line.substr(line.find(":") + 1);
        bool impossible{false};

        while (true)
        {
            map<string, int> cubes_left_temp = cubes_left;

            string curr_line = line.substr(0, line.find(";"));

            ss = stringstream{curr_line};
            string sub_line;
            while (getline(ss, sub_line, ','))
            {
                stringstream ss_sub{sub_line};
                int number;
                string color;

                ss_sub >> number >> color;

                cubes_left_temp[color] -= number;
            }

            for (auto const &pair : cubes_left_temp)
            {
                if (pair.second < 0)
                {
                    cout << "weee\n";
                    impossible = true;
                    break;
                }
            }

            if (line.find(";") == string::npos)
                break;
            line = line.substr(line.find(";") + 1);
        }
        if (!impossible)
            sum += id;
    }
    cout << sum << endl;
    return 0;
}