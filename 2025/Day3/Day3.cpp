#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

using Strings = std::vector<std::string>;
using Longs = std::vector<long>;

Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings ranges;
    for (std::string s; std::getline(in, s);)
        ranges.push_back(s);

    return ranges;
}

struct Result
{
    int position;
    int value;
};

Result find_position(const std::string &s)
{
    Result r{0, s[0] - '0'};

    for (int i = 1; i < (int)s.size(); ++i)
    {
        int digit = s[i] - '0';
        if (digit > r.value)
        {
            r.value = digit;
            r.position = i;
        }
    }
    return r;
}

int part1(const Strings &input)
{
    int totaloutputjoltage = 0;
    for (const std::string &bank : input)
    {
        auto [pos, jolts] = find_position(bank.substr(0, bank.size() - 1));
        jolts = jolts * 10 + find_position(bank.substr(pos + 1)).value;
        std::cout << jolts << std::endl;
        totaloutputjoltage += jolts;
    }

    return totaloutputjoltage;
}

int main()
{
    // Print
    auto instructions = read_input("input/testinput");
    for (const auto &s : instructions)
        std::cout << s << std::endl;

    int answer1 = part1(instructions);
    std::cout << "Part 1: " << answer1 << std::endl;

    // long answer2 = part2(instructions);
    // std::cout << "Part 2: " << answer2 << std::endl;
    return 0;
}