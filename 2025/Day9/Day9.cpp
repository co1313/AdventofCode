#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Point
{
    long x, y;

    bool operator<(const Point &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

static bool operator==(const Point &a, const Point &b)
{
    return a.x == b.x && a.y == b.y;
}

using Points = std::vector<Point>;

Points read_input(const std::string &filename)
{
    std::ifstream in(filename + ".txt");
    assert(in && "Could not open input file");

    Points points;
    for (std::string line; std::getline(in, line);)
    {
        const auto commaPos = line.find(',');
        assert(commaPos != std::string::npos && "Invalid coordinate format");

        const long x = std::stol(line.substr(0, commaPos));
        const long y = std::stol(line.substr(commaPos + 1));

        points.push_back({x, y});
    }

    return points;
}

long part1(const Points &input)
{
    Points points = input;
    std::sort(points.begin(), points.end());

    long max_area = 0;
    const size_t n = points.size();

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            const long area =
                (points[j].x - points[i].x + 1) *
                (points[j].y - points[i].y + 1);

            if (area > max_area)
                max_area = area;
        }
    }
    return max_area;
}

static long orientation(const Point &a, const Point &b, const Point &c)
{
    const long v =
        (b.x - a.x) * (c.y - a.y) -
        (b.y - a.y) * (c.x - a.x);

    if (v == 0)
        return 0;
    return (v > 0) ? 1 : -1;
}

static bool pointOnSegment(const Point &a, const Point &b, const Point &p)
{
    return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
           std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

static bool segmentsIntersect(const Point &a, const Point &b,
                              const Point &c, const Point &d)
{
    const long o1 = orientation(a, b, c);
    const long o2 = orientation(a, b, d);
    const long o3 = orientation(c, d, a);
    const long o4 = orientation(c, d, b);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && pointOnSegment(a, b, c))
        return true;
    if (o2 == 0 && pointOnSegment(a, b, d))
        return true;
    if (o3 == 0 && pointOnSegment(c, d, a))
        return true;
    if (o4 == 0 && pointOnSegment(c, d, b))
        return true;

    return false;
}

static bool pointInPolygon(const Points &poly, const Point &p)
{
    bool inside = false;
    const int n = static_cast<int>(poly.size());

    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        const Point &a = poly[i];
        const Point &b = poly[j];

        if (orientation(a, b, p) == 0 && pointOnSegment(a, b, p))
            return true;

        if ((a.y > p.y) != (b.y > p.y))
        {
            const long lhs = (p.x - a.x) * (b.y - a.y);
            const long rhs = (b.x - a.x) * (p.y - a.y);

            if ((b.y > a.y && lhs < rhs) ||
                (b.y < a.y && lhs > rhs))
            {
                inside = !inside;
            }
        }
    }
    return inside;
}

bool rectangleInsidePolygon(const Points &poly,
                            const Point &p1, const Point &p2)
{
    long x1 = p1.x, y1 = p1.y;
    long x2 = p2.x, y2 = p2.y;

    if (x1 > x2)
        std::swap(x1, x2);
    if (y1 > y2)
        std::swap(y1, y2);

    const std::vector<Point> corners = {
        {x1, y1}, {x1, y2}, {x2, y2}, {x2, y1}};

    for (const auto &c : corners)
        if (!pointInPolygon(poly, c))
            return false;

    const std::vector<std::pair<Point, Point>> rectEdges = {
        {corners[0], corners[1]},
        {corners[1], corners[2]},
        {corners[2], corners[3]},
        {corners[3], corners[0]}};

    const int n = static_cast<int>(poly.size());

    for (const auto &re : rectEdges)
    {
        for (int i = 0; i < n; ++i)
        {
            const Point &a = poly[i];
            const Point &b = poly[(i + 1) % n];

            if (segmentsIntersect(re.first, re.second, a, b))
            {
                if (a == re.first || a == re.second ||
                    b == re.first || b == re.second)
                    continue;

                if (pointOnSegment(re.first, re.second, a) ||
                    pointOnSegment(re.first, re.second, b) ||
                    pointOnSegment(a, b, re.first) ||
                    pointOnSegment(a, b, re.second))
                    continue;

                return false;
            }
        }
    }

    return true;
}

long part2(const Points &inputPoly)
{
    const int n = static_cast<int>(inputPoly.size());
    long bestArea = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (rectangleInsidePolygon(inputPoly, inputPoly[i], inputPoly[j]))
            {
                const long w = std::abs(inputPoly[j].x - inputPoly[i].x);
                const long h = std::abs(inputPoly[j].y - inputPoly[i].y);
                const long area = (w + 1) * (h + 1);

                if (area > bestArea)
                    bestArea = area;
            }
        }
    }

    return bestArea;
}

int main()
{
    const auto input = read_input("input/input");

    std::cout << "Part 1: " << part1(input) << "\n";
    std::cout << "Part 2: " << part2(input) << "\n";

    return 0;
}
