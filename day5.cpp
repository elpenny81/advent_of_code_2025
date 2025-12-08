#include "utils.hpp"
#include <bits/stdc++.h>

struct Range
{
    uint64_t start = 0;
    uint64_t end   = 0;

    static Range fromString(const std::string &s)
    {
        const auto parts = utils::stringSplit(s, '-');
        return {std::stoull(parts.at(0)), std::stoull(parts.at(1))};
    }

    bool isInRange(uint64_t n) const { return n >= start && n <= end; }

    bool isOverlap(const Range &other) const
    {
        return isInRange(other.start) || isInRange(other.end) || other.isInRange(start) || other.isInRange(end);
    }

    uint64_t elements() const { return (end - start) + 1; }
};

void part1(const std::string &filename)
{
    std::ifstream      file(filename);
    std::string        line;
    uint64_t           result      = 0;
    bool               parseRanges = true;
    std::vector<Range> ranges;

    while (std::getline(file, line)) {
        if (line.empty()) {
            parseRanges = false;
            continue;
        }

        if (parseRanges) {
            ranges.push_back(Range::fromString(line));
        } else {
            auto n = std::stoll(line);
            if (std::ranges::any_of(ranges, [&](const auto &range) { return range.isInRange(n); })) {
                result++;
            }
        }
    }

    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream      file(filename);
    std::string        line;
    std::vector<Range> ranges;

    // collect all ranges
    while (std::getline(file, line)) {
        if (line.empty())
            break;

        auto r1 = Range::fromString(line);
        for (auto it = ranges.begin(); it != ranges.end();) {
            if (const auto r2 = *it; r1.isOverlap(r2)) {
                r1.start = std::min(r2.start, r1.start);
                r1.end   = std::max(r2.end, r1.end);
                ranges.erase(it);
                it = ranges.begin(); // continue at begin
                continue;
            }
            ++it;
        }
        ranges.emplace_back(r1);
    }

    uint64_t result = 0;
    for (auto &r : ranges)
        result += r.elements();

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
