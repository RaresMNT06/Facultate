#pragma once
#include "repo_abstract.h"
#include "masini.h"
#include "exceptii.h"
#include <map>
#include <random>

/* Clasa RepoDictionar - implementare alternativa de Repository folosind std::map
   Stocheaza masinile intr-un dictionar (cheia = nrInmatriculare)
   Cerinta iteratia 2: La constructor primeste o probabilitate (intre 0 si 1)
   Daca apelam orice metoda din repo, metoda arunca exceptie cu probabilitatea data
   Repo-ul este volatil (in memorie) - nu salveaza in fisier */
class RepoDictionar : public RepoAbstract {
private:
    std::map<std::string, Masina> masini;     // dictionar nrInm -> Masina
    std::map<std::string, Masina> spalate;    // dictionar pentru lista de spalare
    double probabilitateEroare;               // probabilitate intre 0 si 1
    mutable std::mt19937 generator;           // generator random (mutable - folosit in metode const)

    /* Verifica daca trebuie sa arunce exceptie pe baza probabilitatii
       Genereaza un numar random intre 0 si 1 si compara cu probabilitateEroare
       Apelat la inceputul fiecarei metode publice
       @param: - ; @return: - (sau arunca ValidareException) */
    void verificaProbabilitate() const;

public:
    /* Constructor cu probabilitate
       @param probabilitate: valoare intre 0 si 1 - probabilitatea ca o metoda sa esueze
       Arunca ValidareException daca probabilitatea e in afara intervalului [0, 1]
       @return: - */
    explicit RepoDictionar(double probabilitate);

    /* Adauga o masina in dictionar
       Arunca MasinaDuplicataException daca exista deja
       Arunca ValidareException cu probabilitatea data ; @return: - */
    void adauga(const Masina& masina) override;

    /* Sterge masina dupa cheie ; @return: - */
    void sterge(const std::string& nrInmatriculare) override;

    /* Modifica datele unei masini ; @return: - */
    void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip) override;

    /* Modifica statusul de inchiriere ; @return: - */
    void setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) override;

    /* Cauta masina dupa cheie
       @return: referinta la masina */
    const Masina& cauta(const std::string& nrInmatriculare) const override;

    /* Verifica existenta dupa cheie
       @return: true/false */
    bool exista(const std::string& nrInmatriculare) const override;

    /* Returneaza toate masinile - construieste un vector din valorile dictionarului
       @return: vector cu toate masinile */
    std::vector<Masina> getAll() const override;

    /* Aplica o functie pe fiecare masina fara copii
       @param f: functia callback ; @return: - */
    void forEachMasina(const std::function<void(const Masina&)>& f) const override;

    /* Returneaza numarul de masini
       @return: numarul de masini */
    size_t size() const override;

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    void adaugaInListaSpalate(const Masina& masina) override;
    void golesteListaSpalate() override;
    bool existaInListaSpalate(const std::string& nrInmatriculare) const override;
    std::vector<Masina> getListaSpalate() const override;
    size_t lungimeListaSpalate() const override;
};
