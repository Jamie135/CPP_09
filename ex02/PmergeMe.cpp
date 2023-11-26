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
	int				insertIndex;
	clock_t			start;
	clock_t			end;

	oddFlag = false;
	std::deque<int> cpyvalDeque;
	std::deque<std::deque<int> > pairs;
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

	// std::cout << "1) cpyvalDeque and separated: " << std::endl;
	// std::cout << "cpyvalDeque: ";
	// for (size_t i = 0; i < cpyvalDeque.size(); i++)
	// 	std::cout << cpyvalDeque[i] << " ";
	// std::cout << std::endl;
	// std::cout << "separated: " << separated << std::endl << std::endl;

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

	// std::cout << "2) pairs: " << std::endl;
	// for (size_t i = 0; i < pairs.size(); i++)
	// {
	// 	std::cout << "pairs[" << i << "]: ";
	// 	for (size_t j = 0; j < pairs[i].size(); j++)
	// 		std::cout << pairs[i][j] << " ";
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;

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

	// std::cout << "3) sorted/tosort before: " << std::endl;
	// std::cout << "sorted: ";
	// for (size_t i = 0; i < sorted.size(); i++)
	// 	std::cout << sorted[i] << " ";
	// std::cout << std::endl;
	// std::cout << "tosort: ";
	// for (size_t i = 0; i < tosort.size(); i++)
	// 	std::cout << tosort[i] << " ";
	// std::cout << std::endl << std::endl;

	//transferer le premier élément de tosort à l'avant de sorted
	//et retirer cet élément de tosort
	sorted.push_front(tosort.front());
	tosort.pop_front();

	// std::cout << "4) sorted/tosort after: " << std::endl;
	// std::cout << "sorted: ";
	// for (size_t i = 0; i < sorted.size(); i++)
	// 	std::cout << sorted[i] << " ";
	// std::cout << std::endl;
	// std::cout << "tosort: ";
	// for (size_t i = 0; i < tosort.size(); i++)
	// 	std::cout << tosort[i] << " ";
	// std::cout << std::endl << std::endl;

	insertIndex = 2;
	//boucle d'insertion de manière séquentielle (insertIndex + 2)
	//les éléments de tosort dans la sorted
	while (!tosort.empty())
	{
		std::deque<int>::iterator it = sorted.begin();

		//l'itérateur it est incrémenté de insertIndex dans sorted
		//c'est une façon d'espacer l'insertion des éléments de tosort
		std::advance(it, insertIndex);

		//trouver la première position dans sorted 
		//où l'élément de tosort.front() peut être inséré
		it = std::lower_bound(sorted.begin(), it, tosort.front());
		sorted.insert(it, tosort.front());

		tosort.pop_front();
		insertIndex += 2;
	}

	// std::cout << "5) inserted sorted: " << std::endl;
	// std::cout << "sorted: ";
	// for (size_t i = 0; i < sorted.size(); i++)
	// 	std::cout << sorted[i] << " ";
	// std::cout << std::endl << std::endl;

	//gestion de l'élément supplémentaire (separated)
	if (oddFlag)
	{
		std::deque<int>::iterator it = std::lower_bound(sorted.begin(),
				sorted.end(), separated);
		sorted.insert(it, separated);
	}

	// std::cout << "6) sorted with separated: " << std::endl;
	// std::cout << "sorted: ";
	// for (size_t i = 0; i < sorted.size(); i++)
	// 	std::cout << sorted[i] << " ";
	// std::cout << std::endl << std::endl;

	_sortedDeque = sorted;
	end = clock();
	_timeDeque = double((end - start) / double(CLOCKS_PER_SEC));
}

void PmergeMe::merge_insertion_List()
{
	bool									oddFlag = false;
	int										separated;
	int										insertIndex;

	clock_t									start;
	clock_t									end;

	std::list<int>::iterator				it;
	std::list<int>							cpyvalList;
	std::list<std::list<int> >				pairs;
	std::list<int>							sorted;
	std::list<int>							tosort;
	std::list<std::list<int> >::iterator	itPair;

	cpyvalList = _valList;
	start = clock();

	//liste de taille 1
	if (_valList.size() <= 1)
	{
		sorted = _valList;
		std::time(&end);
		_timeList = double((end - start) / double(CLOCKS_PER_SEC));
		return ;
	}

	//separer une liste impaire
	if (cpyvalList.size() % 2 == 1)
	{
		oddFlag = true;
		separated = cpyvalList.back();
		cpyvalList.pop_back();
	}

	// std::cout << "1) cpyvalList and separated: " << std::endl;
	// std::cout << "cpyvalList: ";
	// std::list<int>::iterator it_cpy;
	// for (it_cpy = cpyvalList.begin(); it_cpy != cpyvalList.end(); ++it_cpy) {
	// 	std::cout << *it_cpy << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "separated: " << separated << std::endl << std::endl;

	//creation des pairs
	it = cpyvalList.begin();
	while (it != cpyvalList.end())
	{
		std::list<int>				temp;
		std::list<int>::iterator	next = ++it;
		--it;
		if (*it > *(next))
		{
			temp.push_back(*it);
			temp.push_back(*(next));
		}
		else
		{
			temp.push_back(*(next));
			temp.push_back(*it);
		}
		pairs.push_back(temp);
		std::advance(it, 2);
	}

	// std::cout << "2) pairs: " << std::endl;
	// int j = 0;
	// for (std::list<std::list<int> >::const_iterator outerIt = pairs.begin(); outerIt != pairs.end(); ++outerIt) {
    //     std::cout << "pairs[" << j << "]: ";
	// 	for (std::list<int>::const_iterator innerIt = outerIt->begin(); innerIt != outerIt->end(); ++innerIt) {
    //         std::cout << *innerIt << " ";
    //     }
	// 	j++;
    //     std::cout << std::endl;
    // }
	// std::cout << std::endl;

	//tri de pairs avec mergesort
	mergeList(pairs.begin(), pairs.end());
	itPair = pairs.begin();
	while (itPair != pairs.end())
	{
		sorted.push_back(itPair->front());
		tosort.push_back(itPair->back());
		++itPair;
	}

	// std::cout << "3) sorted/tosort before: " << std::endl;
	// std::cout << "sorted: ";
	// std::list<int>::iterator it_sorted;
	// for (it_sorted = sorted.begin(); it_sorted != sorted.end(); ++it_sorted) {
	// 	std::cout << *it_sorted << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "tosort: ";
	// std::list<int>::iterator it_tosort;
	// for (it_tosort = tosort.begin(); it_tosort != tosort.end(); ++it_tosort) {
	// 	std::cout << *it_tosort << " ";
	// }
	// std::cout << std::endl << std::endl;

	//le premier element dans tosort est <= au premier element de sorted
	//c'est donc safe de le push_front dans sorted.
	sorted.push_front(tosort.front());
	tosort.pop_front();

	// std::cout << "4) sorted/tosort after: " << std::endl;
	// std::cout << "sorted: ";
	// std::list<int>::iterator it_sorted1;
	// for (it_sorted1 = sorted.begin(); it_sorted1 != sorted.end(); ++it_sorted1) {
	// 	std::cout << *it_sorted1 << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "tosort: ";
	// std::list<int>::iterator it_tosort1;
	// for (it_tosort1 = tosort.begin(); it_tosort1 != tosort.end(); ++it_tosort1) {
	// 	std::cout << *it_tosort1 << " ";
	// }
	// std::cout << std::endl << std::endl;

	insertIndex = 2;
	while (!tosort.empty())
	{
		it = sorted.begin();
		std::advance(it, insertIndex);
		it = lower_bound(sorted.begin(), it, tosort.front());
		sorted.insert(it, tosort.front());
		tosort.pop_front();
		insertIndex += 2;
	}

	// std::cout << "5) inserted sorted: " << std::endl;
	// std::cout << "sorted: ";
	// std::list<int>::iterator it_sorted2;
	// for (it_sorted2 = sorted.begin(); it_sorted2 != sorted.end(); ++it_sorted2) {
	// 	std::cout << *it_sorted2 << " ";
	// }
	// std::cout << std::endl << std::endl;

	if (oddFlag)
	{
		it = lower_bound(sorted.begin(), sorted.end(), separated);
		sorted.insert(it, separated);
	}

	// std::cout << "6) sorted with separated: " << std::endl;
	// std::cout << "sorted: ";
	// std::list<int>::iterator it_sorted3;
	// for (it_sorted3 = sorted.begin(); it_sorted3 != sorted.end(); ++it_sorted3) {
	// 	std::cout << *it_sorted3 << " ";
	// }
	// std::cout << std::endl << std::endl;

	_sortedList = sorted;
	end = clock();
	_timeList = double((end - start) / double(CLOCKS_PER_SEC));
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
