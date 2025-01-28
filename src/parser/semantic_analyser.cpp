#include "semantic_analyser.hpp"

#include <sstream>
#include <format>
#include <iostream>

#include "../log.hpp"
#include "../utils.hpp"

namespace GRC {

    template<typename ...Args>
    inline void SemanticAnalyser::error(Args &&...args) {
        std::ostringstream omsg;

        (omsg << ... << std::forward<Args>(args));

        omsg << "\n    " << this->current_token.row << " | " << this->get_line(this->current_token.row) << std::endl
             << "      | ";

        size_t index = 0;
        while (index < this->current_token.col - 1) {
            omsg << " ";
            index++;
        }
        for (size_t i = 0 ; i < this->current_token.unwrap().value.size() ; i++) {
            if (i == 0) {
                omsg << "^";
            } else { omsg << "~"; }
        }

        this->do_exit = true;
        LOG_ERROR("line: {0}:{1}: {2}", this->current_token.row, this->current_token.col, omsg.str());
    }

    std::vector<std::string> valid_keywords = {
        "fn", "return"
    };

    void SemanticAnalyser::advance() {
        this->current_token = this->tokenizer.fetch_token();
    }

    void SemanticAnalyser::check() {
        switch (this->current_token.unwrap().type) {
        case IDENTIFIER: this->check_ident(); break;
        default: {
                this->error("invalid syntax `", this->current_token.unwrap().value, "`");
            } break;
        }
    }

    void SemanticAnalyser::validate_type(std::string type) {
        if (type != "i32") {
            this->error("invalid type `", type, "`");
        }
    }

    void SemanticAnalyser::check_function() {
        this->advance();

        if (this->current_token.unwrap().type != IDENTIFIER) {
            this->error("expected valid identifier, found: ", ttype_to_str(this->current_token.unwrap().type));
        }
        
        this->advance();
        if (this->current_token.unwrap().type != LPAREN) {
            this->error("expected '(' after function identifier, found `", this->current_token.unwrap().value, "`");
        }

        this->advance();
        if (this->current_token.unwrap().type != RPAREN) {
            this->error("expected ')' after function identifier, found `", this->current_token.unwrap().value, "`");
        }

        this->advance();

        this->validate_type(this->current_token.unwrap().value);
        
        this->advance();
        if (this->current_token.unwrap().type != LCURLY) {
            this->error("expected '{' after type, found: ", ttype_to_str(this->current_token.unwrap().type));
        }

        this->advance();
        while (this->current_token.unwrap().type != RCURLY
                && this->current_token.unwrap().type != END_OF_FILE) {
            this->check();

            this->advance();
        }

        if (this->current_token.unwrap().type == END_OF_FILE) {
            this->error("function scope does not end, found EOF instead");
        }
    }

    void SemanticAnalyser::check_ident() {
        if (this->current_token.unwrap().value == "fn") {
            this->check_function();
        } else if (this->current_token.unwrap().value == "return") {
            this->advance();
            
            this->advance();
            if (this->current_token.unwrap().type != SEMICOLON) {
                this->error("expected ';' at the end of statement");
            }
        } else {
            std::string closest = Utils::find_closest_word(valid_keywords, this->current_token.unwrap().value);
            if (closest.empty()) {
                this->error("invalid keyword `", this->current_token.unwrap().value, "`");
            } else {
                this->error("invalid keyword `", this->current_token.unwrap().value, "`, did you mean `",
                    Utils::find_closest_word(valid_keywords, this->current_token.unwrap().value), "`?");
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

        LOG_ERROR("unexpected: failed to get line: {0}", num);
        exit(1);
    }


    void SemanticAnalyser::run_checks() {
        while (this->current_token.unwrap().type != END_OF_FILE) {
            this->check();

            this->advance();
        }

        if (this->do_exit) { exit(1); }
    }

}