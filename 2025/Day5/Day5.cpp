#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>

struct Range
{
    long min;
    long max;
};

using Strings = std::vector<std::string>;
using Longs = std::vector<long>;
using Ranges = std::vector<Range>;

// Read input lines from a file with space between
Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings lines;
    for (std::string line; std::getline(in, line);)
        lines.push_back(line);

    return lines;
}

// Convert stringranges into long array with begin/end of range in every row
Ranges build_ranges(const Strings &rangelines)
{
    Ranges ranges;

    for (const auto &str : rangelines)
    {
        auto dash = str.find('-');
        assert(dash != std::string::npos);

        ranges.push_back({std::stol(str.substr(0, dash)),
                          std::stol(str.substr(dash + 1))});
    }
    return ranges;
}

int part1(const Strings &lines)
{
    auto emptyline = std::find(lines.begin(), lines.end(), "");
    assert(emptyline != lines.end());

    Strings rangelines(lines.begin(), emptyline);
    Strings ingredientlines(emptyline + 1, lines.end());

    Ranges ranges = build_ranges(rangelines);

    Longs ingredients;
    for (const auto &str : ingredientlines)
        ingredients.push_back(std::stol(str));

    int result = 0;

    for (const auto &ingredient : ingredients)
    {
        for (const auto &row : ranges)
        {
            if (ingredient >= row.min && ingredient <= row.max)
            {
                ++result;
                break;
            }
        }
    }

    return result;
}

int main()
{
    // Print
    const auto input = read_input("input/input");

    // for (const auto &s : input)
    //     std::cout << s << std::endl;

    std::cout << "Part 1: " << part1(input) << "\n";
    // std::cout << "Part 2: " << part2(at_locations) << "\n";

    return 0;
}