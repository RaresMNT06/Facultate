#include "domain.h"

Film::Film(const std::string& cod, const std::string& titlu, const std::string& autor, const std::string& gen)
	: cod(cod), titlu(titlu), autor(autor), gen(gen) {

}
/* @return: codul filmului */
const std::string& Film::getCod() const {
	return cod;
}
/* @return: titlul filmului */
const std::string& Film::getTitlu() const {
	return titlu;
}
/* @return: autorul filmului */
const std::string& Film::getAutor() const {
	return autor;
}

/* @return: genul filmului */
const std::string& Film::getGen() const {
	return gen;
}

