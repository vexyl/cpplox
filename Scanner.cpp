#include "Scanner.hpp"

#include <iostream>

Scanner::Scanner(Lox& lox, std::string input) : m_lox(lox), m_input(input)
{
	m_start = 1;
	m_current = 0;
	m_line = 1;

	m_keywords.insert(std::make_pair("and",		AND));
	m_keywords.insert(std::make_pair("class", 	CLASS));
	m_keywords.insert(std::make_pair("else", 	ELSE));
	m_keywords.insert(std::make_pair("false", 	FALSE_));
	m_keywords.insert(std::make_pair("for", 	FOR));
	m_keywords.insert(std::make_pair("fun", 	FUN));
	m_keywords.insert(std::make_pair("if", 		IF));
	m_keywords.insert(std::make_pair("nil", 	NIL));
	m_keywords.insert(std::make_pair("or", 		OR));
	m_keywords.insert(std::make_pair("print", 	PRINT));
	m_keywords.insert(std::make_pair("return",	RETURN));
	m_keywords.insert(std::make_pair("super", 	SUPER));
	m_keywords.insert(std::make_pair("this", 	THIS));
	m_keywords.insert(std::make_pair("true", 	TRUE_));
	m_keywords.insert(std::make_pair("var", 	VAR));
	m_keywords.insert(std::make_pair("while", 	WHILE));
}

std::vector<Token> Scanner::scanTokens()
{
	while (!isAtEnd()) {
		m_start = m_current;
		scanToken();
	}

	m_tokens.push_back(Token(EOF_, "", Object(), m_line));

	return m_tokens;
}

void Scanner::scanToken()
{
	char c = advance();
	switch(c) {
		case '(': addToken(LEFT_PAREN); break;
		case ')': addToken(RIGHT_PAREN); break;
		case '{': addToken(LEFT_BRACE); break;
		case '}': addToken(RIGHT_BRACE); break;
		case ',': addToken(COMMA); break;
		case '.': addToken(DOT); break;
		case '-': addToken(MINUS); break;
		case '+': addToken(PLUS); break;
		case ';': addToken(SEMICOLON); break;
		case '*': addToken(STAR); break;
		case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
		case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
		case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
		case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
		case '/':
			if (match('/')) {
				// C++-style comment
				while (peek() != '\n' && !isAtEnd()) advance();
			} else if (match('*')) {
				// C-style comment
				while (peek() != '*' && !isAtEnd()) advance();
				if (!match('*') || !match('/')) m_lox.error(m_line, "Unterminated C-style comment.");
			} else {
				addToken(SLASH);
			}

			break;
		case ' ':
		case '\t':
		case '\r':
			// ignore whitespace
			break;
		case '\n':
			m_line++;
			break;
		case '"': string(); break;
		default:
			if (isDigit(c)) {
				number();
			} else if (isAlpha(c)) {
				identifier();
			} else {
				m_lox.error(m_line, "Unexpected character.");
			}
			break;
	}
}

void Scanner::identifier()
{
	while (isAlphaNumeric(peek())) advance();

	std::string text = m_input.substr(m_start, m_current - m_start);
	TokenType type = IDENTIFIER;
	auto result = m_keywords.find(text);

	if (result != m_keywords.end())
		type = result->second;

	addToken(type);
}

void Scanner::number()
{
	while (isDigit(peek())) advance();

	// Fractional part
	if (peek() == '.' && isDigit(peekNext())) {
		advance();

		while (isDigit(peek())) advance();
	}

	addToken(NUMBER, std::stod(m_input.substr(m_start, m_current - m_start)));
}

void Scanner::string()
{
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') m_line++;
		advance();
	}

	// Unterminated string
	if (isAtEnd()) {
		m_lox.error(m_line, "Unterminated string.");
		return;
	}

	// Closing quotation mark
	advance();

	std::string value = m_input.substr(m_start + 1, (m_current - 1) - (m_start + 1));
	addToken(STRING, Object(value));
}

bool Scanner::match(char expected)
{
	if (isAtEnd()) return false;
	if (m_input.at(m_current) != expected) return false;

	m_current++;
	return true;
}

char Scanner::peek()
{
	if (isAtEnd()) return '\0';
	return m_input.at(m_current);
}

char Scanner::peekNext()
{
	if (m_current + 1 >= m_input.length()) return '\0';
	return m_input.at(m_current + 1);
}

bool Scanner::isAlpha(char c)
{
	return	(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
	return isAlpha(c) || isDigit(c);
}

bool Scanner::isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool Scanner::isAtEnd()
{
	return m_current >= m_input.length();
}

char Scanner::advance()
{
	m_current++;
	return m_input.at(m_current - 1);
}

void Scanner::addToken(TokenType type)
{
	addToken(type, Object());
}

void Scanner::addToken(TokenType type, Object literal)
{
	std::string text = m_input.substr(m_start, m_current - m_start);

	m_tokens.push_back(Token(type, text, literal, m_line));
}
