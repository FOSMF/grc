#pragma once

#include "../parser/symbol_table.hpp"
#include "../tokenizer.hpp"
#include "expr.hpp"

namespace HIR {

    class SemanticAnalyser {
    public:
        SemanticAnalyser(GRC::SymbolTable &table, GRC::Tokenizer tokenizer, ExprList &hir_code)
            : table(table), hir_code(hir_code), current_expr(hir_code[0]), tokenizer(tokenizer) {}

        void run_checks();
    private:
        inline void advance();
        
        void check(Expr &expr);

        void check_function(Expr &expr);
        void check_param(Expr &expr);
        void check_body_expr(Expr &func_expr, Expr &expr, const std::string &type, bool &has_returned);

        template<typename ...Args>
        inline void error(Expr &expr, Args &&...args);

        template<typename ...Args>
        inline void warn(Expr &expr, Args &&...args);

        template<typename ...Args>
        inline void info(Expr &expr, Args &&...args);

        std::string get_line(size_t num);
    private:
        GRC::SymbolTable &table;

        ExprList &hir_code;
        Expr &current_expr;
        size_t index = 0;

        GRC::Tokenizer tokenizer;

        bool do_exit = false;
    };

}