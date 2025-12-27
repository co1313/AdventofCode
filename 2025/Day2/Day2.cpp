#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>
#include <filesystem>

using instructies = std::vector<std::string>;

instructies input(const std::string &filename)
{
    std::cout << std::filesystem::current_path() << '\n';
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    instructies ranges;
    std::string token;

    while (std::getline(in, token, ','))
    {
        ranges.push_back(token);
    }

    return ranges;
}

int main()
{

    // Print
    auto instructies = input("input/input");
    std::cout << "Read " << instructies.size() << " instructions\n";

    for (const auto &s : instructies)
    {
        std::cout << s << std::endl;
    }
    // int answer1 = part1(instructies);
    // std::cout << answer1 << std::endl;

    // int answer2 = part2(instructies);
    // std::cout << answer2 << " keer langs 0 gekomen" << std::endl;
    return 0;
}