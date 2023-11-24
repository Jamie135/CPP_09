#pragma once

# include <ctime>
# include <cmath>
# include <iostream>
# include <deque>
# include <queue>
# include <set>
# include <iterator>
# include <algorithm>
# include <sstream>
# include <string>
# include <list>
# include <iomanip>

class PmergeMe
{
	private:
		std::deque<int>		_valDeque;
		std::list<int>		_valList;
		std::deque<int>		_sortedDeque;
		std::list<int>		_sortedList;
		double				_timeDeque;
		double				_timeList;
	public:
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &src);

		//Getter
		const std::deque<int>		&getValDeque() const;
		const std::list<int>		&getValList() const;
		const std::deque<int>		&getSortedDeque() const;
		const std::list<int>		&getSortedList() const;
		double				getTimeDeque() const;
		double				getTimeList() const;

		//Methods
};
