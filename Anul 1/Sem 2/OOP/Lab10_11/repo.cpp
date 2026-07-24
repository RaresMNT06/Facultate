#include "repo.h"
#include <algorithm>
#include <fstream>
#include <sstream>

/* Constructor cu persistenta - citeste mesinile din fisier la pornire
   Daca fisierul nu exista, lista ramane goala (e ok la prima rulare)
   @param numeFisier: calea fisierului ; @return: - */
Repository::Repository(const std::string& numeFisier) : numeFisier{ numeFisier } {
    incarcaDinFisier();
}

/* Citeste mesinile din fisier - format CSV: nrInm,prod,model,tip,inchiriata
   Daca fisierul nu poate fi deschis, ignora silentios (probabil prima rulare)
   @param: - ; @return: - */
void Repository::incarcaDinFisier() {
    if (numeFisier.empty()) return;

    std::ifstream in(numeFisier);
    if (!in.is_open()) return;  // Fisierul nu exista - prima rulare

    std::string linie;
    while (std::getline(in, linie)) {
        if (linie.empty()) continue;

        // Parsare linie CSV
        std::stringstream ss(linie);
        std::string nrInm, prod, model, tip, inchiriataStr;

        std::getline(ss, nrInm, ',');
        std::getline(ss, prod, ',');
        std::getline(ss, model, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, inchiriataStr, ',');

        bool inchiriata = (inchiriataStr == "1");
        masini.push_back(Masina{ nrInm, prod, model, tip, inchiriata });
    }
}

/* Salveaza toate masinile in fisier
   @param: - ; @return: - */
void Repository::salveazaInFisier() const {
    if (numeFisier.empty()) return;

    std::ofstream out(numeFisier);
    if (!out.is_open()) return;

    for (const auto& m : masini) {
        out << m.getNrInmatriculare() << ","
            << m.getProducator() << ","
            << m.getModel() << ","
            << m.getTip() << ","
            << (m.getInchiriata() ? 1 : 0) << "\n";
    }
}

/* Adauga o masina in lista
   @param masina: masina de adaugat ; @return: - */
void Repository::adauga(const Masina& masina) {
    bool exista = std::any_of(masini.cbegin(), masini.cend(),
        [&masina](const Masina& m) {
            return m.getNrInmatriculare() == masina.getNrInmatriculare();
        });

    if (exista)
        throw MasinaDuplicataException(masina.getNrInmatriculare());

    masini.push_back(masina);
    salveazaInFisier();
}

/* Sterge masina cu nrInmatriculare dat
   @param nrInmatriculare: cheia ; @return: - */
void Repository::sterge(const std::string& nrInmatriculare) {
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    masini.erase(it);
    salveazaInFisier();
}

/* Modifica producatorul, modelul si tipul masinii
   @param ... ; @return: - */
void Repository::modifica(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    it->setProducator(producator);
    it->setModel(model);
    it->setTip(tip);
    salveazaInFisier();
}

/* Modifica statusul de inchiriere
   @param ... ; @return: - */
void Repository::setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) {
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    it->setInchiriata(inchiriata);
    salveazaInFisier();
}

/* Cauta masina dupa nrInmatriculare
   @param nrInmatriculare: cheia ; @return: referinta */
const Masina& Repository::cauta(const std::string& nrInmatriculare) const {
    auto it = std::find_if(masini.begin(), masini.end(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });

    if (it == masini.end())
        throw MasinaInexistentaException(nrInmatriculare);

    return *it;
}

/* Verifica daca exista o masina
   @param nrInmatriculare: cheia ; @return: true/false */
bool Repository::exista(const std::string& nrInmatriculare) const {
    return std::any_of(masini.cbegin(), masini.cend(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });
}

/* Returneaza referinta constanta la vector
   @param: - ; @return: referinta la vector */
const std::vector<Masina>& Repository::getAll() const noexcept {
    return masini;
}

/* Aplica o functie pe fiecare masina fara copii
   @param f: functia callback ; @return: - */
void Repository::forEachMasina(const std::function<void(const Masina&)>& f) const {
    for (const auto& m : masini) {
        f(m);
    }
}

/* Returneaza numarul de masini
   @param: - ; @return: numarul de masini */
size_t Repository::size() const {
    return masini.size();
}

/* ===== Implementari pentru lista de spalare (cerinta 9) ===== */

/* Adauga o masina in lista de spalare
   @param masina: masina de adaugat ; @return: - */
void Repository::adaugaInListaSpalate(const Masina& masina) {
    spalate.push_back(masina);
}

/* Goleste lista de spalare
   @param: - ; @return: - */
void Repository::golesteListaSpalate() {
    spalate.clear();
}

/* Verifica daca o masina exista in lista de spalare
   @param nrInmatriculare: cheia ; @return: true/false */
bool Repository::existaInListaSpalate(const std::string& nrInmatriculare) const {
    return std::any_of(spalate.cbegin(), spalate.cend(),
        [&nrInmatriculare](const Masina& m) {
            return m.getNrInmatriculare() == nrInmatriculare;
        });
}

/* Returneaza referinta la lista de spalare
   @param: - ; @return: referinta la vector */
const std::vector<Masina>& Repository::getListaSpalate() const noexcept {
    return spalate;
}

/* Returneaza numarul de masini din lista de spalare
   @param: - ; @return: numarul de masini de spalat */
size_t Repository::lungimeListaSpalate() const {
    return spalate.size();
}
