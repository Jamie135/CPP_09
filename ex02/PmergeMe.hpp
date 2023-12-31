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
	public:
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &src);

		//Getters
		const std::deque<int>		&getValDeque() const;
		const std::list<int>		&getValList() const;
		const std::deque<int>		&getSortedDeque() const;
		const std::list<int>		&getSortedList() const;
		double						getTimeDeque() const;
		double						getTimeList() const;

		//Methods
		void	merge_insertion_Deque();
		void	merge_insertion_List();
		static bool cmpDeque(const std::deque<int>& a, const std::deque<int>& b);
		static bool cmpList(const std::list<int>& a, const std::list<int>& b);

		//Function Templates
		template <class Iterator>
		void mergeDeque(Iterator begin, Iterator end) {
			//vérifier si la séquence délimitée par les itérateurs est <= 1 
			//si c'est le cas, la séquence est déjà triée
			if (end <= begin + 1) return;
			//calcul du point median
			Iterator middle = begin + (end - begin) / 2;
			//appel recursive pour trier les deux moitiés
			mergeDeque(begin, middle);
			mergeDeque(middle, end);
			std::inplace_merge(begin, middle, end, cmpDeque);
		}

		template <class Iterator>
		void mergeList(Iterator begin, Iterator end) {
			if (std::distance(begin, end) <= 1) return;

			Iterator middle = begin;
			std::advance(middle, std::distance(begin, end) / 2);

			mergeList(begin, middle);
			mergeList(middle, end);

			std::list<typename Iterator::value_type> temp;
			std::merge(begin, middle, middle, end, std::back_inserter(temp), cmpList);

			std::copy(temp.begin(), temp.end(), begin);
		}

		//trouver la première position dans la liste où l'élément peut être inséré de manière ordonnée
		template <typename T>
		typename std::list<T>::iterator lower_bound(typename std::list<T>::iterator first, typename std::list<T>::iterator last, const T& value) {
			while (first != last) {
				typename std::list<T>::iterator mid = first;
				std::advance(mid, std::distance(first, last) / 2);

				if (*mid < value) {
					++mid;
					first = mid;
				} else {
					last = mid;
				}
			}
			return first;
		}
	
	private:
		std::deque<int>		_valDeque;
		std::list<int>		_valList;
		std::deque<int>		_sortedDeque;
		std::list<int>		_sortedList;
		double				_timeDeque;
		double				_timeList;
};
