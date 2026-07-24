#pragma once
#include "repo.h"
#include <vector>
#include <string>

class Service {
	private:
		Repository& repo;
		
	public:
		/* Constructor
			@param repo: referinta la repository
			@return: - */

		Service(Repository& repo);

		/*Returneaza toate filmele
			@return: referinta fata de vecor*/

		const std::vector<Film>& getAll() const;

		/* Filtreaza filmele dupa gen
			@param gen: genul cautat
			@return: vector cu filmele filtrate */
		std::vector<Film> filtreazaDupaGen(const std::string& gen) const;

		/* Sorteaza filmele dupa titlu
		   @param: -
		   @return: vector sortat dupa titlu */
		std::vector<Film> sorteazaDupaTitlu() const;
		




};