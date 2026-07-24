#pragma once
#include "masini.h"
#include "exceptii.h"
#include <vector>
#include <string>
#include <functional>

/* Clasa pur abstracta RepoAbstract - interfata pentru toate repository-urile
   Defineste contractul pe care orice repository trebuie sa-l respecte
   Service-ul va lucra prin referinta la aceasta clasa, fara sa stie ce repo concret se foloseste
   (polimorfism la runtime - se poate folosi Repository sau RepoDictionar interschimbabil) */
class RepoAbstract {
public:
    /* Destructor virtual - obligatoriu pentru clase abstracte
       Asigura ca delete pe pointer la baza apeleaza destructorul corect din clasa derivata
       @param: - ; @return: - */
    virtual ~RepoAbstract() = default;

    /* Adauga o masina in lista
       Arunca MasinaDuplicataException daca nrInmatriculare exista deja
       @param masina: masina de adaugat ; @return: - */
    virtual void adauga(const Masina& masina) = 0;

    /* Sterge masina cu nrInmatriculare dat
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
    virtual void sterge(const std::string& nrInmatriculare) = 0;

    /* Modifica producatorul, modelul si tipul masinii
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia ; @param producator: nou producator
       @param model: nou model ; @param tip: nou tip ; @return: - */
    virtual void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip) = 0;

    /* Modifica statusul de inchiriere al masinii
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia ; @param inchiriata: nou status ; @return: - */
    virtual void setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) = 0;

    /* Cauta masina dupa nrInmatriculare
       Arunca MasinaInexistentaException daca masina nu exista
       @param nrInmatriculare: cheia cautata
       @return: referinta constanta la masina gasita */
    virtual const Masina& cauta(const std::string& nrInmatriculare) const = 0;

    /* Verifica daca exista o masina cu nrInmatriculare dat
       @param nrInmatriculare: cheia cautata
       @return: true daca exista, false altfel */
    virtual bool exista(const std::string& nrInmatriculare) const = 0;

    /* Returneaza intreaga lista de masini (copie - pentru ca repo-uri diferite
       pot stoca diferit datele intern: vector vs map)
       @param: - ; @return: vector cu toate masinile */
    virtual std::vector<Masina> getAll() const = 0;

    /* Aplica o functie pe fiecare masina, fara copii
       Folosita de Service pentru iteratii eficiente (filtrare, raport, etc.)
       Mai eficient decat getAll() pentru ca evita copia vectorului
       @param f: functia care primeste o referinta constanta la fiecare masina
       @return: - */
    virtual void forEachMasina(const std::function<void(const Masina&)>& f) const = 0;

    /* Returneaza numarul de masini din lista
       @param: - ; @return: numarul de masini */
    virtual size_t size() const = 0;

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    /* Adauga o masina in lista de spalare
       @param masina: masina de adaugat ; @return: - */
    virtual void adaugaInListaSpalate(const Masina& masina) = 0;

    /* Goleste lista de spalare
       @param: - ; @return: - */
    virtual void golesteListaSpalate() = 0;

    /* Verifica daca o masina cu nrInmatriculare exista in lista de spalare
       @param nrInmatriculare: cheia cautata
       @return: true daca exista in lista de spalare, false altfel */
    virtual bool existaInListaSpalate(const std::string& nrInmatriculare) const = 0;

    /* Returneaza lista de spalare (copie)
       @param: - ; @return: vector cu masinile de spalat */
    virtual std::vector<Masina> getListaSpalate() const = 0;

    /* Returneaza numarul de masini din lista de spalare
       @param: - ; @return: numarul de masini din lista de spalare */
    virtual size_t lungimeListaSpalate() const = 0;
};
