#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>

using Strings = std::vector<std::string>;
using Longs = std::vector<long>;

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

bool is_all_spaces(const std::string &s)
{
    return s.find_first_not_of(' ') == std::string::npos;
}

long apply_op(long a, long b, char op)
{
    return (op == '+') ? a + b : a * b;
}

Strings tokenize(const std::string &line)
{
    std::stringstream ss(line);
    Strings token;
    std::string temp;

    while (ss >> temp)
    {
        token.push_back(temp);
    }

    return token;
}

long calculate_problem(Strings &column)
{
    char op = '+';
    if (!column.empty())
    {
        op = column.back()[0];
        column.pop_back();
    }

    Longs problem(column.size());
    std::transform(column.begin(), column.end(), problem.begin(),
                   [](const std::string &s)
                   { return std::stol(s); });

    long solution = 0;

    solution = (op == '+') ? std::accumulate(problem.begin(), problem.end(), 0L) : std::accumulate(problem.begin(), problem.end(), 1L, [](long a, long b)
                                                                                                   { return a * b; });
    return solution;
}

long part1(const Strings &lines)
{
    std::vector<Strings> tokens;
    for (const auto &line : lines)
    {
        tokens.push_back(tokenize(line));
    }

    long grand_total = 0;

    for (size_t col = 0; col < tokens[0].size(); ++col)
    {
        Strings column;
        for (const auto &row : tokens)
        {
            column.push_back(row[col]);
        }

        grand_total += calculate_problem(column);
    }

    return grand_total;
}

Strings rows_to_columns(const Strings &lines)
{
    Strings columns(lines[0].size());

    for (auto &row : lines)
        for (size_t col = 0; col < row.size(); ++col)
            columns[col].push_back(row[col]);
    return columns;
}

long part2(const Strings &lines)
{
    Strings columns = rows_to_columns(lines);
    long total = 0;
    long grand_total = 0;
    char op = '+';
    size_t num_columns = columns.size();

    for (size_t col = 0; col < num_columns; ++col)
    {

        if (is_all_spaces(columns[col]))
            continue;

        char last = columns[col].back();
        if (last == '+' || last == '*')
        {
            grand_total += total;
            op = last;
            total = (op == '+') ? 0 : 1;
            columns[col].pop_back();
        }

        total = apply_op(total, std::stol(columns[col]), op);
    }

    return grand_total + total;
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