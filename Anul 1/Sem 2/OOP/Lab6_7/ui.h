#pragma once
#include "service.h"
#include "MyList.h"
#include <vector>

/* Clasa Ui gestioneaza interfata cu utilizatorul
   Citeste comenzi de la tastatura si afiseaza rezultatele
   Vorbeste doar cu Service, nu stie cum sunt stocate datele */
class Ui {
private:
    Service& service;

    /* Afiseaza o lista MyList de masini numerotata
       @param masini: lista de masini de afisat ; @return: - */
    void afiseazaMasini(const MyList<Masina>& masini) const;

    /* Afiseaza un vector de masini numerotata
       @param masini: lista de masini de afisat ; @return: - */
    void afiseazaMasini(const std::vector<Masina>& masini) const;

    /* Citeste datele unei masini si o adauga prin service
       @param: - ; @return: - */
    void adauga_masina();

    /* Citeste nrInmatriculare si sterge masina prin service
       @param: - ; @return: - */
    void sterge_masina();

    /* Citeste datele noi ale unei masini si o modifica prin service
       @param: - ; @return: - */
    void modifica_masina();

    /* Citeste nrInmatriculare si afiseaza masina gasita
       @param: - ; @return: - */
    void cauta_masina();

    /* Afiseaza toate masinile din lista
       @param: - ; @return: - */
    void afisare_masini();

    /* Afiseaza submeniul de filtrare si afiseaza rezultatele
       @param: - ; @return: - */
    void filtrare_masini();

    /* Afiseaza submeniul de sortare si afiseaza rezultatele
       @param: - ; @return: - */
    void sortare_masini();

public:
    /* Initializeaza Ui-ul cu o referinta la service
       @param service: referinta la service ; @return: - */
    Ui(Service& service) noexcept;

    /* Afiseaza meniul principal si proceseaza comenzile utilizatorului
       @param: - ; @return: - */
    void run();
};