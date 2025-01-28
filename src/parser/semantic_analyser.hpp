#pragma once

#include "symbol_table.hpp"
#include "../tokenizer.hpp"

namespace GRC {

    class SemanticAnalyser {
    public:
        SemanticAnalyser(SymbolTable &table, Tokenizer tokenizer)
            : table(table), tokenizer(tokenizer) {}

        void run_checks();
    private:
        void advance();
        
        void check();

        void validate_type(std::string type);

        void check_ident();
        void check_function();

        template<typename ...Args>
        inline void error(Args &&...args);

        std::string get_line(size_t num);
    private:
        SymbolTable &table;

        bool do_exit = false;
        
        Tokenizer tokenizer;
        PositionWrapper<Token> current_token = this->tokenizer.fetch_token();
    };

}