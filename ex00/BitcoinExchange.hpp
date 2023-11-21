#pragma once

# include <map>
# include <vector>
# include <sstream>
# include <string>
# include <iostream>
# include <fstream>
# include <cstdlib>
# include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<int, float> _data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange &src);

		int			setDate(std::string &strDate);
		void		readFile(const std::string &filePath);
		std::string	trimSpace(std::string &str);
		std::string	trimFront(std::string &str);
		void		processLine(std::vector<std::string> &line);
};
