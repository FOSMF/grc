#include "parser_symbol.hpp"

#include "../log.hpp"

namespace GRC {

    inline void ParserSymbol::careless_eat() {
        this->current_token = this->tokenizer.fetch_token();
    }
    
    void ParserSymbol::eat(enum TokenType type) {
        if (this->current_token.value.type != type) {
            LOG_ERROR("line: {0}:{1}: invalid token",
                        this->current_token.row, this->current_token.col);
            exit(1);
        }

        this->careless_eat();
    }

    void ParserSymbol::parse_functions() {
        while (this->current_token.value.type != END_OF_FILE) {
            if (this->current_token.value.type != IDENTIFIER
                && this->current_token.value.value != "fn") {
                this->eat(TokenType::IDENTIFIER);

                std::string name = this->current_token.value.value;
                this->eat(TokenType::IDENTIFIER);

                this->eat(TokenType::LPAREN);
                // TODO: Add support for function arguments
                this->eat(TokenType::RPAREN);

                std::string type = this->current_token.value.value;
                this->eat(TokenType::IDENTIFIER);

                this->table.functions.insert({ name, Function {}
                });
            } else {
                this->careless_eat();
            }
        }
    }

}