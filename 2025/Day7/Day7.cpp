#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>

using Strings = std::vector<std::string>;
using Ints = std::vector<int>;

// Read input lines from a file
Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings lines;
    for (std::string line; std::getline(in, line);)
        lines.push_back(line);

    return lines;
}

Ints adjust_row(const Ints &previous_beam_positions, std::string &row, int &split_count)
{
    Ints beam_postions;
    for (const auto &beam : previous_beam_positions)
    {
        if (row[beam] == '|')
        {
            continue;
        }

        if (row[beam] == '.')
        {
            row[beam] = '|';
            beam_postions.push_back(beam);
        }
        else if (row[beam] == '^')
        {
            ++split_count;
            if (beam > 0)
            {
                row[beam - 1] = '|';
                if (beam_postions.empty() || beam_postions.back() != beam - 1)
                {
                    beam_postions.push_back(beam - 1);
                }
            }
            if (beam < row.size() - 1)
            {
                row[beam + 1] = '|';
                beam_postions.push_back(beam + 1);
            }
        }
    }
    return beam_postions;
}

int part1(const Strings &lines)
{
    int split_count = 0;
    Strings manifold = lines;
    Ints beam_positions;
    beam_positions.push_back(lines[0].find("S"));
    for (size_t row = 1; row < manifold.size(); ++row)
    {
        beam_positions = adjust_row(beam_positions, manifold[row], split_count);
        for (const auto &s : manifold)
            std::cout << s << std::endl;
    }
    return split_count;
}
int main()
{
    // Print
    const auto input = read_input("input/input");

    // for (const auto &s : input)
    //     std::cout << s << std::endl;

    std::cout << "Part 1: " << part1(input) << "\n";
    // std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}