#pragma once

#include <string>

enum TokenType {
	// Types
	IDENTIFIER = 0,
	NUMBER,

	// Delimiters
	LPAREN,
	RPAREN,
	LCURLY,
	RCURLY,
	SEMICOLON,

	// Other
	END_OF_FILE,
};

struct Token {
	enum TokenType type;
	std::string value;
};

// PositionWrapper is used mainly in error messages
// as it provides easier access of the token's position
template<typename T>
struct PositionWrapper {
	PositionWrapper(T val, size_t r, size_t c)
		: value(val), row(r), col(c) {}
public:
	T value;
	size_t row;
	size_t col;
};

namespace GRC {

	// The tokenizer organizes each piece of text in a file
	// into a token if valid.
	class Tokenizer {
	public:
		Tokenizer(std::string src)
			: source(src), ch(src[0]) {}
	
		PositionWrapper<Token> fetch_token();
	private:
		void advance();
		PositionWrapper<Token> advance_with(PositionWrapper<Token> tok);

		PositionWrapper<Token> lex_ident();
		PositionWrapper<Token> lex_num();
	private:
		std::string source;
		size_t index = 0;
		char ch;

		size_t row = 1;
		size_t col = 1;
	};

}