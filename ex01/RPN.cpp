#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &copy) : _values(copy._values)
{}

RPN &RPN::operator=(const RPN &src)
{
	if (&src != this)
		_values = src._values;
	return (*this);
}

RPN::~RPN() {}

void	RPN::calculate(const std::string &str)
{
	std::string			op;
	std::stringstream	s(str);

	while (std::getline(s, op, ' ')) //parcourir chaque element de l'operation
	{
		if (!checkOp(op)) //verifier la validite
			throw std::runtime_error("Invalid operand/operator.");
		if (std::isdigit((op)[0])) //si c'est un nombre, il est converti en entier et empiler
			_values.push(std::atoi((op).c_str()));
		else //si c'est un operateur, les deux dernières valeurs sont défilées du stack, on effectue l'operation puis le resultat est empiler
		{
			if (_values.size() < 2)
				throw std::runtime_error("Operation cannot be executed.");
			int	a = _values.top();
			_values.pop();
			int	b = _values.top();
			_values.pop();
			_values.push(execOp(a, b, (op)[0]));
		}
	}
	if (_values.size() != 1)
		throw std::runtime_error("Invalid size at result.");
	std::cout << _values.top() << std::endl;
	_values.pop();
}

bool	RPN::checkOp(const std::string &str)
{
	if (str.size() != 1)
		return (false);
	if (std::isdigit(str[0]))
		return (true);
	if (str[0] == '/' || str[0] == '*' || str[0] == '+' || str[0] == '-')
		return (true);
	return (false);
}

int		RPN::execOp(int a, int b, char operation)
{
	if (operation == '*')
		return (a * b);
	else if (operation == '/')
	{
		if (a == 0)
			throw std::runtime_error("Cannot divide by zero!");
		return (b / a);
	}
	else if (operation == '+')
		return (a + b);
	else
		return (b - a);
}
