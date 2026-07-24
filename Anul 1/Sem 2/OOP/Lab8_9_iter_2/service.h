#pragma once
#include "repo_abstract.h"
#include "actiune_undo.h"
#include "exceptii.h"
#include "dto.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

/* Clasa Service contine logica aplicatiei: validare, filtrare, sortare
   Iteratia 2: lucreaza cu RepoAbstract& (polimorfism) si suporta undo
   Tine o lista de unique_ptr<ActiuneUndo> care permite undo polimorfic
   Smart pointers pentru a evita memory leaks si slicing */
class Service {
private:
    RepoAbstract& repo;                                       // referinta la repo (abstract - polimorfism)
    std::vector<std::unique_ptr<ActiuneUndo>> actiuniUndo;    // stiva de actiuni reversibile

    /* Verifica daca caracterul este litera (a-z sau A-Z)
       @param c: caracterul de verificat
       @return: true daca e litera, false altfel */
    bool esteLitera(char c) const noexcept;

    /* Verifica daca caracterul este cifra (0-9)
       @param c: caracterul de verificat
       @return: true daca e cifra, false altfel */
    bool esteCifra(char c) const noexcept;

    /* Valideaza formatul numarului de inmatriculare
       @param nr: numarul de validat
       @return: true daca formatul e valid, false altfel */
    bool esteNrInmatriculareValid(const std::string& nr) const;

public:
    /* Initializeaza service-ul cu o referinta la repository abstract
       Datorita polimorfismului, repo poate fi Repository sau RepoDictionar
       @param repo: referinta la repository abstract
       @return: - */
    explicit Service(RepoAbstract& repo) noexcept;

    /* Valideaza si adauga o masina, salveaza actiunea pentru undo
       Arunca ValidareException pentru date invalide
       Arunca MasinaDuplicataException daca masina exista deja
       @param nrInmatriculare: cheia ; @param producator: producator
       @param model: modelul ; @param tip: tipul masinii
       @param inchiriata: statusul de inchiriere (default false) ; @return: - */
    void adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip, bool inchiriata = false);

    /* Valideaza si sterge masina, salveaza actiunea pentru undo
       (salvam masina inainte de stergere ca sa o putem reface la undo)
       @param nrInmatriculare: cheia ; @return: - */
    void stergeMasina(const std::string& nrInmatriculare);

    /* Valideaza si modifica masina, salveaza actiunea pentru undo
       (salvam masina inainte de modificare ca sa o putem reface la undo)
       @param nrInmatriculare: cheia ; @param producator: noul producator
       @param model: noul model ; @param tip: noul tip ; @return: - */
    void modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Cauta masina dupa nrInmatriculare
       @param nrInmatriculare: cheia cautata
       @return: copie a masinii (pentru ca repo-uri diferite stocheaza diferit) */
    Masina cautaMasina(const std::string& nrInmatriculare) const;

    /* Returneaza toate masinile (copie - din cauza interfetei abstracte)
       @param: -
       @return: vector cu toate masinile */
    std::vector<Masina> getToateMasinile() const;

    /* Filtreaza masinile dupa producator
       @param producator: producatorul cautat ; @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaProducator(const std::string& producator) const;

    /* Filtreaza masinile dupa tip
       @param tip: tipul cautat ; @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaTip(const std::string& tip) const;

    /* Sortare dupa nrInmatriculare
       @param crescator: true=crescator, false=descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaNrInmatriculare(bool crescator) const;

    /* Sortare dupa tip
       @param crescator: true=crescator, false=descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaTip(bool crescator) const;

    /* Sortare dupa producator + model
       @param crescator: true=crescator, false=descrescator ; @return: vector sortat */
    std::vector<Masina> sorteazaDupaProducatorModel(bool crescator) const;

    /* Inchiriaza o masina (status -> true)
       @param nrInmatriculare: cheia ; @return: - */
    void inchiriazaMasina(const std::string& nrInmatriculare);

    /* Returneaza o masina (status -> false)
       @param nrInmatriculare: cheia ; @return: - */
    void returneazaMasina(const std::string& nrInmatriculare);

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    void adaugaInListaSpalate(const std::string& nrInmatriculare);
    void golesteListaSpalate();
    void genereazaListaSpalate(size_t nrMasini);
    std::vector<Masina> getListaSpalate() const;
    size_t lungimeListaSpalate() const;
    void exportListaSpalate(const std::string& numeFisier) const;

    /* ===== Raport / Analiza (cerinta cu dictionar) ===== */

    std::map<std::string, DTO> analizaMasiniDupaTip() const;

    /* ===== UNDO (cerinta iteratia 2) ===== */

    /* Anuleaza ultima actiune (adaugare, stergere sau modificare)
       Foloseste polimorfism: apelam doUndo() pe pointerul abstract
       Arunca ValidareException daca nu mai sunt actiuni de anulat
       @param: - ; @return: - */
    void undo();

    /* Returneaza numarul de actiuni in stiva de undo
       Util pentru UI si teste
       @param: - ; @return: numarul de actiuni reversibile disponibile */
    size_t numarActiuniUndo() const noexcept;
};
