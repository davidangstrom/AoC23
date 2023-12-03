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
        {"red", -1},
        {"green", -1},
        {"blue", -1}};

    string line, trash;
    int sum{};
    while (getline(ifs, line))
    {
        int id{};
        stringstream ss{line};
        ss >> trash >> id;

        string::size_type pos;

        line = line.substr(line.find(":") + 1);

        map<string, int> cubes_left_temp = cubes_left;
        while (true)
        {
            string curr_line = line.substr(0, line.find(";"));

            ss = stringstream{curr_line};
            string sub_line;
            while (getline(ss, sub_line, ','))
            {
                stringstream ss_sub{sub_line};
                int number;
                string color;

                ss_sub >> number >> color;

                if (cubes_left_temp[color] < number || cubes_left_temp[color] == -1)
                    cubes_left_temp[color] = number;
            }

            if (line.find(";") == string::npos)
                break;
            line = line.substr(line.find(";") + 1);
        }
        cout << cubes_left_temp["red"] << " " << cubes_left_temp["blue"] << " " << cubes_left_temp["green"] << endl;
        sum += (cubes_left_temp["red"] * cubes_left_temp["blue"] * cubes_left_temp["green"]);
    }
    cout << sum << endl;
    return 0;
}