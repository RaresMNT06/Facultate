#include "repo.h"
#include <fstream>
#include <sstream>


/*constructor*/
Repository::Repository(const std::string& filename) : filename(filename) {
	loadFromFile();
}


/*Citire din fisier*/
void Repository::loadFromFile() {
	std::ifstream f(filename);
	std::string line;
	while (std::getline(f, line)) {
		std::stringstream ss(line);
		std::string cod, titlu, autor, gen;
		std::getline(ss, cod, ',');
		std::getline(ss, titlu, ',');
		std::getline(ss, autor, ',');
		std::getline(ss, gen, ',');
		filme.push_back(Film(cod, titlu, autor, gen));
	}
}

/*@return : returneaza toate filmele*/
const std::vector<Film>& Repository::getAll() const {
	return filme;
}
/*@return : returneaza numarul de filme*/

size_t Repository::size() const {
	return filme.size();
}