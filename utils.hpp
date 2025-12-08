#pragma once

#include <string>
#include <vector>

namespace utils {

std::vector<std::string> stringSplit(std::string_view sv, char delimiter = ' ', bool keepEmpty = false)
{
    std::vector<std::string> ret;
    std::size_t              pos      = 0;
    std::size_t              startPos = 0;

    while ((pos = sv.find(delimiter, startPos)) != std::string_view::npos) {
        ret.emplace_back(sv.substr(startPos, pos - startPos));
        startPos = pos + 1;
    }
    ret.emplace_back(sv.substr(startPos));

    return ret;
}

} // namespace utils
