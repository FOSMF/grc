#include "tokenizer.hpp"

#include <iostream>

#include "log.hpp"

namespace GRC {

	void Tokenizer::advance() {
		this->index++;
		this->ch = this->source[this->index];
		
		if (this->ch == '\n') {
			this->row++;
			this->col = 0;
		} else { this->col++; }
	}

	PositionWrapper<Token> Tokenizer::advance_with(PositionWrapper<Token> tok) {
		this->advance();

		return tok;
	}
	
	PositionWrapper<Token> Tokenizer::lex_ident() {
		size_t row = this->row;
		size_t col = this->col;
		size_t start = this->index;
		while (isalnum(this->ch) && this->index + 1 < this->source.size()) {
			this->advance();
		}
		std::string value = this->source.substr(start, this->index - start);
		
		return PositionWrapper<Token>({
				.type = IDENTIFIER,
				.value = value,
			}, row, col);
	}

	PositionWrapper<Token> Tokenizer::lex_num() {
		size_t row = this->row;
		size_t col = this->col;
		size_t start = this->index;
		while (isdigit(this->ch) && this->index + 1 < this->source.size()) {
			this->advance();
		}
		std::string value = this->source.substr(start, this->index - start);

		return PositionWrapper<Token>({
				.type = NUMBER,
				.value = value,
			}, row, col);
	}

	PositionWrapper<Token> Tokenizer::fetch_token() {
		if (this->index < this->source.size()) {
			// Skips whitespace as they are not needed, this isn't python.
			while (isspace(this->ch)) { this->advance(); }
			
			// Some quick checks to see if we should lex it as ident or num.
			if (isalpha(this->ch)) { return lex_ident(); }
			if (isdigit(this->ch)) { return lex_num(); }

			// Organizing single chars into valid tokens.
			switch (this->ch) {
				case '(': return this->advance_with(PositionWrapper<Token>({
						.type = LPAREN,
						.value = "(",
					}, this->row, this->col));
				case ')': return this->advance_with(PositionWrapper<Token>({
						.type = RPAREN,
						.value = ")",
					}, this->row, this->col));
				case '{': return this->advance_with(PositionWrapper<Token>({
						.type = LCURLY,
						.value = "{",
					}, this->row, this->col));
				case '}': return this->advance_with(PositionWrapper<Token>({
						.type = RCURLY,
						.value = "}",
					}, this->row, this->col));
				case ';': return this->advance_with(PositionWrapper<Token>({
						.type = SEMICOLON,
						.value = ";",
					}, this->row, this->col));
				default:
					{
						LOG_ERROR("line: {0}:{1}: invalid token `{2}`", this->row, this->col, this->ch);
						exit(1);
					} break;
			}
		}

		// EOF
		return PositionWrapper<Token>({
			.type = END_OF_FILE,
			.value = "?",
		}, this->row, this->col);
	}
	
}