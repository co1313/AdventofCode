#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using Strings = std::vector<std::string>;
using Boolgrid = std::vector<std::vector<bool>>;
using Intgrid = std::vector<std::vector<int>>;

// Read input lines from a file
Strings read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Strings lines;
    for (std::string line; std::getline(in, line);)
        if (!line.empty())
            lines.push_back(line);

    return lines;
}

// Convert lines to a boolean grid where '@' is true
Boolgrid at_mask(const Strings &lines)
{
    Boolgrid mask;

    for (const auto &str : lines)
    {
        std::vector<bool> row;
        row.reserve(lines.size());
        for (char c : str)
        {
            row.push_back(c == '@');
        }
        mask.push_back(row);
    }

    return mask;
}

// Count adjacent '@'s for each cell
Intgrid find_adjacent(const Boolgrid &rolls)
{
    size_t rows = rolls.size();
    size_t columns = rolls[0].size();
    Intgrid adjacent(rows, std::vector<int>(columns, 0));

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

// Count safe '@'s (less than 4 adjacent)
int part1(const Boolgrid &rolls)
{
    int result = 0;
    Intgrid adj = find_adjacent(rolls);
    for (size_t i = 0; i < rolls.size(); ++i)
    {
        for (size_t j = 0; j < rolls[i].size(); ++j)
        {
            if (adj[i][j] < 4 && rolls[i][j])
                ++result;
        }
    }
    return result;
}

// Count total '@'s removed iteratively
int part2(const Boolgrid &rolls)
{
    int result = 0;
    Boolgrid current = rolls;

    while (true)
    {
        Intgrid adj = find_adjacent(current);
        int result_last_round = result;

        for (size_t i = 0; i < current.size(); ++i)
        {
            for (size_t j = 0; j < current[i].size(); ++j)
            {
                if (adj[i][j] < 4 && current[i][j])
                {
                    ++result;
                    current[i][j] = false;
                }
            }
        }
        if (result_last_round == result)
            break;
    }
    return result;
}

int main()
{
    // Print
    const auto input = read_input("input/input");
    const auto at_locations = at_mask(input);

    // for (const auto &s : input)
    //     std::cout << s << std::endl;

    std::cout << "Part 1: " << part1(at_locations) << "\n";
    std::cout << "Part 2: " << part2(at_locations) << "\n";

    return 0;
}