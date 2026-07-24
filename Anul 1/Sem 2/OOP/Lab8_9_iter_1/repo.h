#pragma once
#include "masini.h"
#include "exceptii.h"
#include <vector>
#include <string>

/* Clasa Repository stocheaza si acceseaza lista de masini in memorie
   Nu valideaza date si nu contine logica - doar operatii directe pe lista
   Arunca exceptii proprii pentru operatii invalide (duplicat, inexistent)
   Stocheaza si o lista separata de masini de spalat (cerinta 9 - Inchiriere masini) */
class Repository {
private:
    std::vector<Masina> masini;     // lista principala de masini stocata in memorie
    std::vector<Masina> spalate;    // lista de masini selectate pentru spalat

public:
    /* Adauga o masina in lista
       Arunca MasinaDuplicataException daca nrInmatriculare exista deja
       @param masina: masina de adaugat
       @return: - */
    void adauga(const Masina& masina);

    /* Sterge masina cu nrInmatriculare dat
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia dupa care se sterge
       @return: - */
    void sterge(const std::string& nrInmatriculare);

    /* Modifica producatorul, modelul si tipul masinii identificate prin nrInmatriculare
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia de identificare
       @param producator: noul producator
       @param model: noul model
       @param tip: noul tip
       @return: - */
    void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Modifica statusul de inchiriere al masinii identificate prin nrInmatriculare
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia de identificare
       @param inchiriata: noul status de inchiriere
       @return: - */
    void setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata);

    /* Cauta masina dupa nrInmatriculare
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia cautata
       @return: referinta constanta la masina gasita */
    const Masina& cauta(const std::string& nrInmatriculare) const;

    /* Verifica daca exista o masina cu nrInmatriculare dat
       Nu arunca exceptii - returneaza doar true/false
       @param nrInmatriculare: cheia cautata
       @return: true daca exista, false altfel */
    bool exista(const std::string& nrInmatriculare) const noexcept;

    /* Returneaza intreaga lista de masini fara copiere
       @param: -
       @return: referinta constanta la vectorul de masini */
    const std::vector<Masina>& getAll() const noexcept;

    /* Returneaza numarul de masini din lista
       @param: -
       @return: numarul de masini */
    size_t size() const noexcept;

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    /* Adauga o masina in lista de spalare
       Nu verifica duplicate - apelantul (Service) trebuie sa o faca
       @param masina: masina de adaugat in lista de spalare
       @return: - */
    void adaugaInListaSpalate(const Masina& masina);

    /* Goleste lista de spalare - elimina toate masinile
       @param: -
       @return: - */
    void golesteListaSpalate() noexcept;

    /* Verifica daca o masina cu nrInmatriculare dat exista in lista de spalare
       @param nrInmatriculare: cheia cautata
       @return: true daca exista in lista de spalare, false altfel */
    bool existaInListaSpalate(const std::string& nrInmatriculare) const noexcept;

    /* Returneaza intreaga lista de spalare fara copiere
       @param: -
       @return: referinta constanta la vectorul cu masinile de spalat */
    const std::vector<Masina>& getListaSpalate() const noexcept;

    /* Returneaza numarul de masini din lista de spalare
       @param: -
       @return: numarul de masini din lista de spalare */
    size_t lungimeListaSpalate() const noexcept;
};