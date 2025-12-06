#include <bits/stdc++.h>

std::vector<std::vector<char>> readInputData(const std::string &filename)
{
    std::ifstream                  file(filename);
    std::string                    line;
    std::vector<std::vector<char>> data;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        data.push_back(row);
    }
    return data;
}

// NOLINTNEXTLINE
static constexpr std::pair<int, int> Directions[] = {
    {-1, 0 },
    {-1, -1},
    {0,  -1},
    {1,  -1},
    {1,  0 },
    {1,  1 },
    {0,  1 },
    {-1, 1 }
};

void part1(const std::string &filename)
{
    uint64_t   result = 0;
    const auto data   = readInputData(filename);

    for (std::size_t i = 0; i < data.size(); ++i) {
        for (std::size_t j = 0; j < data[i].size(); ++j) {
            if (data[i][j] != '@')
                continue;
            int cnt = 0;
            for (auto &dir : Directions) {
                std::pair<int, int> idx{i + dir.first, j + dir.second};
                if (idx.first < 0 || idx.second < 0 || idx.first >= data.size() || idx.second >= data[i].size())
                    continue;
                if (data[idx.first][idx.second] == '@')
                    cnt++;
            }
            if (cnt < 4) {
                result++;
            }
        }
    }

    std::cout << "Part 1: " << result << std::endl;
}

void part2(const std::string &filename)
{
    uint64_t result = 0;
    auto     data   = readInputData(filename);

    while (true) {
        uint64_t tmpResult = 0;

        for (std::size_t i = 0; i < data.size(); ++i) {
            for (std::size_t j = 0; j < data[i].size(); ++j) {
                if (data[i][j] != '@')
                    continue;
                int cnt = 0;
                for (auto &dir : Directions) {
                    std::pair<int, int> idx{i + dir.first, j + dir.second};
                    if (idx.first < 0 || idx.second < 0 || idx.first >= data.size() || idx.second >= data[i].size())
                        continue;
                    if (data[idx.first][idx.second] == '@')
                        cnt++;
                }
                if (cnt < 4) {
                    data[i][j] = 'x';
                    tmpResult++;
                }
            }
        }

        if (tmpResult == 0)
            break;
        result += tmpResult;
    }

    std::cout << "Part 2: " << result << std::endl;
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
