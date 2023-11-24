#include "PmergeMe.hpp"

//Créer un ensemble set pour stocker des valeurs uniques en parcourant les arguments
//puis vérifier si la valeur n'est pas déjà présente dans set et est non négative
PmergeMe::PmergeMe(char **argv)
{
	int	val;

	std::set<int> set;
	while (*argv)
	{
		val = std::atoi(*argv);
		if (set.find(val) == set.end() && val >= 0)
		{
			set.insert(val);
			_valDeque.push_back(val);
			_valList.push_back(val);
		}
		else
			throw std::runtime_error("Error");
		argv++;
	}
	_sortedDeque = _valDeque;
	_sortedList = _valList;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
	: _valDeque(copy._valDeque),
		_valList(copy._valList),
		_sortedDeque(copy._sortedDeque),
		_sortedList(copy._sortedList),
		_timeDeque(copy._timeDeque),
		_timeList(copy._timeList)
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		delete (this);
		return (*(new PmergeMe(src)));
	}
	return (*this);
}

const std::deque<int> &PmergeMe::getValDeque() const
{
	return (_valDeque);
}

const std::list<int> &PmergeMe::getValList() const
{
	return (_valList);
}

const std::deque<int> &PmergeMe::getSortedDeque() const
{
	return (_sortedDeque);
}

const std::list<int> &PmergeMe::getSortedList() const
{
	return (_sortedList);
}

double PmergeMe::getTimeDeque() const
{
	return (_timeDeque);
}

double PmergeMe::getTimeList() const
{
	return (_timeList);
}

//comparer deux deques avec le premier element
bool PmergeMe::cmpDeque(const std::deque<int> &a,
		const std::deque<int> &b)
{
	return (a.front() < b.front());
}

//comparer deux listes avec le premier element
bool PmergeMe::cmpList(const std::list<int> &a,
		const std::list<int> &b)
{
	return (a.front() < b.front());
}
