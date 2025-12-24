#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>

using instructies = std::vector<std::string>;

instructies input(std::string filename)
{

    instructies ranges;

    if (std::ifstream in{filename + ".txt"})
    {
        std::string token;
        while (std::getline(in, token, ','))
        {
            ranges.push_back(token);
        }
    }
    return ranges;
}

int main()
{

    // Print
    auto instructies = input("testinput");

    for (const auto &s : instructies)
    {
        std::cout << s << std::endl;
    }
    // int answer1 = part1(instructies);
    //std::cout << answer1 << std::endl;

    // int answer2 = part2(instructies);
    // std::cout << answer2 << " keer langs 0 gekomen" << std::endl;
    return 0;
}