#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "../ast.hpp"

namespace GRC {

    struct SymbolTable {
        std::unordered_map<std::string, Function> functions;
        //std::unordered_map<std::string, Node> variables;
    };

}