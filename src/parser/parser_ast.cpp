#include "parser_ast.hpp"

#include "../log.hpp"

namespace GRC {

    void ParserAST::careless_eat() {
        this->current_token = this->tokenizer.fetch_token();
    }
    
    void ParserAST::eat(TokenType type) {
        if (this->current_token.unwrap().type != type) {
            LOG_ERROR("line: {0}:{1}: expected: {2}, found: {3}",
                        this->current_token.row, this->current_token.col,
                        ttype_to_str(type), ttype_to_str(this->current_token.unwrap().type));
            exit(1);
        }

        this->careless_eat();
    }

    Node ParserAST::parse_ident() {
        if (this->current_token.unwrap().value == "fn") {
            this->eat(IDENTIFIER);

            std::string name = this->current_token.unwrap().value;
            this->eat(IDENTIFIER);

            NodeList params;
            this->eat(LPAREN);
            // TODO: implement parameters
            this->eat(RPAREN);

            std::string type = this->current_token.unwrap().value;
            this->eat(IDENTIFIER);

            this->eat(LCURLY);
            NodeList body;
            while (this->current_token.unwrap().type != RCURLY
                    && this->current_token.unwrap().type != END_OF_FILE) {
                body.push_back(this->parse_expr());
            }
            this->eat(RCURLY);

            return std::make_unique<Function>(Function(name, type, std::move(params), std::move(body)));
        } else if (this->current_token.unwrap().value == "return") {
            this->eat(IDENTIFIER);

            Node value = this->parse_expr();
            this->eat(SEMICOLON);

            return std::make_unique<Return>(Return(std::move(value)));
        }

        LOG_ERROR("line: {0}:{1}: invalid keyword `{2}`",
            this->current_token.row, this->current_token.col,
            this->current_token.unwrap().value);
        exit(1);
    }

    Node ParserAST::parse_expr() {
        switch (this->current_token.unwrap().type) {
        case IDENTIFIER: return parse_ident();
        case NUMBER: {
                std::string value = this->current_token.unwrap().value;
                this->eat(NUMBER);

                return std::make_unique<Number>(Number(value));
            };
        default: {
                LOG_ERROR("line: {0}:{1}: invalid token type to parse: {2}",
                    this->current_token.row, this->current_token.col,
                    ttype_to_str(this->current_token.unwrap().type));
                exit(1);
            } break;
        }
    }

    NodeList ParserAST::parse_ast() {
        NodeList ast;
        while (this->current_token.unwrap().type != END_OF_FILE) {
            ast.push_back(parse_expr());
        }

        return ast;
    }

}