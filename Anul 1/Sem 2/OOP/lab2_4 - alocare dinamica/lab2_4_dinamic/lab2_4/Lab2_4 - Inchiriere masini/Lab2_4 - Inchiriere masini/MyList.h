#ifndef MYLIST_H
#define MYLIST_H

typedef void* TElem;
typedef void (*DestroyFunc)(TElem);
typedef TElem(*CopyFunc)(TElem);

typedef struct {
    TElem* elemente;
    int lungime;
    int capacitate;
} MyList;

/*
 * Creeaza o lista noua goala
 * return: pointer catre MyList, NULL daca alocarea esueaza
 */
MyList* creeazaLista();

/*
 * Distruge lista si elementele din ea folosind functia destroy furnizata
 * Daca destroy este NULL, elementele nu sunt eliberate (util pentru liste de pointeri imprumutati)
 */
void distrugeLista(MyList* list, DestroyFunc destroy);

/*
 * Adauga un element la sfarsitul listei
 * return: 0 succes, 1 eroare
 */
int adaugaElement(MyList* list, TElem elem);

/*
 * Sterge elementul de la pozitia data, apeland destroy pe el
 * return: 0 succes, 1 pozitie invalida
 */
int stergeElement(MyList* list, int pos, DestroyFunc destroy);

/*
 * Returneaza elementul de la pozitia pos
 */
TElem getElement(MyList* list, int pos);

/*
 * Seteaza elementul de la pozitia pos
 */
void setElement(MyList* list, int pos, TElem elem);

/*
 * Returneaza numarul de elemente din lista
 */
int getLungimeLista(MyList* list);

/*
 * Creeaza o copie profunda a listei folosind functia copy furnizata
 * return: lista noua independenta, NULL daca alocarea esueaza
 */
MyList* copiazaLista(MyList* list, CopyFunc copy);

#endif