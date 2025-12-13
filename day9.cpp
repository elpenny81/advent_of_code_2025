#include "utils.hpp"
#include <bits/stdc++.h>

struct Coordinate
{
    int64_t x{0};
    int64_t y{0};

    static Coordinate fromString(std::string_view str)
    {
        auto parts = utils::stringSplit(str, ',');
        assert(parts.size() == 2);
        return {std::stoll(parts[0]), std::stoll(parts[1])};
    }

    int64_t area(const Coordinate &other) const { return (std::abs(x - other.x) + 1) * (std::abs(y - other.y) + 1); }

    bool operator<(const Coordinate &other) const
    {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
};

struct Rect
{
    int64_t xMin{0};
    int64_t xMax{0};
    int64_t yMin{0};
    int64_t yMax{0};

    static Rect fromCoordinates(const Coordinate &a, const Coordinate &b)
    {
        return {std::min(a.x, b.x), std::max(a.x, b.x), std::min(a.y, b.y), std::max(a.y, b.y)};
    }
};

static int64_t cross(const Coordinate &a, const Coordinate &b, const Coordinate &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static bool onSegment(const Coordinate &p, const Coordinate &a, const Coordinate &b)
{
    if (cross(a, b, p) != 0)
        return false;
    return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) && std::min(a.y, b.y) <= p.y
           && p.y <= std::max(a.y, b.y);
}

static bool pointInPolyOrOnBoundary(const Coordinate &p, const std::vector<Coordinate> &poly)
{
    bool   inside = false;
    size_t n      = poly.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        const auto &a = poly[i];
        const auto &b = poly[j];
        if (onSegment(p, a, b))
            return true;

        const bool intersects = ((a.y > p.y) != (b.y > p.y))
                                && (static_cast<double>(p.x) < static_cast<double>((b.x - a.x) * (p.y - a.y))
                                                                   / static_cast<double>((b.y - a.y) + a.x));
        if (intersects)
            inside = !inside;
    }
    return inside;
}

static bool properIntersect(const Coordinate &a, const Coordinate &b, const Coordinate &c, const Coordinate &d)
{
    int64_t abXc = cross(a, b, c);
    int64_t abXd = cross(a, b, d);
    int64_t cdXa = cross(c, d, a);
    int64_t cdXb = cross(c, d, b);

    // Proper intersection requires strict sign changes on both
    return ((abXc > 0 && abXd < 0) || (abXc < 0 && abXd > 0)) && ((cdXa > 0 && cdXb < 0) || (cdXa < 0 && cdXb > 0));
}

static bool edgeCrossesRectBoundary(const Coordinate &p, const Coordinate &q, const Rect &rect)
{
    Coordinate e1{rect.xMin, rect.yMin};
    Coordinate e2{rect.xMax, rect.yMin};
    Coordinate e3{rect.xMax, rect.yMax};
    Coordinate e4{rect.xMin, rect.yMax};

    if (properIntersect(p, q, e1, e2))
        return true;
    if (properIntersect(p, q, e2, e3))
        return true;
    if (properIntersect(p, q, e3, e4))
        return true;
    if (properIntersect(p, q, e4, e1))
        return true;

    return false;
}

static bool rectInsidePoly(const Rect &r, const std::vector<Coordinate> &poly)
{
    if (r.xMin == r.xMax || r.yMin == r.yMax)
        return false;

    Coordinate c1{r.xMin, r.yMin};
    Coordinate c2{r.xMax, r.yMin};
    Coordinate c3{r.xMax, r.yMax};
    Coordinate c4{r.xMin, r.yMax};

    if (!pointInPolyOrOnBoundary(c1, poly))
        return false;
    if (!pointInPolyOrOnBoundary(c2, poly))
        return false;
    if (!pointInPolyOrOnBoundary(c3, poly))
        return false;
    if (!pointInPolyOrOnBoundary(c4, poly))
        return false;

    for (size_t i = 0; i < poly.size(); ++i) {
        const auto &a = poly[i];
        const auto &b = poly[(i + 1) % poly.size()];
        if (edgeCrossesRectBoundary(a, b, r))
            return false;
    }

    return true;
}

void part1(const std::string &filename)
{
    std::ifstream           file(filename);
    std::string             line;
    std::vector<Coordinate> coordinates;

    while (std::getline(file, line)) {
        coordinates.push_back(Coordinate::fromString(line));
    }

    int64_t maxArea = 0;
    for (size_t i = 0; i < coordinates.size(); ++i) {
        for (size_t j = i + 1; j < coordinates.size(); ++j) {
            int64_t area = coordinates[i].area(coordinates[j]);
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    std::println("Part 1 : {}", maxArea);
}

void part2(const std::string &filename)
{
    std::ifstream           file(filename);
    std::string             line;
    std::vector<Coordinate> coordinates;

    while (std::getline(file, line)) {
        coordinates.push_back(Coordinate::fromString(line));
    }

    int64_t maxArea = 0;
    for (size_t i = 0; i < coordinates.size(); ++i) {
        for (size_t j = i + 1; j < coordinates.size(); ++j) {
            auto r = Rect::fromCoordinates(coordinates[i], coordinates[j]);
            if (!rectInsidePoly(r, coordinates))
                continue;
            int64_t area = coordinates[i].area(coordinates[j]);
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    std::println("Part 2 : {}", maxArea);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::println(stderr, "Usage: {} <input_file>", argv[0]); // NOLINT(*-pro-bounds-pointer-arithmetic)
        return 1;
    }

    const std::string filename = argv[1]; // NOLINT(*-pro-bounds-pointer-arithmetic)

    part1(filename);
    part2(filename);

    return 0;
}
