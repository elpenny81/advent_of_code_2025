#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

struct Range
{
    uint64_t start = 0;
    uint64_t end   = 0;
};

Range parseRange(const std::string &s)
{
    auto dashPos = s.find('-');
    if (dashPos == std::string::npos) {
        throw std::invalid_argument("Invalid range format");
    }
    Range range;
    range.start = std::stoull(s.substr(0, dashPos));
    range.end   = std::stoull(s.substr(dashPos + 1));
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

        unsigned half = digits / 2;
        uint64_t base = POW10[half]; // 10^half

        uint64_t hi = n / base;
        uint64_t lo = n % base;

        return hi == lo;
    };

    std::ifstream file(filename);
    std::string   line;
    uint64_t      result = 0;
    while (std::getline(file, line, ',')) {
        // process line
        auto range = parseRange(line);
        for (auto n = range.start; n <= range.end; ++n) {
            if (haveTwiceSeq(n)) {
                result += n;
            }
        }
    };
    std::cout << std::format("Part 1: {}\n", result);
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

        std::size_t longestPrefixSuffix = lps[n - 1];
        if (longestPrefixSuffix == 0) {
            return false; // no proper prefix = suffix → no repetition
        }

        std::size_t patternLen = n - longestPrefixSuffix;
        return (n % patternLen == 0);
    };

    std::ifstream file(filename);
    std::string   line;
    uint64_t      result = 0;
    while (std::getline(file, line, ',')) {
        // process line
        auto range = parseRange(line);
        for (auto n = range.start; n <= range.end; ++n) {
            auto s = std::to_string(n);
            if (haveAnyRepetitionSeq(s)) {
                result += n;
            }
        }
    };
    std::cout << std::format("Part 2: {}\n", result);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n"; // NOLINT
        return 1;
    }
    part1(argv[1]); // NOLINT
    part2(argv[1]); // NOLINT
    return 0;
}
