#pragma once

#include <vector>
#include <memory>

#include "symbol_table.hpp"
#include "../tokenizer.hpp"
#include "../ast.hpp"

namespace GRC {

    class ParserAST {
    public:
        ParserAST(SymbolTable &table, Tokenizer tokenizer)
            : table(table), tokenizer(tokenizer) {}

        NodeList parse_ast();
    private:
        Node parse_expr();
        Node parse_ident();

        void careless_eat();
        void eat(TokenType type);
    private:
        SymbolTable &table;

        Tokenizer tokenizer;
        PositionWrapper<Token> current_token = this->tokenizer.fetch_token();
    };

}