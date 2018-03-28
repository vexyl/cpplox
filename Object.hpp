#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

class Object {
public:
	enum ObjectType { kNone, kString, kNumber };

	Object() : m_type(kNone), decimalLiteral(0.0f) { }
	Object(std::string value) : m_type(kString), stringLiteral(value), decimalLiteral(0.0f) { }
	Object(double value) : m_type(kNumber), decimalLiteral(value) { }

	std::string toString()
	{
		if (m_type == kNone) return "None";
		if (m_type == kString) return stringLiteral;
		if (m_type == kNumber) return std::to_string(decimalLiteral);
	}

private:
	ObjectType m_type;

	std::string stringLiteral;
	double decimalLiteral;
};

#endif // OBJECT_H_
