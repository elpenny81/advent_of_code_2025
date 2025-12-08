#include <bits/stdc++.h>

void part1(const std::string &filename)
{
    std::vector<std::vector<std::string>> grid;
    std::ifstream                         file(filename);
    std::string                           line;
    while (std::getline(file, line)) {
        std::stringstream str(line);
        std::string       token;
        grid.emplace_back();
        while (str >> token) {
            grid.back().emplace_back(token);
        }
    }

    const std::size_t rows   = grid.size() - 1;
    const std::size_t cols   = grid[0].size();
    const auto       &ops    = grid.back();
    uint64_t          result = 0;

    for (std::size_t col = 0; col < cols; col++) {
        const auto &op = ops.at(col).at(0);

        uint64_t rowResult = op == '+' ? 0 : 1;
        for (std::size_t row = 0; row < rows; row++) {
            if (op == '+')
                rowResult += std::stoull(grid[row][col]);
            if (op == '*')
                rowResult *= std::stoull(grid[row][col]);
        }

        result += rowResult;
    }

    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream            file(filename);
    std::string              line;
    uint64_t                 result = 0;
    while (std::getline(file, line)) {
        lines.emplace_back(line);
    }

    auto opsLine = lines.back();
    lines.pop_back();
    auto startPos = opsLine.find_first_not_of(' ');
    while (startPos != std::string::npos) {
        auto     nextStartPos = opsLine.find_first_not_of(' ', startPos + 1);
        auto     endPos       = (nextStartPos == std::string::npos) ? opsLine.size() - 1 : nextStartPos - 2;
        char     op           = opsLine.at(startPos);
        uint64_t tmpResult    = op == '+' ? 0 : 1;
        for (size_t i = startPos; i <= endPos; i++) {
            std::string tmp;
            for (auto &l : lines) {
                char c = l.at(i);
                if (c == ' ')
                    continue;
                tmp.push_back(c);
            }

            if (op == '*')
                tmpResult *= std::stoull(tmp);
            if (op == '+')
                tmpResult += std::stoull(tmp);
        }
        startPos = nextStartPos;
        result += tmpResult;
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
