#include "service.h"
#include <algorithm>

/* constructor
   @param repo: referinta la repository */
Service::Service(Repository& repo) : repo(repo) {
}

/* @return: toate filmele */
const std::vector<Film>& Service::getAll() const {
	return repo.getAll();
}


/* @param gen: genul cautat
   @return: filmele filtrate dupa gen */
std::vector<Film> Service::filtreazaDupaGen(const std::string& gen) const {
	std::vector<Film> result;
	for(const auto& f : getAll())
		if(f.getGen() == gen)
			result.push_back(f);
	return result;
}

/* @return: filmele sortate dupa titlu */
std::vector<Film> Service::sorteazaDupaTitlu() const {
	std::vector<Film> result = repo.getAll();
	std::sort(result.begin(), result.end(),
		[](const Film& a, const Film& b) {
			return a.getTitlu() < b.getTitlu();
		});
	return result;
}

