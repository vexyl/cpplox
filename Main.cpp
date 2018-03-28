#include "Lox.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	Lox lox;

	if (argc > 2) {
		std::cout << "Usage: cpplox [script]" << std::endl;
	} else if (argc == 2) {
		lox.runFile(argv[1]);
	} else {
		lox.runPrompt();
	}

	return 0;
}
