#ifndef TOKEN_H_
#define TOKEN_H_

#include "TokenType.hpp"
#include "Object.hpp"

#include <string>

class Token {
public:
	Token(TokenType type, std::string lexeme, Object literal, int line)
		: m_type(type), m_lexeme(lexeme), m_literal(literal), m_line(line) { }

	std::string toString()
	{
		return "Token [type: " + std::to_string(m_type) + ", line: " + std::to_string(m_line) + "] lexeme=" + m_lexeme + " | " + "literal='" + m_literal.toString() + "'";
	}

private:
	TokenType m_type;
	std::string m_lexeme;
	Object m_literal;
	int m_line;
};

#endif // TOKEN_H_
