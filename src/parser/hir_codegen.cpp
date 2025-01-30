#include "hir_codegen.hpp"

#include <iostream>

#include "../log.hpp"

namespace GRC { 

    void HIRCodegen::advance() {
        this->index++;
        if (this->index < this->ast.size()) {
            this->current_node = this->ast[this->index];
        }
    }

    HIR::Expr HIRCodegen::generate_function(Node &func_node) {
        auto function = dynamic_cast<Function*>(func_node.get());

        HIR::ExprList params;
        for (auto param : function->params) {
            params.push_back(this->generate_expr(param));
        }

        HIR::ExprList body;
        for (auto node : function->body) {
            body.push_back(this->generate_expr(node));
        }

        return std::make_shared<HIR::Function>(HIR::Function(
            function->name, function->type, params, body, function->line, function->start_col, function->end_col));
    }

    HIR::Expr HIRCodegen::generate_return(Node &ret_node) {
        auto ret = dynamic_cast<Return*>(ret_node.get());

        HIR::Expr value = this->generate_expr(ret->value);

        return std::make_shared<HIR::Return>(HIR::Return(value, ret->line, ret->start_col, ret->end_col));
    }

    HIR::Expr HIRCodegen::generate_expr(Node &node) {
        if (dynamic_cast<Function*>(node.get())) {
            return this->generate_function(node);
        } else if (dynamic_cast<Return*>(node.get())) {
            return this->generate_return(node);
        } else if (auto num = dynamic_cast<Number*>(node.get())) {
            return std::make_shared<HIR::NumberSigned>(std::stoi(num->value), num->line, num->start_col, num->end_col);
        }

        LOG_ERROR("unreachable, welp you have messed up big time.");
        exit(1);
    }

    void HIRCodegen::generate() {
        while (this->index < this->ast.size()) {
            this->hir_code.push_back(this->generate_expr(this->current_node));
            this->advance();
        }
    }
    
}