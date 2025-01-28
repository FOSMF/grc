#pragma once

#include <string>
#include <vector>

namespace GRC {

    class Utils {
    public:
        static int is_similar(const std::string &w1, const std::string &w2);
        static std::string find_closest_word(const std::vector<std::string> &words, const std::string &word);
    };

}