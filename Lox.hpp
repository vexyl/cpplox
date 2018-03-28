#ifndef LOX_H_
#define LOX_H_

#include <string>
#include <vector>

class Lox {
public:
	Lox();

	void error(int line, std::string message);
	void report(int line, std::string where, std::string message);
	void runFile(std::string path);
	void run(std::string input);
	void runPrompt();

private:
	bool m_hadError;
};

#endif // LOX_H_
