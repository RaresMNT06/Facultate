#include "service.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

bool Service::esteLitera(char c) const noexcept {
    return (c >= 'A' && c <= 'Z');
}

bool Service::esteCifra(char c) const noexcept {
    return c >= '0' && c <= '9';
}

bool Service::esteNrInmatriculareValid(const std::string& nr) const {
    const auto len = nr.size();

    if (len == 9 && nr.at(1) != ' ') {
        if (!esteLitera(nr.at(0)) || !esteLitera(nr.at(1))) return false;
        if (nr.at(2) != ' ') return false;
        if (!esteCifra(nr.at(3)) || !esteCifra(nr.at(4))) return false;
        if (nr.at(5) != ' ') return false;
        if (!esteLitera(nr.at(6)) || !esteLitera(nr.at(7)) || !esteLitera(nr.at(8))) return false;
        return true;
    }

    if ((len == 8 || len == 9) && nr.at(0) == 'B' && nr.at(1) == ' ') {
        if (len == 9) {
            if (!esteCifra(nr.at(2)) || !esteCifra(nr.at(3)) || !esteCifra(nr.at(4))) return false;
            if (nr.at(5) != ' ') return false;
            if (!esteLitera(nr.at(6)) || !esteLitera(nr.at(7)) || !esteLitera(nr.at(8))) return false;
        }
        else {
            if (!esteCifra(nr.at(2)) || !esteCifra(nr.at(3))) return false;
            if (nr.at(4) != ' ') return false;
            if (!esteLitera(nr.at(5)) || !esteLitera(nr.at(6)) || !esteLitera(nr.at(7))) return false;
        }
        return true;
    }

    return false;
}

/* Initializeaza service-ul cu o referinta la repository
   @param repo: referinta la repository ; @return: - */
Service::Service(Repository& repo) noexcept : repo{ repo } {}

/* Valideaza si adauga o masina in repository
   Arunca exceptie daca un camp e gol, format invalid sau masina exista deja
   @param nrInmatriculare: cheia unica ; @param producator: producatorul
   @param model: modelul ; @param tip: tipul masinii ; @return: - */
void Service::adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw std::invalid_argument("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw std::invalid_argument("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    Masina m{ nrInmatriculare, producator, model, tip };
    repo.adauga(m);
}

/* Valideaza si sterge masina cu nrInmatriculare dat
   Arunca exceptie daca campul e gol sau masina nu exista
   @param nrInmatriculare: cheia de identificare ; @return: - */
void Service::stergeMasina(const std::string& nrInmatriculare) {
    if (nrInmatriculare.empty())
        throw std::invalid_argument("Numarul de inmatriculare nu poate fi gol!");
    repo.sterge(nrInmatriculare);
}

/* Valideaza si modifica masina identificata prin nrInmatriculare
   Arunca exceptie daca un camp e gol, format invalid sau masina nu exista
   @param nrInmatriculare: cheia de identificare
   @param producator, model, tip: noile valori ; @return: - */
void Service::modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
    const std::string& model, const std::string& tip) {
    if (nrInmatriculare.empty() || producator.empty() || model.empty() || tip.empty())
        throw std::invalid_argument("Toate campurile sunt obligatorii!");
    if (!esteNrInmatriculareValid(nrInmatriculare))
        throw std::invalid_argument("Format invalid! Exemple: 'CJ 01 ABC' sau 'B 67 MNT'");
    repo.modifica(nrInmatriculare, producator, model, tip);
}

/* Cauta masina dupa nrInmatriculare
   Arunca exceptie daca campul e gol sau masina nu exista
   @param nrInmatriculare: cheia cautata ; @return: referinta constanta la masina gasita */
const Masina& Service::cautaMasina(const std::string& nrInmatriculare) const {
    if (nrInmatriculare.empty())
        throw std::invalid_argument("Numarul de inmatriculare nu poate fi gol!");
    return repo.cauta(nrInmatriculare);
}

/* Returneaza toata lista de masini fara copiere
   @param: - ; @return: referinta constanta la lista de masini */
const MyList<Masina>& Service::getToateMasinile() const noexcept {
    return repo.getAll();
}

/* Returneaza un vector nou cu masinile care au producatorul dat
   @param producator: producatorul cautat ; @return: vector cu masinile filtrate */
std::vector<Masina> Service::filtreazaDupaProducator(const std::string& producator) const {
    std::vector<Masina> rezultat;
    for (size_t i = 0; i < repo.getAll().size(); i++)
        if (repo.getAll().at(i).getProducator() == producator)
            rezultat.push_back(repo.getAll().at(i));
    return rezultat;
}

/* Returneaza un vector nou cu masinile care au tipul dat
   @param tip: tipul cautat ; @return: vector cu masinile filtrate */
std::vector<Masina> Service::filtreazaDupaTip(const std::string& tip) const {
    std::vector<Masina> rezultat;
    for (size_t i = 0; i < repo.getAll().size(); i++)
        if (repo.getAll().at(i).getTip() == tip)
            rezultat.push_back(repo.getAll().at(i));
    return rezultat;
}

/* Returneaza un vector nou sortat dupa nrInmatriculare crescator sau descrescator
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaNrInmatriculare(bool crescator) const {
    std::vector<Masina> rezultat;
    for (size_t i = 0; i < repo.getAll().size(); i++)
        rezultat.push_back(repo.getAll().at(i));
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator)
            return a.getNrInmatriculare() < b.getNrInmatriculare();
        return a.getNrInmatriculare() > b.getNrInmatriculare();
        });
    return rezultat;
}

/* Returneaza un vector nou sortat dupa tip crescator sau descrescator
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaTip(bool crescator) const {
    std::vector<Masina> rezultat;
    for (size_t i = 0; i < repo.getAll().size(); i++)
        rezultat.push_back(repo.getAll().at(i));
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (crescator)
            return a.getTip() < b.getTip();
        return a.getTip() > b.getTip();
        });
    return rezultat;
}

/* Returneaza un vector nou sortat dupa producator, apoi dupa model la egalitate
   @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
std::vector<Masina> Service::sorteazaDupaProducatorModel(bool crescator) const {
    std::vector<Masina> rezultat;
    for (size_t i = 0; i < repo.getAll().size(); i++)
        rezultat.push_back(repo.getAll().at(i));
    std::sort(rezultat.begin(), rezultat.end(), [crescator](const Masina& a, const Masina& b) {
        if (a.getProducator() == b.getProducator()) {
            if (crescator)
                return a.getModel() < b.getModel();
            return a.getModel() > b.getModel();
        }
        if (crescator)
            return a.getProducator() < b.getProducator();
        return a.getProducator() > b.getProducator();
        });
    return rezultat;
}