#include "utils.hpp"
#include <bits/stdc++.h>

#include <cppitertools/combinations.hpp>
#include <z3++.h>

struct Machine
{
    int              target = 0;
    std::vector<int> buttons;
    std::vector<int> joltages;

    static Machine fromString(std::string_view input)
    {
        Machine machine;

        auto parts = utils::stringSplit(input, ' ');
        for (auto &part : parts) {
            if (part.starts_with('[')) {
                machine.target = 0;
                for (size_t i = 1; i < part.size() - 1; i++) {
                    if (part[i] == '#')
                        machine.target |= 1 << (i - 1);
                }
            } else if (part.starts_with('(')) {
                auto ns  = utils::stringSplit(part.substr(1, part.size() - 2), ',');
                int  btn = 0;
                for (const auto &nStr : ns)
                    btn |= 1 << std::stoi(nStr);
                machine.buttons.push_back(btn);
            } else if (part.starts_with('{')) {
                for (auto &nStr : utils::stringSplit(part.substr(1, part.size() - 2), ',')) {
                    machine.joltages.emplace_back(std::stoi(nStr));
                }
            }
        }

        return machine;
    }
};

void part1(const std::string &filename)
{
    std::ifstream        file(filename);
    std::string          line;
    std::vector<Machine> machines;
    int32_t              result = 0;

    while (std::getline(file, line)) {
        machines.emplace_back(Machine::fromString(line));
    }

    for (const auto &machine : machines) {
        for (size_t c = 0; c < machine.buttons.size(); c++) {
            for (const auto &comb : iter::combinations(machine.buttons, c + 1)) {
                int current = 0;
                for (const auto &btn : comb)
                    current ^= btn;
                if (current == machine.target) {
                    result += static_cast<int32_t>(c + 1);
                    goto break_loop;
                }
            }
        }
    break_loop:
        continue;
    }

    std::println("Part 1 : {}", result);
}

void part2(const std::string &filename)
{
    std::ifstream        file(filename);
    std::string          line;
    std::vector<Machine> machines;
    int64_t              result = 0;

    while (std::getline(file, line)) {
        machines.emplace_back(Machine::fromString(line));
    }

    for (const auto &machine : machines) {
        auto            ctx = z3::context();
        auto            o   = z3::optimize(ctx);
        z3::expr_vector vars(ctx);

        for (size_t i = 0; i < machine.buttons.size(); i++) {
            vars.push_back(ctx.int_const(std::format("n{}", i).c_str()));
        }

        z3::expr_vector eq(ctx);
        for (size_t i = 0; i < machine.joltages.size(); i++) {
            z3::expr_vector terms(ctx);
            for (size_t j = 0; j < machine.buttons.size(); j++) {
                if ((1 << i) & machine.buttons[j])
                    terms.push_back(vars[j]);
            }
            auto e = z3::sum(terms) == machine.joltages[i];
            eq.push_back(e);
        }

        const auto sum = z3::sum(vars);
        o.minimize(sum);
        for (auto e : eq)
            o.add(e);
        for (auto v : vars)
            o.add(v >= 0);
        o.check();
        result += o.get_model().eval(sum).as_int64();
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
