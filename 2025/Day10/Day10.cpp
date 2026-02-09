#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct Machine
{
    std::string indicator;
    std::vector<std::set<int>> buttons;
    std::string joltage;
};

Machine decode_manual(std::string line)
{
    Machine M;
    auto pos = line.find("]");
    M.indicator = line.substr(0, pos);
    line.erase(0, pos + 1);
    // build the rest of the machine

    return M;
}

std::vector<std::string> read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    std::vector<std::string> lines;
    for (std::string line; std::getline(in, line);)
        lines.push_back(line);

    return lines;
}
int part1(const std::vector<std::string> &lines)
{
    int result = 0;
    for (auto line : lines)
    {
        Machine m = decode_manual(line);
    }
}
