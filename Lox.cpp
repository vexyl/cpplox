#include "Lox.hpp"
#include "Scanner.hpp"
#include "Token.hpp"

#include <iostream>
#include <fstream>

Lox::Lox() : m_hadError(false)
{

}

void Lox::error(int line, std::string message)
{
	report(line, "", message);
}

void Lox::report(int line, std::string where, std::string message)
{
	std::cout << "[line " << line << "] Error" \
		<< where << ": " <<  message << std::endl;

	m_hadError = true;
}

void Lox::runFile(std::string path)
{
	std::ifstream file(path);
	std::string input;

	std::string tmp;
	while (getline(file, tmp)) {
		if (!input.empty()) input += '\n';
		input += tmp;
	}

	run(input);

	if (m_hadError)
		exit(65);
}

void Lox::run(std::string input)
{
	Scanner scanner(*this, input);

	std::vector<Token> tokens = scanner.scanTokens();

	for (auto& token : tokens)
		std::cout << token.toString() << std::endl;
}

void Lox::runPrompt()
{
	std::cout << "Running prompt..." << std::endl;
	std::string input;
	std::cout << "> ";
	while (std::getline(std::cin, input)) {
		run(input);
		m_hadError = false;

		std::cout << "> ";
	}
}
