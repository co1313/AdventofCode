#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <numeric>

using Strings = std::vector<std::string>;
using BeamPositions = std::vector<int>;
using Timelines = std::vector<long>;

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

BeamPositions advance_beams(const BeamPositions &previous, std::string &row, int &split_count, Timelines &timelines)
{
    BeamPositions new_positions;
    const int width = static_cast<int>(row.size());

    for (const auto &beam : previous)
    {
        if (beam < 0 || beam >= width)
        {
            continue;
        }

        char &cell = row[beam];
        if (cell == '|')
        {
            continue;
        }

        if (cell == '.')
        {
            cell = '|';
            new_positions.push_back(beam);
        }
        else if (cell == '^')
        {
            ++split_count;

            if (beam > 0)
            {
                timelines[beam - 1] += timelines[beam];
                row[beam - 1] = '|';
                new_positions.push_back(beam - 1);
            }
            if (beam + 1 < width)
            {
                timelines[beam + 1] += timelines[beam];
                row[beam + 1] = '|';
                new_positions.push_back(beam + 1);
            }

            timelines[beam] = 0;
        }
    }
    return new_positions;
}

int find_start(const Strings &lines)
{
    auto pos = lines[0].find('S');
    assert(pos != std::string::npos);
    return static_cast<int>(pos);
}

void run_simulation(const Strings &lines, BeamPositions &beam_positions, Strings &manifold, int &split_count, Timelines &timelines)
{
    for (size_t row = 1; row < manifold.size(); ++row)
    {
        beam_positions = advance_beams(beam_positions, manifold[row], split_count, timelines);
    }
}

int part1(const Strings &lines)
{
    int split_count = 0;
    Strings manifold = lines;

    BeamPositions beam_positions;
    Timelines dummy_timelines(lines[0].size(), 0);

    int start = find_start(lines);
    beam_positions.push_back(start);

    run_simulation(lines, beam_positions, manifold, split_count, dummy_timelines);

    return split_count;
}

long part2(const Strings &lines)
{
    int split_count = 0;
    Strings manifold = lines;

    BeamPositions beam_positions;
    Timelines timelines(lines[0].size(), 0);

    int start = find_start(lines);
    beam_positions.push_back(start);
    timelines[start] = 1;

    run_simulation(lines, beam_positions, manifold, split_count, timelines);

    return std::accumulate(timelines.begin(), timelines.end(), 0L);
}

int main()
{
    // Print
    const auto input = read_input("input/input");

    // for (const auto &s : input)
    //     std::cout << s << std::endl;

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
