#include "repo_dictionar.h"
#include <chrono>

/* Constructor cu probabilitate
   @param probabilitate: valoare intre 0 si 1 ; @return: - */
RepoDictionar::RepoDictionar(double probabilitate) : probabilitateEroare{ probabilitate } {
    if (probabilitate < 0.0 || probabilitate > 1.0)
        throw ValidareException("Probabilitatea trebuie sa fie intre 0 si 1!");

    // Initializam generatorul cu seed bazat pe timp
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(static_cast<unsigned>(seed));
}

/* Verifica daca trebuie sa arunce exceptie pe baza probabilitatii
   Foloseste uniform_real_distribution pentru a genera un double in [0, 1)
   Daca valoarea e mai mica decat probabilitatea, arunca exceptie
   @param: - ; @return: - (sau ValidareException) */
void RepoDictionar::verificaProbabilitate() const {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double valoare = dist(generator);
    if (valoare < probabilitateEroare)
        throw ValidareException("Operatie esuata aleator (probabilitate de eroare)!");
}

/* Adauga o masina in dictionar
   @param masina: masina de adaugat ; @return: - */
void RepoDictionar::adauga(const Masina& masina) {
    verificaProbabilitate();

    const std::string& cheie = masina.getNrInmatriculare();
    // contains() e disponibil din C++20
    if (masini.contains(cheie))
        throw MasinaDuplicataException(cheie);

    // Folosim insert in loc de operator[] (care ar avea nevoie de default constructor pe Masina)
    masini.insert({ cheie, masina });
}

/* Sterge masina dupa cheie
   @param nrInmatriculare: cheia ; @return: - */
void RepoDictionar::sterge(const std::string& nrInmatriculare) {
    verificaProbabilitate();

    auto it = masini.find(nrInmatriculare);
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    masini.erase(it);
}

/* Modifica datele unei masini
   @param nrInmatriculare: cheia ; @param producator: nou producator
   @param model: nou model ; @param tip: nou tip ; @return: - */
void RepoDictionar::modifica(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    verificaProbabilitate();

    auto it = masini.find(nrInmatriculare);
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    it->second.setProducator(producator);
    it->second.setModel(model);
    it->second.setTip(tip);
}

/* Modifica statusul de inchiriere
   @param nrInmatriculare: cheia ; @param inchiriata: nou status ; @return: - */
void RepoDictionar::setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) {
    verificaProbabilitate();

    auto it = masini.find(nrInmatriculare);
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    it->second.setInchiriata(inchiriata);
}

/* Cauta masina dupa cheie
   @param nrInmatriculare: cheia ; @return: referinta la masina */
const Masina& RepoDictionar::cauta(const std::string& nrInmatriculare) const {
    verificaProbabilitate();

    auto it = masini.find(nrInmatriculare);
    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    return it->second;
}

/* Verifica existenta dupa cheie
   @param nrInmatriculare: cheia ; @return: true/false */
bool RepoDictionar::exista(const std::string& nrInmatriculare) const {
    verificaProbabilitate();
    return masini.contains(nrInmatriculare);
}

/* Returneaza toate masinile - construieste vector din valorile dictionarului
   Range-based for peste pair-urile din map
   @param: - ; @return: vector cu toate masinile */
std::vector<Masina> RepoDictionar::getAll() const {
    verificaProbabilitate();

    std::vector<Masina> rezultat;
    rezultat.reserve(masini.size());
    for (const auto& [cheie, masina] : masini) {
        rezultat.push_back(masina);
    }
    return rezultat;
}

/* Aplica o functie pe fiecare masina fara copii
   @param f: functia callback ; @return: - */
void RepoDictionar::forEachMasina(const std::function<void(const Masina&)>& f) const {
    verificaProbabilitate();
    for (const auto& [cheie, masina] : masini) {
        f(masina);
    }
}

/* Returneaza numarul de masini
   @param: - ; @return: numarul de masini */
size_t RepoDictionar::size() const {
    verificaProbabilitate();
    return masini.size();
}

/* ===== Implementari pentru lista de spalare (cerinta 9) ===== */

/* Adauga o masina in lista de spalare (in dictionarul spalate)
   Foloseste insert_or_assign in caz ca exista deja (suprascrie)
   @param masina: masina de adaugat ; @return: - */
void RepoDictionar::adaugaInListaSpalate(const Masina& masina) {
    verificaProbabilitate();
    spalate.insert_or_assign(masina.getNrInmatriculare(), masina);
}

/* Goleste complet lista de spalare
   Apelat la generare lista (resetare) si la cerere user
   @param: - ; @return: - */
void RepoDictionar::golesteListaSpalate() {
    verificaProbabilitate();
    spalate.clear();
}

/* Verifica daca o masina cu nrInmatriculare exista in lista de spalare
   Foloseste contains() din C++20 pe map
   @param nrInmatriculare: cheia cautata
   @return: true daca exista, false altfel */
bool RepoDictionar::existaInListaSpalate(const std::string& nrInmatriculare) const {
    verificaProbabilitate();
    return spalate.contains(nrInmatriculare);
}

/* Returneaza lista de spalare ca vector (copie)
   Construieste un vector din valorile dictionarului
   @param: - ; @return: vector cu toate masinile de spalat */
std::vector<Masina> RepoDictionar::getListaSpalate() const {
    verificaProbabilitate();

    std::vector<Masina> rezultat;
    rezultat.reserve(spalate.size());
    // Range-based for cu structured binding C++17 - iteram pair-urile
    for (const auto& [cheie, masina] : spalate) {
        rezultat.push_back(masina);
    }
    return rezultat;
}

/* Returneaza numarul de masini din lista de spalare
   @param: - ; @return: numarul de masini de spalat */
size_t RepoDictionar::lungimeListaSpalate() const {
    verificaProbabilitate();
    return spalate.size();
}
