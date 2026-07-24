#include "repo.h"
#include <algorithm>

/* Adauga o masina in lista dupa ce verifica sa nu existe deja
   Arunca MasinaDuplicataException daca nrInmatriculare exista deja
   @param masina: masina de adaugat ; @return: - */
void Repository::adauga(const Masina& masina) {
    // Verificam daca exista deja o masina cu acelasi nrInmatriculare
    if (exista(masina.getNrInmatriculare()))
        throw MasinaDuplicataException(masina.getNrInmatriculare());
    masini.push_back(masina);
}

/* Cauta si sterge masina cu nrInmatriculare dat folosind std::find_if
   Arunca MasinaInexistentaException daca masina nu exista
   @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
void Repository::sterge(const std::string& nrInmatriculare) {
    // Cautam iteratorul catre masina cu nrInmatriculare dat
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    // Daca nu s-a gasit, aruncam exceptie
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    // Stergem elementul direct prin iterator, fara calcul de index
    masini.erase(it);
}

/* Modifica producatorul, modelul si tipul masinii identificate prin nrInmatriculare
   Foloseste std::find_if pentru a gasi masina, apoi o modifica prin iterator
   Arunca MasinaInexistentaException daca masina nu exista
   @param nrInmatriculare: cheia de identificare
   @param producator: noul producator
   @param model: noul model
   @param tip: noul tip
   @return: - */
void Repository::modifica(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    // Cautam iteratorul catre masina care trebuie modificata
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    // Daca nu s-a gasit, aruncam exceptie
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    // Modificam masina prin iterator
    it->setProducator(producator);
    it->setModel(model);
    it->setTip(tip);
}

/* Modifica statusul de inchiriere al masinii identificate prin nrInmatriculare
   Foloseste std::find_if pentru a gasi masina, apoi seteaza statusul prin iterator
   Arunca MasinaInexistentaException daca masina nu exista
   @param nrInmatriculare: cheia de identificare
   @param inchiriata: noul status de inchiriere
   @return: - */
void Repository::setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) {
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    it->setInchiriata(inchiriata);
}

/* Cauta masina dupa nrInmatriculare si returneaza referinta la ea
   Foloseste std::find_if pe iteratorii constanti (cbegin/cend)
   Arunca MasinaInexistentaException daca masina nu exista
   @param nrInmatriculare: cheia cautata
   @return: referinta constanta la masina gasita */
const Masina& Repository::cauta(const std::string& nrInmatriculare) const {
    // Cautam iteratorul constant catre masina
    auto it = std::find_if(masini.cbegin(), masini.cend(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    // Daca nu s-a gasit, aruncam exceptie
    if (it == masini.cend())
        throw MasinaInexistentaException(nrInmatriculare);

    return *it;
}

/* Verifica daca exista o masina cu nrInmatriculare dat folosind std::any_of
   Nu arunca exceptii - returneaza doar true/false
   @param nrInmatriculare: cheia cautata
   @return: true daca exista, false altfel */
bool Repository::exista(const std::string& nrInmatriculare) const noexcept {
    // any_of returneaza true daca cel putin un element satisface predicatul
    return std::any_of(masini.cbegin(), masini.cend(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });
}

/* Returneaza intreaga lista de masini fara copiere
   @param: -
   @return: referinta constanta la vectorul de masini */
const std::vector<Masina>& Repository::getAll() const noexcept {
    return masini;
}

/* Returneaza numarul de masini din lista
   @param: -
   @return: numarul de masini */
size_t Repository::size() const noexcept {
    return masini.size();
}

/* ===== Implementari pentru lista de spalare (cerinta 9) ===== */

/* Adauga o masina in lista de spalare
   Nu verifica duplicate - apelantul (Service) trebuie sa o faca
   @param masina: masina de adaugat in lista de spalare ; @return: - */
void Repository::adaugaInListaSpalate(const Masina& masina) {
    spalate.push_back(masina);
}

/* Goleste lista de spalare - elimina toate masinile
   @param: - ; @return: - */
void Repository::golesteListaSpalate() noexcept {
    spalate.clear();
}

/* Verifica daca o masina cu nrInmatriculare dat exista in lista de spalare
   Foloseste std::any_of pe lista de spalare
   @param nrInmatriculare: cheia cautata
   @return: true daca exista in lista de spalare, false altfel */
bool Repository::existaInListaSpalate(const std::string& nrInmatriculare) const noexcept {
    return std::any_of(spalate.cbegin(), spalate.cend(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });
}

/* Returneaza intreaga lista de spalare fara copiere
   @param: -
   @return: referinta constanta la vectorul cu masinile de spalat */
const std::vector<Masina>& Repository::getListaSpalate() const noexcept {
    return spalate;
}

/* Returneaza numarul de masini din lista de spalare
   @param: -
   @return: numarul de masini din lista de spalare */
size_t Repository::lungimeListaSpalate() const noexcept {
    return spalate.size();
}