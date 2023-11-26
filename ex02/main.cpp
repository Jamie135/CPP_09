#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	try {
		PmergeMe p(argv + 1);
		p.merge_insertion_Deque();
		p.merge_insertion_List();
		std::cout << "Before: ";
		const std::deque<int> original = p.getValDeque();
		for (size_t i = 0; i < original.size(); i++)
			std::cout << original[i] << " ";
		std::cout << std::endl;
		std::cout << "After: ";
		const std::deque<int> sorted = p.getSortedDeque();
		std::list<int> sortedList = p.getSortedList();
		std::list<int>::iterator it;
		for (it = sortedList.begin(); it != sortedList.end(); ++it) {
			std::cout << *it << " ";
		}
		// for (size_t i = 0; i < sorted.size(); i++)
		// 	std::cout << sorted[i] << " ";
		std::cout << std::endl;
		std::cout << "Time to process a rance of " << original.size()
			<< " elements with std::deque : "
			<< std::fixed << p.getTimeDeque() << std::setprecision(5)
			<< std::endl;
		std::cout << "Time to process a rance of " << original.size()
			<< " elements with std::list : "
			<< std::fixed << p.getTimeList() << std::setprecision(5)
			<< std::endl;
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
