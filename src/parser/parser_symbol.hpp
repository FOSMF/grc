#pragma once

#include "symbol_table.hpp"
#include "../tokenizer.hpp"

namespace GRC {

    class ParserSymbol {
    public:
        ParserSymbol(SymbolTable &table, Tokenizer &tokenizer)
            : table(table), tokenizer(tokenizer), current_token(tokenizer.fetch_token()) {}

        void parse_functions();
    private:
        void careless_eat();
        void eat(enum TokenType type);
    private:
        SymbolTable &table;

        Tokenizer &tokenizer;
        PositionWrapper<Token> current_token;
    };

}