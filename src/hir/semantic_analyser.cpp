#include "semantic_analyser.hpp"

#include <sstream>
#include <format>
#include <iostream>

#include "../log.hpp"
#include "../utils.hpp"

namespace HIR {

    template<typename ...Args>
    inline void SemanticAnalyser::error(Expr &expr, Args &&...args) {
        std::ostringstream omsg;

        (omsg << ... << std::forward<Args>(args));
        omsg << "\n";

        size_t padding = 4;
        for (size_t i = 0 ; i < std::to_string(expr->get_line()).size() ; i++) {
            if (padding == 0) { break; }
            padding--;
        }

        for (size_t i = 0 ; i <= padding ; i++) {
            omsg << " ";
        }

        omsg << expr->get_line() << " | " << this->get_line(expr->get_line()) << std::endl;
        
        for (size_t i = 0 ; i <= padding + std::to_string(expr->get_line()).size() ; i++) {
            omsg << " ";
        }
        omsg << " | ";

        size_t index = 0;
        while (index < expr->get_start_col() - 1) {
            omsg << " ";
            index++;
        }
        for (size_t i = 0 ; i < expr->get_end_col() - expr->get_start_col() ; i++) {
            if (i == 0) {
                omsg << "^";
            } else { omsg << "~"; }
        }

        this->do_exit = true;
        LOG_ERROR("line: {0}:{1}: {2}", expr->get_line(), expr->get_start_col(), omsg.str());
    }

    template <typename... Args>
    inline void SemanticAnalyser::warn(Expr &expr, Args &&...args) {
        std::ostringstream omsg;

        (omsg << ... << std::forward<Args>(args));
        omsg << "\n";

        size_t padding = 4;
        for (size_t i = 0 ; i < std::to_string(expr->get_line()).size() ; i++) {
            if (padding == 0) { break; }
            padding--;
        }

        for (size_t i = 0 ; i <= padding ; i++) {
            omsg << " ";
        }

        omsg << expr->get_line() << " | " << this->get_line(expr->get_line()) << std::endl;
        
        for (size_t i = 0 ; i <= padding + std::to_string(expr->get_line()).size() ; i++) {
            omsg << " ";
        }
        omsg << " | ";

        size_t index = 0;
        while (index < expr->get_start_col() - 1) {
            omsg << " ";
            index++;
        }
        for (size_t i = 0 ; i < expr->get_end_col() - expr->get_start_col() ; i++) {
            if (i == 0) {
                omsg << "^";
            } else { omsg << "~"; }
        }

        LOG_WARN("line: {0}:{1}: {2}", expr->get_line(), expr->get_start_col(), omsg.str());
    }

    template <typename... Args>
    inline void SemanticAnalyser::info(Expr &expr, Args &&...args) {
        std::ostringstream omsg;

        (omsg << ... << std::forward<Args>(args));
        omsg << "\n";

        size_t padding = 4;
        for (size_t i = 0 ; i < std::to_string(expr->get_line()).size() ; i++) {
            if (padding == 0) { break; }
            padding--;
        }

        for (size_t i = 0 ; i <= padding ; i++) {
            omsg << " ";
        }

        omsg << expr->get_line() << " | " << this->get_line(expr->get_line()) << std::endl;
        
        for (size_t i = 0 ; i <= padding + std::to_string(expr->get_line()).size() ; i++) {
            omsg << " ";
        }
        omsg << " | ";

        size_t index = 0;
        while (index < expr->get_start_col() - 1) {
            omsg << " ";
            index++;
        }
        for (size_t i = 0 ; i < expr->get_end_col() - expr->get_start_col() ; i++) {
            if (i == 0) {
                omsg << "^";
            } else { omsg << "~"; }
        }

        LOG_INFO("{0}", omsg.str());
    }

    inline void SemanticAnalyser::advance() {
        this->index++;
        if (this->index < this->hir_code.size()) {
            this->current_expr = this->hir_code[this->index];
        }
    }

    void SemanticAnalyser::check(Expr &expr) {
        if (dynamic_cast<Function*>(expr.get())) {
            return this->check_function(expr);
        }

        LOG_ERROR("unreachable, welp you have messed up big time.");
        exit(1);
    }

    void SemanticAnalyser::check_function(Expr &expr) {
        auto function = dynamic_cast<Function*>(expr.get());
        
        for (auto &param : function->params) {
            this->check_param(param);
        }

        bool has_returned = false;
        for (auto &body_expr : function->body) {
            this->check_body_expr(expr, body_expr, function->type, has_returned);
        }
    }

    void SemanticAnalyser::check_param(Expr &expr) {

    }

    void SemanticAnalyser::check_body_expr(Expr &func_expr, Expr &expr, const std::string &type, bool &has_returned) {
        if (has_returned) {
            this->warn(expr, "this code will never be executed");
            LOG_INFO("note: consider removing `return` or something that is blocking/halting the execution of the code.");
        } else {
            auto func = dynamic_cast<Function*>(func_expr.get());
            if (dynamic_cast<Return*>(expr.get())) {
                auto ret = dynamic_cast<Return*>(expr.get());
                has_returned = true;
                if (dynamic_cast<NumberSigned*>(ret->value.get())) {
                    if (type != "i32") {
                        this->error(ret->value, "expected type `", type, "`, found `i32`");
                        this->info(func_expr, "note: function declared here");
                    }
                } else if (dynamic_cast<NumberUnsigned*>(ret->value.get())) {
                    if (type != "u32") {
                        this->error(ret->value, "expected type `", type, "`, found `u32`");
                        this->info(func_expr, "note: function declared here");
                    }
                }
            }
        }
    }

    std::string SemanticAnalyser::get_line(size_t num) {
        std::istringstream stream(this->tokenizer.get_source());

        std::string line;
        size_t current_line = 1;
        while (std::getline(stream, line)) {
            if (current_line == num) {
                return line;
            }

            current_line++;
        }

        return "";
    }


    void SemanticAnalyser::run_checks() {
        while (this->index < this->hir_code.size()) {
            this->check(this->current_expr);
            this->advance();
        }

        if (this->do_exit) { exit(1); }
    }

}