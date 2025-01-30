#pragma once

#include "expr.hpp"
#include "../mir/expr.hpp"

namespace HIR {

    class MIRCodegen {
    public:
        MIRCodegen(ExprList &hir_code)
            : hir_code(hir_code), current_expr(hir_code[0]) {}

        void generate();
    public:
        MIR::ExprList &get_mir_code() { return this->mir_code; }
    private:
        MIR::Expr generate_expr(Expr &expr, const std::string &type);

        MIR::Expr generate_function(Expr &func_expr);
        MIR::Expr generate_return(const std::string &type, Expr &ret_expr);
        
        void advance();
    private:
        ExprList &hir_code;
        Expr &current_expr;
        size_t index = 0;

        MIR::ExprList mir_code;
    };

}