#include "parser_symbol.hpp"

#include "../log.hpp"

#include <iostream>

namespace GRC {

    void ParserSymbol::careless_eat() {
        this->current_token = this->tokenizer.fetch_token();
    }
    
    void ParserSymbol::eat(TokenType type) {
        if (this->current_token.unwrap().type != type) {
            LOG_ERROR("line: {0}:{1}: expected: {2}, found: {3}",
                        this->current_token.row, this->current_token.col,
                        ttype_to_str(type), ttype_to_str(this->current_token.unwrap().type));
            exit(1);
        }

        this->careless_eat();
    }

    void ParserSymbol::parse_functions() {
        while (this->current_token.unwrap().type != END_OF_FILE) {
            if (this->current_token.unwrap().type == IDENTIFIER
                && this->current_token.unwrap().value == "fn") {
                this->eat(IDENTIFIER);

                std::string name = this->current_token.unwrap().value;
                this->eat(IDENTIFIER);

                this->eat(LPAREN);
                // TODO: Add support for function arguments
                this->eat(RPAREN);

                std::string type = this->current_token.unwrap().value;
                this->eat(IDENTIFIER);

                this->table.functions.insert({ name, Function(name, type) });
            } else {
                this->careless_eat();
            }
        }
    }

}