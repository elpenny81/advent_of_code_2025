#include <bits/stdc++.h>

void part1(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;

    std::size_t result = 0;

    while (std::getline(file, line)) {
        char max1 = '0';
        char max2 = '0';
        for (std::size_t i = 0; i < line.size(); ++i) {
            if (line[i] > max1 && i < (line.size() - 1)) {
                max1 = line[i];
                max2 = '0';
            } else if (line[i] > max2) {
                max2 = line[i];
            }
        }

        result += (max1 - '0') * 10 + (max2 - '0');
    }

    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream file(filename);
    std::string   line;
    uint64_t      result = 0;

    while (std::getline(file, line)) {
        std::string digits(12, '0');
        std::size_t start = 0;

        for (std::size_t i = 0; i < digits.size(); i++) {
            for (std::size_t j = start; j < (line.size() - (digits.size() - i)) + 1; j++) {
                if (line[j] > digits[i]) {
                    digits[i] = line[j];
                    start     = j + 1;
                    if (digits[i] == '9')
                        break; // there is no higher digit
                }
            }
        }
        result += std::stoull(digits);
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
