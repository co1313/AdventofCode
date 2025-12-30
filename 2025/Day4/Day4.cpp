#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>
#include <array>

using Strings = std::vector<std::string>;
using Booleans = std::vector<std::vector<bool>>;
using Ints = std::vector<std::vector<int>>;

Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings lines;
    std::string s;
    while (std::getline(in, s))
    {
        if (!s.empty())
            lines.push_back(s);
    }

    return lines;
}
Booleans find_at(const Strings &instructions)
{
    Booleans rolls;

    for (const auto &str : instructions)
    {
        std::vector<bool> row;
        for (char c : str)
        {
            row.push_back(c == '@');
        }
        rolls.push_back(row);
    }

    return rolls;
}

Ints find_adjacent(const Booleans &rolls)
{
    size_t rows = rolls.size();
    size_t columns = rolls[0].size();

    Ints adjacent(rows, std::vector<int>(columns, 0));
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            int sum = 0;
            for (int ii = -1; ii <= 1; ++ii)
            {
                for (int jj = -1; jj <= 1; ++jj)
                {
                    if (ii == 0 && jj == 0)
                        continue;
                    int ni = ii + static_cast<int>(i);
                    int nj = jj + static_cast<int>(j);
                    if (ni >= 0 && nj >= 0 && ni < static_cast<int>(rows) && nj < static_cast<int>(columns))
                        sum += rolls[ni][nj];
                }
            }
            adjacent[i][j] = sum;
        }
    }
    return adjacent;
}

int part1(const Ints &adj_rolls, const Booleans &rolls)
{
    int result = 0;
    for (size_t i = 0; i < rolls.size(); ++i)
    {
        for (size_t j = 0; j < rolls[i].size(); ++j)
        {
            if (adj_rolls[i][j] < 4 && rolls[i][j])
                ++result;
        }
    }
    return result;
}

int main()
{
    // Print
    auto instructions = read_input("input/testinput");
    // for (const auto &s : instructions)
    //     std::cout << s << std::endl;
    int answer1 = part1(find_adjacent(find_at(instructions)), find_at(instructions));
    std::cout << "Part 1: " << answer1 << std::endl;

    // long answer2 = part2(instructions);
    // std::cout << "Part 2: " << answer2 << std::endl;
    return 0;
}