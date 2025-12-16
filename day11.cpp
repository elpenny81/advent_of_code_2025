#include "utils.hpp"
#include <bits/stdc++.h>

using Map   = std::unordered_map<std::string, std::vector<std::string>>;
using Cache = std::unordered_map<std::string, int64_t>;

static int64_t cntDst(const std::string &src, const std::string &dst, const Map &map, Cache &cache)
{
    const auto key = std::format("{}->{}", src, dst);
    if (cache.contains(key))
        return cache.at(key);
    if (src == dst)
        return 1;
    if (!map.contains(src))
        return 0;

    int64_t sum = 0;
    for (auto &x : map.at(src))
        sum += cntDst(x, dst, map, cache);
    cache[key] = sum;

    return sum;
}

void part1(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;
    Map           map;

    while (std::getline(file, line)) {
        auto parts   = utils::stringSplit(line);
        auto key     = parts.at(0).substr(0, 3);
        auto targets = std::vector(parts.begin() + 1, parts.end());
        map[key]     = targets;
    }

    Cache cache;
    auto  result = cntDst("you", "out", map, cache);
    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;
    Map           map;

    while (std::getline(file, line)) {
        auto parts   = utils::stringSplit(line);
        auto key     = parts.at(0).substr(0, 3);
        auto targets = std::vector(parts.begin() + 1, parts.end());
        map[key]     = targets;
    }

    Cache   cache;
    int64_t result = cntDst("svr", "dac", map, cache) * cntDst("dac", "fft", map, cache)
                         * cntDst("fft", "out", map, cache)
                     + cntDst("svr", "fft", map, cache) * cntDst("fft", "dac", map, cache)
                           * cntDst("dac", "out", map, cache);
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
