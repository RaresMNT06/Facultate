#pragma once
#include "repo.h"
#include "exceptii.h"
#include "dto.h"
#include <vector>
#include <string>
#include <map>

/* Clasa Service contine logica aplicatiei: validare, filtrare, sortare
   Vorbeste doar cu Repository, nu stie cum sunt stocate datele
   Arunca exceptii proprii pentru date invalide (ValidareException)
   si propaga exceptiile Repository-ului (MasinaDuplicataException, MasinaInexistentaException) */
class Service {
private:
    Repository& repo;

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
    /* Initializeaza service-ul cu o referinta la repository
       explicit pentru a preveni conversii implicite
       @param repo: referinta la repository
       @return: - */
    explicit Service(Repository& repo) noexcept;

    /* Valideaza si adauga o masina
       Arunca ValidareException daca un camp este gol sau nrInmatriculare invalid
       Arunca MasinaDuplicataException daca masina exista deja
       @param nrInmatriculare: cheia unica
       @param producator: producatorul
       @param model: modelul
       @param tip: tipul masinii
       @param inchiriata: statusul de inchiriere (default false)
       @return: - */
    void adaugaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip, bool inchiriata = false);

    /* Valideaza si sterge masina cu nrInmatriculare dat
       Arunca ValidareException daca nrInmatriculare este gol
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia de identificare
       @return: - */
    void stergeMasina(const std::string& nrInmatriculare);

    /* Valideaza si modifica masina identificata prin nrInmatriculare
       Arunca ValidareException daca un camp este gol
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia de identificare
       @param producator: noul producator
       @param model: noul model
       @param tip: noul tip
       @return: - */
    void modificaMasina(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Cauta masina dupa nrInmatriculare
       Arunca ValidareException daca nrInmatriculare este gol
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia cautata
       @return: referinta constanta la masina gasita */
    const Masina& cautaMasina(const std::string& nrInmatriculare) const;

    /* Returneaza toata lista de masini fara copiere
       @param: -
       @return: referinta constanta la vectorul de masini */
    const std::vector<Masina>& getToateMasinile() const noexcept;

    /* Returneaza un vector nou cu masinile care au producatorul dat
       Foloseste std::copy_if pentru filtrare
       @param producator: producatorul cautat
       @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaProducator(const std::string& producator) const;

    /* Returneaza un vector nou cu masinile care au tipul dat
       Foloseste std::copy_if pentru filtrare
       @param tip: tipul cautat
       @return: vector cu masinile filtrate */
    std::vector<Masina> filtreazaDupaTip(const std::string& tip) const;

    /* Returneaza un vector nou sortat dupa nrInmatriculare
       Foloseste std::sort cu un comparator lambda
       @param crescator: true pentru crescator, false pentru descrescator
       @return: vector nou sortat */
    std::vector<Masina> sorteazaDupaNrInmatriculare(bool crescator) const;

    /* Returneaza un vector nou sortat dupa tip
       Foloseste std::sort cu un comparator lambda
       @param crescator: true pentru crescator, false pentru descrescator
       @return: vector nou sortat */
    std::vector<Masina> sorteazaDupaTip(bool crescator) const;

    /* Returneaza un vector nou sortat dupa producator, apoi dupa model la egalitate
       Foloseste std::sort cu un comparator lambda compus
       @param crescator: true pentru crescator, false pentru descrescator
       @return: vector nou sortat */
    std::vector<Masina> sorteazaDupaProducatorModel(bool crescator) const;

    /* Marcheaza o masina ca inchiriata
       Arunca ValidareException daca campul e gol
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia masinii de inchiriat
       @return: - */
    void inchiriazaMasina(const std::string& nrInmatriculare);

    /* Marcheaza o masina ca returnata (disponibila)
       Arunca ValidareException daca campul e gol
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia masinii de returnat
       @return: - */
    void returneazaMasina(const std::string& nrInmatriculare);

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    /* Adauga o masina in lista de spalare dupa cautarea ei in repo
       Arunca ValidareException daca campul e gol
       Arunca MasinaInexistentaException daca masina nu exista in garaj
       Arunca ValidareException daca masina e deja in lista de spalare
       @param nrInmatriculare: cheia masinii de adaugat in lista de spalare
       @return: - */
    void adaugaInListaSpalate(const std::string& nrInmatriculare);

    /* Goleste lista de spalare - elimina toate masinile
       @param: -
       @return: - */
    void golesteListaSpalate() noexcept;

    /* Genereaza o lista de spalare aleatoare cu n masini
       Goleste lista existenta inainte de a o popula
       Foloseste std::default_random_engine cu seed din chrono::system_clock si std::shuffle
       Arunca ValidareException daca n este invalid (peste numarul de masini)
       @param nrMasini: numarul de masini de adaugat in lista de spalare
       @return: - */
    void genereazaListaSpalate(size_t nrMasini);

    /* Returneaza lista de spalare curenta fara copiere
       @param: -
       @return: referinta constanta la vectorul cu masinile de spalat */
    const std::vector<Masina>& getListaSpalate() const noexcept;

    /* Returneaza numarul de masini din lista de spalare
       @param: -
       @return: numarul de masini din lista de spalare */
    size_t lungimeListaSpalate() const noexcept;

    /* Exporta lista de spalare intr-un fisier CSV sau HTML
       Decide formatul dupa extensia fisierului (.csv sau .html / .htm)
       Arunca ValidareException daca fisierul nu poate fi deschis
       Arunca ValidareException daca extensia nu e suportata
       @param numeFisier: calea fisierului in care se salveaza
       @return: - */
    void exportListaSpalate(const std::string& numeFisier) const;

    /* ===== Raport / Analiza (cerinta cu dictionar) ===== */

    /* Genereaza un raport: pentru fiecare tip de masina (sedan, SUV, etc.)
       returneaza un DTO cu numele tipului si numarul de masini de acel tip
       Foloseste std::map ca sa tina evidenta categoriilor
       Raportul e specific aplicatiei: la o aplicatie de inchiriere masini
       e relevant sa stii cate masini ai pe fiecare categorie
       @param: -
       @return: dictionar tip -> DTO(tip, nrAparitii) */
    std::map<std::string, DTO> analizaMasiniDupaTip() const;
};