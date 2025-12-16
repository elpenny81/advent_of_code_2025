#include "utils.hpp"
#include <bits/stdc++.h>

void part1(const std::string &filename)
{
    std::ifstream    file(filename);
    std::string      line;
    std::vector<int> counts;

    for (int i = 0; i < 6; ++i) {
        int bitcount = 0;
        for (int k = 0; k < 4; k++) {
            if (!std::getline(file, line))
                break;
            if (k == 0)
                continue;
            for (const auto &ch : line)
                bitcount += (ch == '#') ? 1 : 0;
        }
        counts.push_back(bitcount);
        std::getline(file, line); // skip empty line
    }

    int32_t result = 0;
    while (std::getline(file, line)) {
        auto parts = utils::stringSplit(line);
        auto dims  = utils::stringSplit(parts.at(0).substr(0, parts.at(0).size() - 1), 'x');
        int  x     = std::stoi(dims.at(0));
        int  y     = std::stoi(dims.at(1));

        int total = 0;
        for (int i = 0; i < 6; ++i)
            total += std::stoi(parts.at(i + 1)) * counts[i];
        if (total <= x * y)
            result++;
    }

    std::println("Part 1 : {}", result);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::println(stderr, "Usage: {} <input_file>", argv[0]); // NOLINT(*-pro-bounds-pointer-arithmetic)
        return 1;
    }

    const std::string filename = argv[1]; // NOLINT(*-pro-bounds-pointer-arithmetic)

    part1(filename);

    return 0;
}
