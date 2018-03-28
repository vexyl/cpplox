#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.hpp"
#include "Lox.hpp"
#include "Object.hpp"

#include <string>
#include <vector>
#include <map>

class Scanner {
public:
	Scanner(Lox& lox, std::string input);

	std::vector<Token> scanTokens();
	void scanToken();
	void identifier();
	void number();
	void string();
	bool match(char expected);
	char peek();
	char peekNext();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool isDigit(char c);
	bool isAtEnd();
	char advance();
	void addToken(TokenType type);
	void addToken(TokenType type, Object literal);

private:
	Lox& m_lox;
	std::string m_input;
	std::vector<Token> m_tokens;
	int m_start, m_current, m_line;
	std::map<std::string, TokenType> m_keywords;
};

#endif // SCANNER_H_
