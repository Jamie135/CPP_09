#pragma once

# include <stack>
# include <list>
# include <string>
# include <sstream>
# include <iostream>
# include <stdexcept>
# include <cstdlib>

class RPN
{
	private:
		std::stack<int> _values;
	public:
		RPN();
		RPN(const RPN &copy);
		~RPN();
		RPN &operator=(const RPN &src);
		void calculate(const std::string &str);
		bool	checkOp(const std::string &str);
		int		execOp(int a, int b, char operation);
};
