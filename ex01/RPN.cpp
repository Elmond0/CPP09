#include "RPN.hpp"

#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

static bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::applyOperator(char op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("not enough operands.");

	int right = _stack.top(); _stack.pop();
	int left  = _stack.top(); _stack.pop();

	int result;
	switch (op)
	{
		case '+': result = left + right; break;
		case '-': result = left - right; break;
		case '*': result = left * right; break;
		case '/':
			if (right == 0)
				throw std::runtime_error("division by zero.");
			result = left / right;
			break;
		default:
			throw std::runtime_error("unknown operator.");
	}
	_stack.push(result);
}

int RPN::evaluate(const std::string& expression)
{
	while (!_stack.empty())
		_stack.pop();

	for (size_t i = 0; i < expression.size(); ++i)
	{
		char c = expression[i];

		if (std::isspace(static_cast<unsigned char>(c)))
			continue;

		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			_stack.push(c - '0');
		}
		else if (isOperator(c))
		{
			applyOperator(c);
		}
		else
		{
			throw std::runtime_error("invalid token.");
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("malformed expression.");

	return _stack.top();
}
