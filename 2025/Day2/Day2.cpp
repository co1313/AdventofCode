#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>
#include <filesystem>
#include <cmath>

using stringvector = std::vector<std::string>;
using intvector = std::vector<std::int64_t>;

stringvector input(const std::string &filename)
{
    std::cout << std::filesystem::current_path() << '\n';
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    stringvector ranges;
    std::string token;

    while (std::getline(in, token, ','))
    {
        ranges.push_back(token);
    }

    return ranges;
}

intvector numbers(const stringvector &ranges)
{
    intvector IDs;

    for (size_t i = 0; i < ranges.size(); i++)
    {
        const std::string &s = ranges[i];

        auto dashPos = s.find('-');
        if (dashPos == std::string::npos)
            continue;

        std::int64_t begin = std::stoll(s.substr(0, dashPos));
        std::int64_t end = std::stoll(s.substr(dashPos + 1));

        intvector IDrange(end - begin + 1);
        std::iota(IDrange.begin(), IDrange.end(), begin);

        IDs.insert(IDs.end(), IDrange.begin(), IDrange.end());
    }
    return IDs;
}

std::int64_t part1(const intvector &IDs)
{
    std::int64_t IDsum = 0;
    for (size_t i = 0; i < IDs.size(); i++)
    {
        int digits = std::to_string(IDs[i]).length();

        if (digits % 2 == 0 and IDs[i] % (int64_t)(std::pow(10, digits / 2) + 1) == 0)
            IDsum += IDs[i];
    }
    return IDsum;
}

intvector primeFac(int n)
{
    intvector res;

    // Check for factor 2
    if (n % 2 == 0)
    {
        res.push_back(2);
        while (n % 2 == 0)
            n /= 2;
    }

    // Check for odd prime factors
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }

    // If remaining n is a prime number > 2
    if (n > 2)
        res.push_back(n);

    return res;
}
std::int64_t zeroinserter(int digits, int factor)
{
    int divisor = 1;
    int insertnumber = digits / factor - 1;
    for (int i = 1; i < factor; i++)
        int divisor += std::pow(10, i + insertnumber);
    return divisor;
}

std::int64_t part2(const intvector &IDs)
{
    std::int64_t IDsum = 0;
    for (size_t i = 0; i < IDs.size(); i++)
    {
        int digits = std::to_string(IDs[i]).length();
        intvector factors = primeFac(digits);

        for (size_t j = 0; j < factors.size(); j++)
            if (digits % factors[j] == 0)

                if (IDs[i] % (int64_t)(std::pow(10, digits / factors[j]) + 1) == 0)
                    IDsum += IDs[i];
    }
    return IDsum;
}

int main()
{

    // Print
    auto instructies = numbers(input("input/testinput"));
    // std::cout << "Read " << instructies.size() << " instructions\n";

    /*     for (const auto &s : instructies)
        {
            std::cout << s << std::endl;
        } */

    std::int64_t answer1 = part1(instructies);
    std::cout << answer1 << std::endl;

    // int answer2 = part2(instructies);
    // std::cout << answer2 << " keer langs 0 gekomen" << std::endl;
    return 0;
}

111 3 121212 10101 6 123123123 1001001 9

    22 11 2 1212 101 4 123123 1001 6