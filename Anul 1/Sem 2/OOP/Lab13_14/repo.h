#pragma once
#include "masini.h"
#include "exceptii.h"
#include <vector>
#include <string>
#include <functional>

/* Clasa Repository stocheaza si acceseaza lista de masini intr-un std::vector
   Suporta persistenta in fisier: la constructor citeste din fisier,
   dupa fiecare modificare salveaza in fisier */
class Repository {
private:
    std::vector<Masina> masini;     // lista principala de masini
    std::vector<Masina> spalate;    // lista de masini selectate pentru spalat
    std::string numeFisier;         // calea fisierului pentru persistenta (gol = fara persistenta)

    /* Salveaza toate masinile din vector in fisier (format CSV)
       Apelata automat dupa fiecare modificare a listei principale
       Nu salveaza lista de spalare (cerinta: cosul nu este persistent)
       @param: - ; @return: - */
    void salveazaInFisier() const;

    /* Citeste mesinile din fisier la pornire
       Daca fisierul nu exista, lista ramane goala
       @param: - ; @return: - */
    void incarcaDinFisier();

public:
    /* Constructor implicit - lista goala, fara persistenta
       @param: - ; @return: - */
    Repository() = default;

    /* Constructor cu persistenta - citeste mesinile din fisier la pornire
       Daca fisierul nu exista, lista ramane goala
       @param numeFisier: calea fisierului pentru salvare/incarcare ; @return: - */
    explicit Repository(const std::string& numeFisier);

    /* Adauga o masina in lista
       Arunca MasinaDuplicataException daca nrInmatriculare exista deja
       Salveaza in fisier la final daca persistenta e activa
       @param masina: masina de adaugat ; @return: - */
    void adauga(const Masina& masina);

    /* Sterge masina cu nrInmatriculare dat
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
    void sterge(const std::string& nrInmatriculare);

    /* Modifica producatorul, modelul si tipul masinii
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia ; @param producator: nou producator
       @param model: nou model ; @param tip: nou tip ; @return: - */
    void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip);

    /* Modifica statusul de inchiriere al masinii
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia ; @param inchiriata: nou status ; @return: - */
    void setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata);

    /* Cauta masina dupa nrInmatriculare
       @param nrInmatriculare: cheia cautata ; @return: referinta la masina */
    const Masina& cauta(const std::string& nrInmatriculare) const;

    /* Verifica daca exista o masina cu nrInmatriculare dat
       @param nrInmatriculare: cheia cautata ; @return: true/false */
    bool exista(const std::string& nrInmatriculare) const;

    /* Returneaza referinta constanta la vector - fara copie
       @param: - ; @return: referinta constanta la vector */
    const std::vector<Masina>& getAll() const noexcept;

    /* Aplica o functie pe fiecare masina, fara copii
       @param f: functia callback ; @return: - */
    void forEachMasina(const std::function<void(const Masina&)>& f) const;

    /* Returneaza numarul de masini din lista
       @param: - ; @return: numarul de masini */
    size_t size() const;

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    /* Adauga o masina in lista de spalare (push_back in vector)
       @param masina: masina de adaugat ; @return: - */
    void adaugaInListaSpalate(const Masina& masina);

    /* Goleste complet lista de spalare
       @param: - ; @return: - */
    void golesteListaSpalate();

    /* Verifica daca o masina cu nrInmatriculare exista in lista de spalare
       @param nrInmatriculare: cheia cautata ; @return: true/false */
    bool existaInListaSpalate(const std::string& nrInmatriculare) const;

    /* Returneaza referinta constanta la vector cu lista de spalat - fara copie
       @param: - ; @return: referinta la vectorul de masini de spalat */
    const std::vector<Masina>& getListaSpalate() const noexcept;

    /* Returneaza numarul de masini din lista de spalare
       @param: - ; @return: numarul de masini de spalat */
    size_t lungimeListaSpalate() const;
};
