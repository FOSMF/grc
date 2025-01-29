#pragma once

#include "../ast.hpp"
#include "../hir/expr.hpp"

namespace GRC {

    class HIRCodegen {
    public:
        HIRCodegen(NodeList &ast)
            : ast(ast), current_node(ast[0]) {}

        void generate();
    public:
        HIR::ExprList &get_hir_code() { return this->hir_code; }
    private:
        HIR::Expr generate_expr(Node &node);

        HIR::Expr generate_function(Node &func_node);
        HIR::Expr generate_return(Node &ret_node);
        
        void advance();
    private:
        NodeList &ast;
        Node &current_node;
        size_t index = 0;

        HIR::ExprList hir_code;
    };

}