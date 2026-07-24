#include "repo.h"
#include <stdexcept>

/* Adauga o masina in lista dupa ce verifica sa nu existe deja
   @param masina: masina de adaugat ; @return: - */
void Repository::adauga(const Masina& masina) {
    if (exista(masina.getNrInmatriculare()))
        throw std::runtime_error("Masina cu acest numar de inmatriculare exista deja!");
    masini.add(masina);
}

/* Cauta si sterge masina cu nrInmatriculare dat
   @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
void Repository::sterge(const std::string& nrInmatriculare) {
    for (size_t i = 0; i < masini.size(); i++) {
        if (masini.at(i).getNrInmatriculare() == nrInmatriculare) {
            masini.remove(i);
            return;
        }
    }
    throw std::runtime_error("Masina nu a fost gasita!");
}

/* Modifica producatorul, modelul si tipul masinii identificate prin nrInmatriculare
   @param nrInmatriculare: cheia de identificare
   @param producator, model, tip: noile valori ; @return: - */
void Repository::modifica(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    for (size_t i = 0; i < masini.size(); i++) {
        if (masini.at(i).getNrInmatriculare() == nrInmatriculare) {
            masini.at(i).setProducator(producator);
            masini.at(i).setModel(model);
            masini.at(i).setTip(tip);
            return;
        }
    }
    throw std::runtime_error("Masina nu a fost gasita!");
}

/* Cauta masina dupa nrInmatriculare si returneaza referinta la ea
   @param nrInmatriculare: cheia cautata ; @return: referinta constanta la masina gasita */
const Masina& Repository::cauta(const std::string& nrInmatriculare) const {
    for (size_t i = 0; i < masini.size(); i++)
        if (masini.at(i).getNrInmatriculare() == nrInmatriculare)
            return masini.at(i);
    throw std::runtime_error("Masina nu a fost gasita!");
}

/* Verifica daca exista o masina cu nrInmatriculare dat
   @param nrInmatriculare: cheia cautata ; @return: true daca exista, false altfel */
bool Repository::exista(const std::string& nrInmatriculare) const noexcept {
    for (size_t i = 0; i < masini.size(); i++)
        if (masini.at(i).getNrInmatriculare() == nrInmatriculare)
            return true;
    return false;
}

/* Returneaza intreaga lista de masini fara copiere
   @param: - ; @return: referinta constanta la lista de masini */
const MyList<Masina>& Repository::getAll() const noexcept {
    return masini;
}

/* Returneaza numarul de masini din lista
   @param: - ; @return: numarul de masini */
size_t Repository::size() const noexcept {
    return masini.size();
}