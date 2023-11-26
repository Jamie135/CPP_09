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

void PmergeMe::merge_insertion_Deque()
{
	bool			oddFlag = false;
	int				separated;
	int				bsLimit;
	clock_t			start;
	clock_t			end;

	oddFlag = false;
	std::deque<int> cpyvalDeque;
	std::deque<std::deque<int>> pairs;
	std::deque<int> sorted;
	std::deque<int> tosort;
	cpyvalDeque = _valDeque;
	start = clock();
	//cas ou deque est de taille 1 (deja triée)
	if (_valDeque.size() <= 1)
	{
		sorted = _valDeque;
		end = clock();
		//convertion en secondes (CLOCKS_PER_SEC représente les coups d'horloge par seconde)
		_timeDeque = double((end - start) / double(CLOCKS_PER_SEC));
		return ;
	}
	//gestion des éléments impairs
	if (cpyvalDeque.size() % 2 == 1)
	{
		oddFlag = true;
		separated = cpyvalDeque.back();
		cpyvalDeque.pop_back();
	}
	//parcourir la copie en sautant de deux en deux, 
	//et chaque paire triée est stockée dans une deque pairs
	//(pairs est une deque de deque de deux entiers)
	for (size_t i = 0; i < cpyvalDeque.size(); i = i + 2)
	{
		std::deque<int> temp;
		if (cpyvalDeque[i] > cpyvalDeque[i + 1])
		{
			temp.push_back(cpyvalDeque[i]);
			temp.push_back(cpyvalDeque[i + 1]);
		}
		else
		{
			temp.push_back(cpyvalDeque[i + 1]);
			temp.push_back(cpyvalDeque[i]);
		}
		pairs.push_back(temp);
	}
	//trier pairs avec le tri fusion
	mergeDeque(pairs.begin(), pairs.end());
	//parcourir chaque deque de pairs et ajouter les premiers elements dans sorted
	//puis les seconds elements dans tosort qui sera utilisée ultérieurement pour 
	//l'insertion dans sorted
	for (size_t i = 0; i < pairs.size(); i++)
	{
		sorted.push_back(pairs[i].front());
		tosort.push_back(pairs[i].back());
	}
	//First element in tosort is lower than first element of sorted
	//so it safe to add push it to front of sorted.
	sorted.push_front(tosort.front());
	tosort.pop_front();
	bsLimit = 2;
	while (!tosort.empty())
	{
		std::deque<int>::iterator it = sorted.begin();
		std::advance(it, bsLimit);
		it = std::lower_bound(sorted.begin(), it, tosort.front());
		sorted.insert(it, tosort.front());
		tosort.pop_front();
		bsLimit += 2;
	}
	if (oddFlag)
	{
		std::deque<int>::iterator it = std::lower_bound(sorted.begin(),
				sorted.end(), separated);
		sorted.insert(it, separated);
	}
	_sortedDeque = sorted;
	end = clock();
	_timeDeque = double((end - start) / double(CLOCKS_PER_SEC));
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
