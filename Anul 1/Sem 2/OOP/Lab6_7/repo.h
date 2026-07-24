#pragma once
#include "Masina.h"
#include "MyList.h"
#include <string>

/* Clasa Repository stocheaza si acceseaza lista de masini in memorie
   Nu valideaza date si nu contine logica - doar operatii directe pe lista */
class Repository {
private:
    MyList<Masina> masini;

public:
    /* Adauga o masina in lista. Arunca exceptie daca nrInmatriculare exista deja
       @param masina: masina de adaugat ; @return: - */
    void adauga(const Masina& masina);

    /* Sterge masina cu nrInmatriculare dat. Arunca exceptie daca nu exista
       @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
    void sterge(const std::string& nrInmatriculare);

    /* Modifica producatorul, modelul si tipul masinii identificate prin nrInmatriculare
       Arunca exceptie daca masina nu exista
       @param nrInmatriculare: cheia de identificare
       @param producator, model, tip: noile valori ; @return: - */
    void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Cauta masina dupa nrInmatriculare. Arunca exceptie daca nu exista
       @param nrInmatriculare: cheia cautata ; @return: referinta constanta la masina gasita */
    const Masina& cauta(const std::string& nrInmatriculare) const;

    /* Verifica daca exista o masina cu nrInmatriculare dat
       @param nrInmatriculare: cheia cautata ; @return: true daca exista */
    bool exista(const std::string& nrInmatriculare) const noexcept;

    /* Returneaza intreaga lista de masini fara copiere
       @param: - ; @return: referinta constanta la lista de masini */
    const MyList<Masina>& getAll() const noexcept;

    /* Returneaza numarul de masini din lista
       @param: - ; @return: numarul de masini */
    size_t size() const noexcept;
};