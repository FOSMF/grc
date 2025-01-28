#pragma once

#include "symbol_table.hpp"
#include "../tokenizer.hpp"

namespace GRC {

    // First parser pass through, meant getting function symbols.
    class ParserSymbol {
    public:
        ParserSymbol(SymbolTable &table, Tokenizer tokenizer)
            : table(table), tokenizer(tokenizer) {}

        void parse_functions();
    private:
        void careless_eat();
        void eat(TokenType type);
    private:
        SymbolTable &table;

        Tokenizer tokenizer;
        PositionWrapper<Token> current_token = this->tokenizer.fetch_token();
    };

}