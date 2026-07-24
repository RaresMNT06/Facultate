#pragma once
#include "service.h"
#include <vector>

/* Clasa Ui gestioneaza interfata cu utilizatorul
   Citeste comenzi de la tastatura si afiseaza rezultatele
   Vorbeste doar cu Service, nu stie cum sunt stocate datele
   Prinde exceptiile aruncate de Service si le afiseaza ca mesaje */
class Ui {
private:
    Service& service;

    /* Afiseaza o lista de masini numerotata
       @param masini: lista de masini de afisat
       @return: - */
    void afiseazaMasini(const std::vector<Masina>& masini) const;

    /* Citeste datele unei masini de la tastatura si o adauga prin service
       @param: -
       @return: - */
    void adaugaMasina();

    /* Citeste nrInmatriculare si sterge masina prin service
       @param: -
       @return: - */
    void stergeMasina();

    /* Citeste datele noi ale unei masini si o modifica prin service
       @param: -
       @return: - */
    void modificaMasina();

    /* Citeste nrInmatriculare si afiseaza masina gasita
       @param: -
       @return: - */
    void cautaMasina();

    /* Afiseaza toate masinile din lista
       @param: -
       @return: - */
    void afisareMasini();

    /* Afiseaza submeniul de filtrare si afiseaza rezultatele
       @param: -
       @return: - */
    void filtrareMasini();

    /* Afiseaza submeniul de sortare si afiseaza rezultatele
       @param: -
       @return: - */
    void sortareMasini();

    /* Citeste nrInmatriculare si marcheaza masina ca inchiriata prin service
       @param: -
       @return: - */
    void inchiriereMasina();

    /* Citeste nrInmatriculare si marcheaza masina ca returnata prin service
       @param: -
       @return: - */
    void returnareMasina();

    /* Submeniu pentru cerinta 9: gestionarea listei de masini de spalat
       Optiuni: Goleste, Adauga, Genereaza, Export
       Dupa fiecare actiune se afiseaza numarul total de masini din lista
       @param: -
       @return: - */
    void meniuSpalare();

    /* Afiseaza raportul cu numarul de masini grupate dupa tip
       Foloseste un dictionar (std::map) populat de Service
       @param: -
       @return: - */
    void afiseazaRaport();

public:
    /* Initializeaza Ui-ul cu o referinta la service
       explicit pentru a preveni conversii implicite
       @param service: referinta la service
       @return: - */
    explicit Ui(Service& service) noexcept;

    /* Afiseaza meniul principal si proceseaza comenzile utilizatorului
       Ruleaza pana cand utilizatorul alege iesirea
       @param: -
       @return: - */
    void run();
};