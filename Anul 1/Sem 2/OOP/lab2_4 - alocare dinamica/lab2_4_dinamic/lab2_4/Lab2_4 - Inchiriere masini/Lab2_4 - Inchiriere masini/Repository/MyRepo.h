#ifndef MYREPO_H 
#define MYREPO_H 

#include "Domain/Masina.h" 
#include "MyList.h"

typedef struct {
    MyList* listaMasini;
} MyRepo;


/*
 * Initializeaza un repository nou pe Heap
 * return: un pointer catre strctura MyRepo
 */
MyRepo* creeazaRepo();


/*
* Elibereaza toata memoria ocupata de repo si de masinile din el
*/
void distrugeRepo(MyRepo* repo);


/*
 * Adauga dinamic o masina (pointer) in lista
 * repo: pointer catre structura MyRepo
 * m: masina care urmeaza sa fie adaugata
 * return: 0 daca adaugarea a reusit, 1 daca repository-ul este plin
 */
int adaugaMasinaRepo(MyRepo* repo, Masina* m);


/*
 * Modifica modelul si categoria unei masini existente dupa numarul de inmatriculare
 * repo: pointer catre MyRepo
 * masinaNoua: structura ce contine numarul de inmatriculare cautat si noile date
 * return: 0 pentru succes, 1 daca masina nu a fost gasita sau lista e goala
 */
int modificaMasinaRepo(MyRepo* repo, Masina* masinaNoua);

/*
 * Returneaza numarul de masini din repository
 */

int getLungime(MyRepo* repo);

/*
 * Returneaza masina de la pozitia pos
 */

Masina* getMasina(MyRepo* repo, int pos);

/*
*Sterge masina cu numarul de inmatriculare dat
* return: 0 succes, 1 daca masina nu a fost gasita
*/
int stergeMasinaRepo(MyRepo* repo, const char* nrInmatriculare);

/*
 * Returneaza o copie independenta a listei curente de masini
 * Folosita pentru a salva snapshots pentru undo
 * return: MyList* copie, NULL daca alocarea esueaza
 */

MyList* getCopieLista(MyRepo* repo);

/*
 * Inlocuieste lista curenta cu un snapshot dat
 * Distruge lista curenta si preia snapshot-ul ca lista activa
 */

void restaureazaLista(MyRepo* repo, MyList* snapshot);

/*
 * Actualizeaza statusul de inchiriere al unei masini
 * status: 1 pentru inchiriata, 0 pentru libera
 * return: 0 daca a reusit, 1 daca masina nu exista
 */
int setStareInchiriereRepo(MyRepo* repo, const char* nrInmatriculare, int status);


#endif