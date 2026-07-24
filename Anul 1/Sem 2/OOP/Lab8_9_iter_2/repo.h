#pragma once
#include "repo_abstract.h"
#include "masini.h"
#include "exceptii.h"
#include <vector>
#include <string>

/* Clasa Repository stocheaza si acceseaza lista de masini intr-un std::vector
   Mosteneste din RepoAbstract pentru a permite folosirea polimorfica
   Suporta persistenta in fisier: la constructor citeste din fisier,
   dupa fiecare modificare salveaza in fisier */
class Repository : public RepoAbstract {
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
    void adauga(const Masina& masina) override;

    /* Sterge masina cu nrInmatriculare dat
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia dupa care se sterge ; @return: - */
    void sterge(const std::string& nrInmatriculare) override;

    /* Modifica producatorul, modelul si tipul masinii
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia ; @param producator: nou producator
       @param model: nou model ; @param tip: nou tip ; @return: - */
    void modifica(const std::string& nrInmatriculare, const std::string& producator,
        const std::string& model, const std::string& tip) override;

    /* Modifica statusul de inchiriere al masinii
       Salveaza in fisier la final daca persistenta e activa
       @param nrInmatriculare: cheia ; @param inchiriata: nou status ; @return: - */
    void setStatusInchiriere(const std::string& nrInmatriculare, bool inchiriata) override;

    /* Cauta masina dupa nrInmatriculare
       @param nrInmatriculare: cheia cautata ; @return: referinta la masina */
    const Masina& cauta(const std::string& nrInmatriculare) const override;

    /* Verifica daca exista o masina cu nrInmatriculare dat
       @param nrInmatriculare: cheia cautata ; @return: true/false */
    bool exista(const std::string& nrInmatriculare) const override;

    /* Returneaza copie cu toate masinile
       @param: - ; @return: vector cu toate masinile */
    std::vector<Masina> getAll() const override;

    /* Aplica o functie pe fiecare masina, fara copii
       @param f: functia callback ; @return: - */
    void forEachMasina(const std::function<void(const Masina&)>& f) const override;

    /* Returneaza referinta constanta la vector - varianta optimizata fara copiere
       Useful pentru iteratii STL pe lista interna
       @param: - ; @return: referinta constanta la vector */
    const std::vector<Masina>& getAllRef() const noexcept;

    /* Returneaza numarul de masini din lista
       @param: - ; @return: numarul de masini */
    size_t size() const override;

    /* ===== Metode pentru lista de spalare (cerinta 9) ===== */

    void adaugaInListaSpalate(const Masina& masina) override;
    void golesteListaSpalate() override;
    bool existaInListaSpalate(const std::string& nrInmatriculare) const override;
    std::vector<Masina> getListaSpalate() const override;
    size_t lungimeListaSpalate() const override;
};
