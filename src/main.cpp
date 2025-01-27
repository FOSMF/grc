#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "tokenizer.h"
#include "log.h"

using namespace GRC;

static std::string get_file_contents(std::string path) {
	std::ifstream file(path);
	std::ostringstream buf;

	buf << file.rdbuf();

	file.close();
	return buf.str();
}

static void usage(char *program) {
	INFO("usage: grc [FILES] +[ARGUMENT]..");
	std::cout << "[ARGUMENTS]:"														<< std::endl;
	std::cout << "  -  toolchain [TOOLCHAIN]"										<< std::endl;
	std::cout << "  -  output-assembly"												<< std::endl;
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
		ERROR("no arguments provided");
		exit(1);
	}

	std::vector<std::string> files;
	while (argc > 0) {
		std::string arg = shift(argc, &argv);

		if (arg.starts_with('+')) {
			if (arg == "+toolchain") {

			} else if (arg == "+show-assembly") {

			} else {
				usage(program);
				ERROR("invalid flag `{0}`", arg);
				exit(1);
			}
		} else {
			files.push_back(arg);
		}
	}

	for (auto &file : files) {
		Tokenizer tokenizer(get_file_contents(file));
		PositionWrapper<Token> token = tokenizer.fetch_token();

		while (token.value.type != END_OF_FILE) {
			std::cout << "token: `" << token.value.value << "`, type: "
				<< token.value.type << ", row: " << token.row << ", col: " << token.col
				<< std::endl;
			token = tokenizer.fetch_token();
		}
	}
}