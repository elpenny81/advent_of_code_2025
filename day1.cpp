#include <bits/stdc++.h>

void part1(const std::string &filename)
{
    int           start     = 50;
    int           countZero = 0;
    std::ifstream file(filename);

    char dir   = 0;
    int  steps = 0;

    while (file >> dir >> steps) {
        constexpr int Modulo = 100;
        steps %= Modulo;
        const int delta = (dir == 'L') ? -steps : steps;
        start           = (start + delta + Modulo) % Modulo;
        if (start == 0)
            countZero++;
    }
    std::println("Part 1 : {}", countZero);
}

void part2(const std::string &filename)
{
    constexpr int Modulo    = 100;
    int           start     = 50;
    int           countZero = 0;
    std::ifstream file(filename);

    char dir   = 0;
    int  steps = 0;

    auto countHits = [&](char d, int n, int s) {
        if (n <= 0)
            return 0;
        const int first = (start == 0) ? Modulo : (d == 'R' ? Modulo - start : start);
        if (n < first)
            return 0;
        return 1 + (n - first) / Modulo;
    };

    while (file >> dir >> steps) {
        countZero += countHits(dir, steps, start);
        const int eff   = steps % Modulo;
        const int delta = (dir == 'L') ? -eff : eff;
        start           = (start + delta + Modulo) % Modulo;
    }
    std::println("Part 2 : {}", countZero);
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
