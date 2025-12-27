#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>

using instructies = std::vector<std::string>;

enum class Richting
{
    Links,
    Rechts
};

struct Instructie
{
    int stapjes;
    Richting richting;

    Instructie(std::string line)
    {
        // R50
        // -> Richting::Rechts, 50 stapjes
        if (line[0] == 'R')
        {
            richting = Richting::Rechts;
        }
        else if (line[0] == 'L')
        {
            richting = Richting::Links;
        }
        stapjes = std::stoi(line.substr(1));
    }
};

class Kluis
{
    int dial = 50;

public:
    int maketurn(const Instructie &instructie)
    {
        int count = 0;

        for (int i = 0; i < instructie.stapjes; i++)
        {
            if (instructie.richting == Richting::Links)
                dial--;
            else
                dial++;

            if (dial > 99)
                dial = 0;
            if (dial < 0)
                dial = 99;

            if (dial == 0)
                count++;
        }

        return count;
    }
};

int turnen(const instructies &instructies)
{
    int base = 100;
    int dial = 50;
    int up = 0;

    for (int i = 0; i < instructies.size(); i++)
    {
        //std::cout << dial << "," << instructies[i] << std::endl;
        int step = std::stoi(instructies[i].substr(1));
        if (instructies[i][0] == 'R')
        {
            dial += step;
        }
        else if (instructies[i][0] == 'L')
        {
            dial -= step;
        }
        else
        {
            assert(false);
        }
        // normalization
        dial = ((dial % base) + base) % base;
        if (dial > 99)
        {
            assert(false);
        }
        if (dial == 0)
        {
            up += 1;
        }
    }

    return up;
}

instructies input(const std::string& filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    instructies turns;
    std::string turn;

    while (in >> turn)
    {
        turns.push_back(turn);
    }

    return turns;
}

int doedeel2(const instructies &instructies)
{
    Kluis kluis;
    int totaal = 0;

    for (const std::string &instructie : instructies)
    {
        totaal += kluis.maketurn(Instructie(instructie));
    }
    return totaal;
}

int main()
{

    // Print
    auto instructies = input("input/input");
    std::cout << "Read " << instructies.size() << " instructions\n";
    int answer = turnen(instructies);
    std::cout << "Number of zeros: " << answer << "\n";

    int answerdeel2 = doedeel2(instructies);
    std::cout << answerdeel2 << " keer langs 0 gekomen" << std::endl;
    return 0;
}