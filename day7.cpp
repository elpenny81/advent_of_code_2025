#include <bits/stdc++.h>

struct Position
{
    std::size_t x{0};
    std::size_t y{0};

    bool operator==(const Position &) const = default;
};

template<>
struct std::hash<Position>
{
    std::size_t operator()(const Position &p) const noexcept
    {
        const auto h1 = std::hash<std::size_t>{}(p.x);
        const auto h2 = std::hash<std::size_t>{}(p.y);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

using Cache = std::unordered_map<Position, uint64_t>;
using Map   = std::vector<std::string>;

uint64_t step(const Position &start, Map &map)
{
    for (std::size_t y = start.y; y < map.size(); y++) {
        // split at '^'
        if (map.at(y).at(start.x) == '^') {
            // count number of splits
            uint64_t result = 0;
            if (start.x > 0 && map[y][start.x - 1] != '|')
                result += step({start.x - 1, y}, map);
            if (start.x < (map.at(y).size() - 1) && map[y][start.x + 1] != '|')
                result += step({start.x + 1, y}, map);
            return 1 + result;
        }
        // if there is already a beam -> we stop/merge with it
        if (map[y][start.x] == '|')
            break;
        map[y][start.x] = '|';
    }

    return 0;
}

uint64_t stepPart2(const Position &start, const Map &map, Cache &cache)
{
    for (std::size_t y = start.y; y < map.size(); y++) {
        // split at '^'
        if (map.at(y).at(start.x) == '^') {
            const Position cur{start.x, y};
            if (cache.contains(cur)) {
                return cache.at(cur);
            }

            // count number of splits
            uint64_t result = 0;
            if (start.x > 0)
                result += stepPart2({start.x - 1, y}, map, cache);
            if (start.x < (map.at(y).size() - 1))
                result += stepPart2({start.x + 1, y}, map, cache);

            cache[cur] = result;
            return result;
        }
    }

    return 1;
}

void part1(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;
    Map           lines;
    Position      start;

    while (std::getline(file, line)) {
        if (auto startPos = line.find('S'); startPos != std::string::npos) {
            start.x = startPos;
            start.y = lines.size();
        }
        lines.emplace_back(line);
    }

    const uint64_t result = step(start, lines);
    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;
    Map           lines;
    Position      start;
    Cache         cache;

    while (std::getline(file, line)) {
        if (auto startPos = line.find('S'); startPos != std::string::npos) {
            start.x = startPos;
            start.y = lines.size();
        }
        lines.emplace_back(line);
    }

    const uint64_t result = stepPart2(start, lines, cache);
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
