#include "utils.hpp"
#include <bits/stdc++.h>

using std::greater;

struct DSU
{
    std::vector<int> parent;
    std::vector<int> size;

    explicit DSU(int n)
        : parent(n)
        , size(n, 1)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;

        if (size[a] < size[b])
            std::swap(a, b);

        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    int componentSize(int x) { return size[find(x)]; }
};

struct Coordinate
{
    uint64_t x{0};
    uint64_t y{0};
    uint64_t z{0};

    static Coordinate fromString(const std::string &in)
    {
        const auto tmp = utils::stringSplit(in, ',');
        assert(tmp.size() == 3);
        return {std::stoull(tmp.at(0)), std::stoull(tmp.at(1)), std::stoull(tmp.at(2))};
    }

    bool operator==(const Coordinate &) const = default;

    uint64_t squaredDistance(const Coordinate &other) const
    {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
    }

    std::string toString() const { return std::format("[{},{},{}]", x, y, z); }
};

struct Edge
{
    uint64_t dist2;
    int      i;
    int      j;
};

void part1(const std::string &filename)
{
    std::ifstream           file(filename);
    std::string             line;
    uint64_t                result = 1;
    std::vector<Coordinate> coordinates;

    while (std::getline(file, line)) {
        coordinates.push_back(Coordinate::fromString(line));
    }

    const auto n = static_cast<int>(coordinates.size());

    std::vector<Edge> edges;
    edges.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({coordinates[i].squaredDistance(coordinates[j]), i, j});
        }
    }

    std::ranges::sort(edges, [](const auto &a, const auto &b) { return a.dist2 < b.dist2; });

    DSU dsu(n);

    int considered = 0;
    for (auto &e : edges) {
        ++considered;
        dsu.unite(e.i, e.j);
        if (considered == 1000)
            break;
    }

    std::vector<int> sizes(n, 0);
    for (int i = 0; i < n; ++i) {
        int root = dsu.find(i);
        sizes[root]++;
    }

    std::ranges::sort(sizes, greater());
    for (int i = 0; i < 3; i++)
        result *= sizes[i];

    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream           file(filename);
    std::string             line;
    uint64_t                result = 1;
    std::vector<Coordinate> coordinates;

    while (std::getline(file, line)) {
        coordinates.push_back(Coordinate::fromString(line));
    }

    const int n = static_cast<int>(coordinates.size());

    std::vector<Edge> edges;
    edges.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({coordinates[i].squaredDistance(coordinates[j]), i, j});
        }
    }

    std::ranges::sort(edges, [](const auto &a, const auto &b) { return a.dist2 < b.dist2; });

    DSU dsu(n);

    int components = n;
    for (auto &e : edges) {
        if (dsu.unite(e.i, e.j)) {
            components--;
            if (components == 1) {
                result = coordinates[e.i].x * coordinates[e.j].x;
            }
        }
    }

    std::println("Part 2 : {}", result);
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
