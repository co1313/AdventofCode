#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>
#include <filesystem>
#include <cmath>

using Strings = std::vector<std::string>;
using Longs = std::vector<long>;

Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings ranges;
    for (std::string s; std::getline(in, s, ',');)
        ranges.push_back(s);

    return ranges;
}

Longs numbers(const Strings &ranges)
{
    Longs IDs;

    for (const auto &s : ranges)
    {
        auto dashPos = s.find('-');
        if (dashPos == std::string::npos)
            continue;

        long begin = std::stol(s.substr(0, dashPos));
        long end = std::stol(s.substr(dashPos + 1));

        for (long i = begin; i <= end; ++i)
            IDs.push_back(i);
    }
    return IDs;
}

long part1(const Longs &IDs)
{
    long IDsum = 0;
    for (size_t i = 0; i < IDs.size(); i++)
    {
        int digits = std::to_string(IDs[i]).length();

        if (digits % 2 == 0 and IDs[i] % (long)(std::pow(10, digits / 2) + 1) == 0)
            IDsum += IDs[i];
    }
    return IDsum;
}

Longs divisors(int n)
{
    Longs res;

    for (int i = 2; i <= n; i++)
        if (n % i == 0)
            res.push_back(i);
    return res;
}
long make_divisor(int digits, long factor)
{
    long divisor = 0;
    int step = digits / factor;

    for (int i = 0; i < factor; i++)
        divisor += static_cast<long>(std::pow(10, i * step));

    return divisor;
}

long part2(const Longs &IDs)
{
    long IDsum = 0;
    for (long ID : IDs)
    {
        int digits = std::to_string(ID).length();

        for (long factor : divisors(digits))
        {
            if (ID % make_divisor(digits, factor) == 0)
            {
                IDsum += ID;
                // std::cout << "counted ID:" << IDs[i] << std::endl;
                break; // stop after first match
            }
        }
    }
    return IDsum;
}

int main()
{

    // Print
    auto instructies = numbers(read_input("input/input"));
    // std::cout << "Read " << instructies.size() << " instructions\n";

    // for (const auto &s : instructies)
    //     std::cout << s << std::endl;

    long answer1 = part1(instructies);
    std::cout << "Part 1: " << answer1 << std::endl;

    long answer2 = part2(instructies);
    std::cout << "Part 2: " << answer2 << std::endl;
    return 0;
}