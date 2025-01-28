#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "log.hpp"

#include "tokenizer.hpp"
#include "parser/parser_symbol.hpp"
#include "parser/parser_ast.hpp"

using namespace GRC;

static std::string get_file_contents(std::string path) {
	std::ifstream file(path);
	std::ostringstream buf;

	buf << file.rdbuf();

	file.close();
	return buf.str();
}

static void usage(char *program) {
	LOG_INFO("usage: {0} [FILES] +[ARGUMENT]..", program);
	std::cout << "[ARGUMENTS]:"														<< std::endl;
	std::cout << "  -  toolchain [TOOLCHAIN]"										<< std::endl;
	std::cout << "  -  output [OUTPUT]"												<< std::endl;
	std::cout << "  -  assembly"													<< std::endl;
	std::cout << "[TOOLCHAINS]:"													<< std::endl;
	std::cout << "  -  x86_64-unknown-gcc = links object files with standard gcc"	<< std::endl;
}

static char *shift(int &argc, char ***argv) {
	char *arg = **argv;
	argc--;
	(*argv)++;
	return arg;
}

int main(int argc, char **argv) {
	Log::init();

	char *program = shift(argc, &argv);

	if (argc < 1) {
		usage(program);
		LOG_ERROR("no arguments provided");
		exit(1);
	}

	std::vector<std::string> files;
	while (argc > 0) {
		std::string arg = shift(argc, &argv);

		if (arg.starts_with('+')) {
			if (arg == "+toolchain") {

			} else if (arg == "+output") {
				std::string out = shift(argc, &argv);
			} else if (arg == "+assembly") {

			} else {
				usage(program);
				LOG_ERROR("invalid flag `{0}`", arg);
				exit(1);
			}
		} else {
			files.push_back(arg);
		}
	}

	for (auto &file : files) {
		Tokenizer tokenizer(get_file_contents(file));
		SymbolTable symbol_table;
		ParserSymbol symbol_parser(symbol_table, tokenizer);
		symbol_parser.parse_functions();

		ParserAST ast_parser(symbol_table, tokenizer);
		for (auto &node : ast_parser.parse_ast()) {
			std::cout << node->to_string() << std::endl;
		}
	}
}