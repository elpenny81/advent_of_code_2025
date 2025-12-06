#include <bits/stdc++.h>

struct Range
{
    uint64_t start = 0;
    uint64_t end   = 0;

    static Range fromString(const std::string &s)
    {
        auto pos = s.find('-');
        if (pos == std::string::npos)
            throw std::invalid_argument("Invalid data");
        return {std::stoull(s.substr(0, pos)), std::stoull(s.substr(pos + 1))};
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

    std::cout << std::format("Part 1: {}\n", result);
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
            const auto r2 = *it;
            if (r1.isOverlap(r2)) {
                r1.start = std::min(r2.start, r1.start);
                r1.end   = std::max(r2.end, r1.end);
                ranges.erase(it);
                it = ranges.begin(); // continue at begin
                continue;
            }
            it++;
        }
        ranges.emplace_back(r1);
    }

    uint64_t result = 0;
    for (auto &r : ranges)
        result += r.elements();

    std::cout << std::format("Part 2: {}\n", result);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl; // NOLINT
        return 1;
    }

    const std::string filename = argv[1]; // NOLINT

    part1(filename);
    part2(filename);

    return 0;
}
