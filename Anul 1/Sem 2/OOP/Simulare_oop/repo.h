#pragma once
#include "domain.h"
#include <string>
#include <vector>

class Repository {
	private:
		/* Vectorul de filme */
		std::vector<Film> filme;
		/* Numele fisierului */
		std::string filename;
	
		/*Incarca filmele din fisier*/
		void loadFromFile();
	
	public:

		/*Constructor citeste filmele din fisier*/
		Repository(const std::string& filename);

		/*@return : returneaza toate filmele*/
		const std::vector<Film>& getAll() const;

		/*@return : returneaza numarul de filme*/
		size_t size() const;



};