#ifndef CONSOLA_H
#define CONSOLA_H

#include "Service/MasinaService.h"

typedef struct {
    MasinaService* service;
} Consola;

Consola* creeazaConsola(MasinaService* service);

void distrugeConsola(Consola* ui);

void printMeniu();

/*
 * Citeste datele de la tastatura si incearca sa adauge o masina
 */
void uiAdauga(Consola* ui);

/*
 * Citeste numarul de inmatriculare si noile date pentru a modifica o masina
 */
void uiModifica(Consola* ui);

/*
 * Afiseaza toate masinile din sistem si statusul lor (LIBERA/INCHIRIATA)
 */
void uiAfisare(Consola* ui);

/*
 * Citeste numarul de inmatriculare si sterge masina
 */
void uiSterge(Consola* ui);

/*
 * Solicita criteriile de filtrare si afiseaza rezultatele gasite
 */
void uiFiltrare(Consola* ui);

/*
 * Filtreaza masinile dupa statusul de inchiriere
 */
void uiFiltrareStatus(Consola* ui);

void uiInchiriaza(Consola* ui);
void uiReturneaza(Consola* ui);
void uiGestiuneStare(Consola* ui);

/*
 * Solicita criteriile de sortare (criteriu si sens) si afiseaza lista sortata
 */
void uiSortare(Consola* ui);

/*
 * Anuleaza ultima operatie efectuata
 */
void uiUndo(Consola* ui);

/*
 * Functia principala a interfetei; gestioneaza meniul si comenzile utilizatorului
 */
void ruleazaConsola(Consola* ui);

#endif