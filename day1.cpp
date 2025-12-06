#include <format>
#include <fstream>
#include <iostream>
#include <string>

void part1(const std::string &filename)
{
    constexpr int Modulo    = 100;
    int           start     = 50;
    int           countZero = 0;
    std::ifstream file(filename);

    char dir   = 0;
    int  steps = 0;

    while (file >> dir >> steps) {
        steps %= Modulo;
        int delta = (dir == 'L') ? -steps : steps;
        start     = (start + delta + Modulo) % Modulo;
        if (start == 0)
            countZero++;
    }
    std::cout << std::format("Part 1: {}\n", countZero);
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
        int first = (start == 0) ? Modulo : (d == 'R' ? Modulo - start : start);
        if (n < first)
            return 0;
        return 1 + (n - first) / Modulo;
    };

    while (file >> dir >> steps) {
        countZero += countHits(dir, steps, start);
        int eff   = steps % Modulo;
        int delta = (dir == 'L') ? -eff : eff;
        start     = (start + delta + Modulo) % Modulo;
    }
    std::cout << std::format("Part 2: {}\n", countZero);
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
