#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>

// Evaluates a Reverse Polish Notation expression using a stack.
class RPN
{
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		// Evaluates the given RPN expression.
		// Throws std::runtime_error on any malformed expression.
		int evaluate(const std::string& expression);

	private:
		std::stack<int> _stack;

		// Applies the operator op to the top two operands on the stack.
		void applyOperator(char op);
};

#endif
