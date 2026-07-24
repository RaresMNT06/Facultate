#pragma once
#include "repo.h"
#include "MyList.h"
#include <vector>
#include <string>

/* Clasa Service contine logica aplicatiei: validare, filtrare, sortare
   Vorbeste doar cu Repository, nu stie cum sunt stocate datele */
class Service {
private:
    Repository& repo;

    /* Verifica daca caracterul este litera
       @param c: caracterul ; @return: true daca e litera */
    bool esteLitera(char c) const noexcept;

    /* Verifica daca caracterul este cifra
       @param c: caracterul ; @return: true daca e cifra */
    bool esteCifra(char c) const noexcept;

    /* Valideaza formatul numarului de inmatriculare
       @param nr: numarul de validat ; @return: true daca e valid */
    bool esteNrInmatriculareValid(const std::string& nr) const;

public:
    /* Initializeaza service-ul cu o referinta la repository
       @param repo: referinta la repository ; @return: - */
    Service(Repository& repo) noexcept;

    /* Valideaza si adauga o masina. Arunca exceptie daca un camp e gol sau masina exista deja
       @param nrInmatriculare: cheia unica ; @param producator: producatorul
       @param model: modelul ; @param tip: tipul masinii ; @return: - */
    void adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Valideaza si sterge masina cu nrInmatriculare dat. Arunca exceptie daca nu exista
       @param nrInmatriculare: cheia de identificare ; @return: - */
    void stergeMasina(const std::string& nrInmatriculare);

    /* Valideaza si modifica masina identificata prin nrInmatriculare
       Arunca exceptie daca un camp e gol sau masina nu exista
       @param nrInmatriculare: cheia de identificare
       @param producator, model, tip: noile valori ; @return: - */
    void modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Cauta masina dupa nrInmatriculare. Arunca exceptie daca nu exista sau campul e gol
       @param nrInmatriculare: cheia cautata ; @return: referinta constanta la masina gasita */
    const Masina& cautaMasina(const std::string& nrInmatriculare) const;

    /* Returneaza toata lista de masini fara copiere
       @param: - ; @return: referinta constanta la lista de masini */
    const MyList<Masina>& getToateMasinile() const noexcept;

    /* Returneaza un vector nou cu masinile care au producatorul dat
       @param producator: producatorul cautat ; @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaProducator(const std::string& producator) const;

    /* Returneaza un vector nou cu masinile care au tipul dat
       @param tip: tipul cautat ; @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaTip(const std::string& tip) const;

    /* Returneaza un vector nou sortat dupa nrInmatriculare crescator sau descrescator
       @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaNrInmatriculare(bool crescator) const;

    /* Returneaza un vector nou sortat dupa tip crescator sau descrescator
       @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaTip(bool crescator) const;

    /* Returneaza un vector nou sortat dupa producator, apoi dupa model la egalitate
       @param crescator: true = crescator, false = descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaProducatorModel(bool crescator) const;
};