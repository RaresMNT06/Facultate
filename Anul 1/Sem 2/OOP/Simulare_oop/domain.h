#pragma once
#include <string>

class Film {
	private:
		std::string cod;
		std::string titlu;
		std::string autor;
		std::string gen;

	public:
		/*constructor 
		@param: cod
		@param: titlu
		@param: autor
		@param: gen
		*/
		Film(const std::string& cod, const std::string& titlu, const std::string& autor, const std::string& gen);

		/* @return: codul filmului */
		const std::string& getCod() const;
		/* @return: titlul filmului */
		const std::string& getTitlu() const;
		/* @retunr: autorul filmului*/
		const std::string& getAutor() const;
		const std::string& getGen() const;



};
