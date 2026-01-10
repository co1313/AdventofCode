#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cmath>

using Ints = std::vector<int>;
using Boxes = std::vector<Ints>;
using Circuits = std::vector<std::set<int>>;
using Pairs = std::vector<std::pair<std::size_t, std::size_t>>;

// Read input lines from a file
Boxes read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Boxes junction_boxes;
    for (std::string line; std::getline(in, line);)
    {
        Ints coordinates;
        std::stringstream ss(line);
        for (std::string val; std::getline(ss, val, ',');)
        {
            coordinates.push_back(std::stoi(val));
        }

        junction_boxes.push_back(coordinates);
    }

    return junction_boxes;
}

double calc_distance(const Ints &a, const Ints &b)
{
    long squares = 0;
    for (size_t i = 0; i < a.size(); ++i)
        squares += static_cast<double>(a[i] - b[i]) * (a[i] - b[i]);
    return std::sqrt(squares);
}

Boxes create_distancegrid(const Boxes &junction_boxes)
{
    size_t n = junction_boxes.size();
    Boxes grid(n, Ints(n, 0));

    for (size_t row = 0; row < n; ++row)
    {
        for (size_t col = row + 1; col < n; ++col)
        {
            grid[row][col] = static_cast<int>(calc_distance(junction_boxes[row], junction_boxes[col]));
        }
    }

    return grid;
}

void merge_and_remove(Circuits &v, std::size_t i, std::size_t j)
{
    if (i > j)
        std::swap(i, j);
    v[i].merge(v[j]);
    v.erase(v.begin() + j);
}

Pairs find_shortest_connections(const Boxes &grid)
{
    using Entry = std::pair<int, std::pair<std::size_t, std::size_t>>;
    std::vector<Entry> all_pairs;

    size_t N = grid.size();
    for (size_t r = 0; r < N; ++r)
        for (size_t c = r + 1; c < N; ++c)
            all_pairs.push_back({grid[r][c], {r, c}});

    std::sort(all_pairs.begin(), all_pairs.end(),
              [](const Entry &a, const Entry &b)
              { return a.first < b.first; });
    Pairs result;
    for (size_t i = 0; i < all_pairs.size(); ++i)
        result.push_back(all_pairs[i].second);

    return result;
}

void merge_circuits(const Boxes &grid, Circuits &circuits, std::size_t connections)
{
    Pairs lowest = find_shortest_connections(grid);
    if (connections > 0)
    {
        lowest.resize(connections);
    }
    for (auto [a, b] : lowest)
    {
        std::size_t idx_a = circuits.size();
        std::size_t idx_b = circuits.size();

        for (std::size_t i = 0; i < circuits.size(); ++i)
        {
            if (circuits[i].count(a))
                idx_a = i;
            if (circuits[i].count(b))
                idx_b = i;
        }

        if (idx_a != idx_b)
            merge_and_remove(circuits, idx_a, idx_b);
    }
}

Pairs merge_all_circuits(const Boxes &grid, Circuits &circuits)
{
    Pairs final_connection;
    Pairs lowest = find_shortest_connections(grid);

    for (auto [a, b] : lowest)
    {
        std::size_t idx_a = circuits.size();
        std::size_t idx_b = circuits.size();

        for (std::size_t i = 0; i < circuits.size(); ++i)
        {
            if (circuits[i].count(a))
                idx_a = i;
            if (circuits[i].count(b))
                idx_b = i;
        }
        if (circuits.size() == 2 && idx_a != idx_b)
        {
            std::pair<std::size_t, std::size_t> final_pair = {a, b};
            final_connection.push_back(final_pair);
            return final_connection;
        }
        if (idx_a != idx_b)
            merge_and_remove(circuits, idx_a, idx_b);
    }
}

std::size_t product_of_largest_3_sets(const Circuits &v)
{
    std::vector<std::size_t> sizes;
    for (auto &s : v)
        sizes.push_back(s.size());

    std::partial_sort(sizes.begin(), sizes.begin() + 3, sizes.end(),
                      std::greater<std::size_t>());

    return sizes[0] * sizes[1] * sizes[2];
}

int part1(const Boxes &junction_boxes, std::size_t connections)
{
    Boxes grid = create_distancegrid(junction_boxes);

    Circuits circuits;
    for (std::size_t i = 0; i < junction_boxes.size(); ++i)
        circuits.push_back({static_cast<int>(i)});

    merge_circuits(grid, circuits, connections);

    return static_cast<int>(product_of_largest_3_sets(circuits));
}

int part2(const Boxes &junction_boxes)
{
    Boxes grid = create_distancegrid(junction_boxes);

    Circuits circuits;
    for (std::size_t i = 0; i < junction_boxes.size(); ++i)
        circuits.push_back({static_cast<int>(i)});

    Pairs final_connection = merge_all_circuits(grid, circuits);

    return junction_boxes[final_connection[0].first][0] * junction_boxes[final_connection[0].second][0];
}

int main()
{
    // Print
    const auto input = read_input("input/input");
    std::size_t connections = 1000;

    // for (const auto &ints : input)
    //{
    //     for (size_t i = 0; i < ints.size(); ++i)
    //     {
    //         std::cout << ints[i];
    //         if (i + 1 < ints.size())
    //             std::cout << ',';
    //     }
    //     std::cout << '\n';
    // }

    std::cout << "Part 1 with " << connections << " connections: " << part1(input, connections) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
