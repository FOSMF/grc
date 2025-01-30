#include "mir_codegen.hpp"

#include <iostream>

#include "../log.hpp"

namespace HIR { 

    void MIRCodegen::advance() {
        this->index++;
        if (this->index < this->hir_code.size()) {
            this->current_expr = this->hir_code[this->index];
        }
    }

    MIR::Expr MIRCodegen::generate_function(Expr &func_expr) {
        auto function = dynamic_cast<Function*>(func_expr.get());

        MIR::ExprList params;
        for (auto param : function->params) {
            params.push_back(this->generate_expr_no_blocks(param, function->type));
        }

        std::vector<MIR::Block> blocks;

        blocks.push_back(MIR::Block("entry"));
        for (auto expr : function->body) {
            blocks[blocks.size() - 1].body.push_back(this->generate_expr(expr, function->type, blocks));
        }


        return std::make_shared<MIR::Function>(MIR::Function(
            function->name, function->type, params, blocks, function->line, function->start_col, function->end_col));
    }

    MIR::Expr MIRCodegen::generate_return(const std::string &type, Expr &ret_expr, std::vector<MIR::Block> &blocks) {
        auto ret = dynamic_cast<Return*>(ret_expr.get());

        MIR::Expr value = this->generate_expr(ret->value, type, blocks);

        return std::make_shared<MIR::Return>(MIR::Return(type, value, ret->line, ret->start_col, ret->end_col));
    }

    MIR::Expr MIRCodegen::generate_expr(Expr &expr, const std::string &type, std::vector<MIR::Block> &blocks) {
        if (dynamic_cast<Return*>(expr.get())) {
            return this->generate_return(type, expr, blocks);
        } else if (auto num = dynamic_cast<NumberSigned*>(expr.get())) {
            return std::make_shared<MIR::NumberSigned>(num->value, num->line, num->start_col, num->end_col);
        } else if (auto num = dynamic_cast<NumberUnsigned*>(expr.get())) {
            return std::make_shared<MIR::NumberUnsigned>(num->value, num->line, num->start_col, num->end_col);
        }

        LOG_ERROR("unreachable, welp you have messed up big time.");
        exit(1);
    }

    MIR::Expr MIRCodegen::generate_expr_no_blocks(Expr &expr, const std::string &type) {
        if (dynamic_cast<Function*>(expr.get())) {
            return this->generate_function(expr);
        }

        LOG_ERROR("unreachable, welp you have messed up big time.");
        exit(1);
    }

    void MIRCodegen::generate() {
        while (this->index < this->hir_code.size()) {
            this->mir_code.push_back(this->generate_expr_no_blocks(this->current_expr, "undefined"));
            this->advance();
        }
    }
    
}