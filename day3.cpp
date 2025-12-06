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

    std::cout << std::format("Part 1: {}\n", result);
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
