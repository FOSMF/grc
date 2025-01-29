#pragma once

#include <unordered_map>
#include <tuple>
#include <memory>
#include <string>

#include "../ast.hpp"

namespace GRC {

    struct SymbolTable {
        std::unordered_map<std::string, std::tuple<size_t, Function>> functions;
        //std::unordered_map<std::string, Node> variables;
    };

}