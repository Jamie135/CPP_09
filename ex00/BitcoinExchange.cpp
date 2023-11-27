#include "BitcoinExchange.hpp"

//initialise les données de la classe en lisant le fichier "data.csv"
BitcoinExchange::BitcoinExchange()
{
	int	i;

	std::ifstream				file; //declaration du fichier
	std::string					line; //stocker chaque ligne lue
	std::string					word; //stocker chaque string separer par ','
	std::vector<std::string>	col; //vecteur de str utiliser pour stocker les string de chaque ligne, chaque string representera une colonne

	file.open("data.csv");
	_data.clear(); //effacee le contenu de la variable _data
	if (file.is_open())
	{
		i = 0;
		while (file)
		{
			col.clear(); //effacer le contenu du vecteur col pour stocker les string de la nouvelle ligne
			std::getline(file, line); //lit une ligne du fichier et la stocke dans line
			std::stringstream s(line); //string qui va etre servi pour l'extraction des strings de line
			while (std::getline(s, word, ','))
			{
				col.push_back(word); //ajoute chaque mot au vecteur col
			}
			//convertir la première colonne (date et heure) en un format approprié, et la deuxième colonne (prix) en un nombre à virgule flottante.
			if (i != 0)
				_data[setDate(col[0])] = std::atof(col[1].c_str());
			i++;
		}
		file.close();
	}
	else
		throw std::runtime_error("Error: could not open data file.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
		_data = src._data;
	return (*this);
}

//convertir un string sous format YYYY-MM-DD en un int sous format YYYY00MMDD 
int	BitcoinExchange::setDate(std::string &strDate)
{
	int					date = 0;
	std::vector<int>	time; //vecteur d'entiers utilisé pour stocker toutes les composantes de la date extraites
	std::string			word; //string utilisée pour stocker chaque composante
	std::stringstream	s(strDate); //string qui va etre servi pour l'extraction
	while (getline(s, word, '-')) //extraire chaque composante de la date séparée par '-' et les ajoute au vecteur time
		time.push_back(std::atoi(word.c_str()));
	if (time.size() != 3)
		return (0);
	if (time[0] < 2000 || time[0] > 10000)
		return (0);
	if (time[1] > 12)
		return (0);
	if (time[2] > 31)
		return (0);
	//verification des mois avec moins de 31 jours, en tenant compte des années bissextiles
	if (time[2] == 31 && (time[1] == 4 or time[1] == 6 or time[1] == 9 or time[1] == 11))
		return (0); 
	if (time[1] == 2)
	{
		if (time[2] > 29)
			return (0);
		if (time[2] == 29 && ((time[0] % 100) % 4 != 0))
			return (0);
	}
	date += time[2];
	date += 100 * time[1];
	date += 1000000 * time[0];
	// std::cout << "date: " << date << std::endl;
	return (date);
}

void BitcoinExchange::readFile(const std::string &path)
{
	int	i;

	std::ifstream				file;
	std::string					line;
	std::string					word;
	std::vector<std::string>	row;

	file.open(path.c_str());
	if (file.is_open())
	{
		i = 0;
		while (file)
		{
			row.clear();
			std::getline(file, line);
			std::stringstream s(line);
			while (getline(s, word, '|'))
				row.push_back(trimSpace(word));
			if (i != 0)
				processLine(row);
			i++;
		}
		file.close();
	}
	else
		throw std::runtime_error("Error: could not open file.");
}

//enlever les espaces
std::string	BitcoinExchange::trimSpace(std::string &str)
{
	str = trimFront(str);
	for (size_t i = 0; i < str.size() / 2; i++)
	{
		char c = str[i];
		str[i] = str[str.size() - i - 1];
		str[str.size() - i - 1] = c;
	}
	str = trimFront(str);
	for (size_t i = 0; i < str.size() / 2; i++)
	{
		char c = str[i];
		str[i] = str[str.size() - i - 1];
		str[str.size() - i - 1] = c;
	}
	return (str);
}

////enlever les espaces au debut
std::string	BitcoinExchange::trimFront(std::string &s)
{
	std::string res = "";
	bool		flag = false;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
			flag = true;
		if (flag)
			res += s[i];
	}
	return (res);
}

void	BitcoinExchange::processLine(std::vector<std::string> &vectLine)
{
	float									bitcoin; //valeur numérique extraite
	int										date; //date extraite
	std::map<int, float>::iterator			it; //itérateur pour _data où la clé est de type entier et la valeur est de type flottant

	if (vectLine.size() != 0)
	{
		if (setDate(vectLine[0])) //convertir la date de l'input
		{
			if (vectLine.size() != 2)
				std::cerr << "Error: bad row => " << vectLine[0] << std::endl;
			else
			{
				bitcoin = std::atof(vectLine[1].c_str()); //convertir le nombre de bitcoin en flottant
				if (bitcoin < 0)
					std::cerr << "Error: not a positive number." << std::endl;
				else if (bitcoin > 1000)
					std::cerr << "Error: too large a number." << std::endl;
				else
				{
					date = setDate(vectLine[0]);
					it = _data.lower_bound(date);
					if (it->first == date)
						std::cout << vectLine[0] << " => " << bitcoin << " = " << (it->second * bitcoin) << std::endl;
					else
					{
						if (_data.begin() != it)
							--it;
						if (_data.begin() == it
							&& date != (it->first))
							std::cerr << "Error: bitcoin doesn't exist here." << std::endl;
						else
							std::cout << vectLine[0] << " => " << bitcoin << " = " << (it->second * bitcoin) << std::endl;
					}
				}
			}
		}
		else
			std::cerr << "Error: bad input => " << vectLine[0] << std::endl;
	}
}
