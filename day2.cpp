#include "utils.hpp"
#include <bits/stdc++.h>

struct Range
{
    uint64_t start = 0;
    uint64_t end   = 0;
};

Range parseRange(const std::string &s)
{
    const auto parts = utils::stringSplit(s, '-');
    Range      range;
    range.start = std::stoull(parts.at(0));
    range.end   = std::stoull(parts.at(1));
    return range;
}

static constexpr uint64_t POW10[] = { // NOLINT
    1ULL,
    10ULL,
    100ULL,
    1000ULL,
    10000ULL,
    100000ULL,
    1000000ULL,
    10000000ULL,
    100000000ULL,
    1000000000ULL,
    10000000000ULL,
    100000000000ULL,
    1000000000000ULL,
    10000000000000ULL,
    100000000000000ULL,
    1000000000000000ULL,
    10000000000000000ULL,
    100000000000000000ULL,
    1000000000000000000ULL};

void part1(const std::string &filename)
{
    auto haveTwiceSeq = [](uint64_t n) -> bool {
        // Count digits
        if (n == 0) {
            return false; // "0" has 1 digit -> odd
        }

        uint64_t tmp    = n;
        unsigned digits = 0;
        while (tmp > 0) {
            tmp /= 10;
            ++digits;
        }

        if (digits & 1u) {
            // odd number of digits
            return false;
        }

        const unsigned half = digits / 2;
        const uint64_t base = POW10[half]; // 10^half

        const uint64_t hi = n / base;
        const uint64_t lo = n % base;

        return hi == lo;
    };

    std::ifstream file(filename);
    std::string   line;
    uint64_t      result = 0;
    while (std::getline(file, line, ',')) {
        // process line
        auto [start, end] = parseRange(line);
        for (auto n = start; n <= end; ++n) {
            if (haveTwiceSeq(n)) {
                result += n;
            }
        }
    };
    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    auto haveAnyRepetitionSeq = [](std::string_view s) -> bool {
        const std::size_t n = s.size();
        if (n <= 1) {
            return false;
        }

        std::vector<std::size_t> lps(n, 0);

        for (std::size_t i = 1, len = 0; i < n;) {
            if (s[i] == s[len]) {
                lps[i++] = ++len;
            } else if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }

        const std::size_t longestPrefixSuffix = lps[n - 1];
        if (longestPrefixSuffix == 0) {
            return false; // no proper prefix = suffix → no repetition
        }

        const std::size_t patternLen = n - longestPrefixSuffix;
        return (n % patternLen == 0);
    };

    std::ifstream file(filename);
    std::string   line;
    uint64_t      result = 0;
    while (std::getline(file, line, ',')) {
        // process line
        auto [start, end] = parseRange(line);
        for (auto n = start; n <= end; ++n) {
            auto s = std::to_string(n);
            if (haveAnyRepetitionSeq(s)) {
                result += n;
            }
        }
    };
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
