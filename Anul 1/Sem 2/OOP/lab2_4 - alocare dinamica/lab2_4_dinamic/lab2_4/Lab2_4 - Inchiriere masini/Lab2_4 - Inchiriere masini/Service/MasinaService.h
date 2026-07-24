#ifndef MASINASERVICE_H 
#define MASINASERVICE_H 

#include "Repository/MyRepo.h"
#include "MyList.h"

typedef struct {
    MyRepo* repo;
    MyList* undoList;
} MasinaService;

/*
 * Creeaza un service nou care gestioneaza un repository dat
 */
MasinaService* creeazaService(MyRepo* repo);

void distrugeService(MasinaService* service);

int esteLitera(char c);

int esteCifra(char c);

int valideazaNrInmatriculare(const char* nrInmatriculare);

/*
 * Valideaza si adauga o masina in sistem
 * return: 0 pentru succes, 1 pentru date invalide, 3 pentru duplicat
 */
int adaugaMasinaService(MasinaService* service, const char* nrInmatriculare, const char* model, const char* categorie);

/*
 * Valideaza datele noi si modifica o masina existenta
 * return: 0 succes, 1 date invalide, 2 masina inexistenta
 */
int modificaMasinaService(MasinaService* service, const char* nrInmatriculare, const char* modelNou, const char* categorieNoua);

/*
 * Sterge masina cu numarul de inmatriculare dat
 * return: 0 succes, 1 daca masina nu exista
 */
int stergeMasinaService(MasinaService* service, const char* nrInmatriculare);

Masina getMasinaService(MasinaService* service, int pos);

/*
 * Filtreaza masinile dupa o categorie data
 * rezultate: vector in care se salveaza masinile gasite
 * nrRezultate: pointer in care se salveaza numarul de masini gasite
 */
void filtreazaMasiniCategorie(MasinaService* service, const char* categorie, Masina* rez[], int* nrRezultate);

/*
 * Filtreaza masinile dupa model (cautare partiala)
 * rezultate: vector in care se salveaza masinile gasite
 * nrRezultate: pointer in care se salveaza numarul de masini gasite
 */
void filtreazaMasiniModel(MasinaService* service, const char* model, Masina* rezultate[], int* nrRezultate);

/*
 * Filtreaza masinile dupa statusul de inchiriere
 * status: 1 pentru inchiriate, 0 pentru libere
 * rezultate: vector in care se salveaza masinile gasite
 * nrRezultate: pointer in care se salveaza numarul de masini gasite
 */
void filtreazaMasiniStatus(MasinaService* service, int status, Masina* rezultate[], int* nrRezultate);

/*
 * Sorteaza masinile din sistem dupa model sau categorie
 * tip: 1 pentru Model, 2 pentru Categorie
 * revers: 0 pentru Crescator, 1 pentru Descrescator
 * rezultate: vectorul in care se copiaza datele sortate
 */
void sorteazaMasiniService(MasinaService* service, int tip, int revers, Masina* rezultate[], int* numar);

/*
 * Schimba statusul unei masini in 'inchiriata'
 * return: 0 succes, 2 deja inchiriata, 1 masina inexistenta
 */
int inchiriazaMasinaService(MasinaService* service, const char* nrInmatriculare);

/*
 * Schimba statusul unei masini in 'libera'
 * return: 0 succes, 1 masina inexistenta
 */
int returneazaMasinaService(MasinaService* service, const char* nrInmatriculare);

/*
 * Anuleaza ultima operatie efectuata (adauga/modifica/sterge)
 * return: 0 succes, 1 daca nu mai sunt operatii de anulat
 */
int undoService(MasinaService* service);

#endif