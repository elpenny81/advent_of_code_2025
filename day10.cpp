#include <bits/stdc++.h>

void part1(const std::string &filename)
{
    // TODO: implementation
    int32_t result = 0;
    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    // TODO: implementation
    int32_t result = 0;
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
