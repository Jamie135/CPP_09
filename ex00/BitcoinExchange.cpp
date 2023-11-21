#include "BitcoinExchange.hpp"

//initialise les données de la classe en lisant le fichier "data.csv"
BitcoinExchange::BitcoinExchange()
{
	int	i;

	std::ifstream				file; //declaration du fichier
	std::string					line; //stocker chaque ligne lue
	std::string					word; //stocker chaque mots separer par ','
	std::vector<std::string>	row; //vecteur de str utiliser pour stocker les mots de chaque ligne

	file.open("data.csv");
	_data.clear(); //effacee le contenu de la variable _data
	if (file.is_open())
	{
		i = 0;
		while (file)
		{
			row.clear(); //effacer le contenu du vecteur row pour stocker les mots de la nouvelle ligne
			std::getline(file, line); //lit une ligne du fichier et la stocke dans line
			std::stringstream s(line); //string qui va etre servi pour l'extraction des mots
			while (std::getline(s, word, ','))
			{
				row.push_back(word); //ajoute chaque mot au vecteur row
			}
			//convertir la première colonne (date et heure) en un format approprié, et la deuxième colonne (prix) en un nombre à virgule flottante.
			if (i != 0)
				_data[setDate(row[0])] = std::atof(row[1].c_str());
			i++;
		}
		file.close();
	}
	else
		throw std::runtime_error("Error: could not open database.");
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

//convertir un string sous format YYYY-MM-DD en un int sous format DDMMYYYY 
int	BitcoinExchange::setDate(std::string &strDate)
{
	int					date = 0;
	std::vector<int>	time; //vecteur d'entiers utilisé pour stocker toutes les composantes de la date extraites
	std::string			word; //string  utilisée pour stocker chaque composante
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
				row.push_back(stripSpaces(word));
			if (i != 0)
				handleLine(row);
			i++;
		}
		file.close();
	}
	else
		throw std::runtime_error("Error: could not open file.");
}