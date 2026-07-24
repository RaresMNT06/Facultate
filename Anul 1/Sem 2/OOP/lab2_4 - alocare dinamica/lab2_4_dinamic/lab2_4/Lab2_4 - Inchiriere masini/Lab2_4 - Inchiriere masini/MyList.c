#define _CRT_SECURE_NO_WARNINGS
#include "MyList.h"
#include <stdlib.h>

int FORTEAZA_EROARE_MALLOC_LIST = 0;

MyList* creeazaLista() {
    if (FORTEAZA_EROARE_MALLOC_LIST == 1)
        return NULL;

    MyList* list = (MyList*)malloc(sizeof(MyList));
    if (list == NULL || FORTEAZA_EROARE_MALLOC_LIST == 2) {
        if (list != NULL)
            free(list);
        return NULL;
    }

    list->lungime = 0;
    list->capacitate = 2;

    list->elemente = (TElem*)malloc(list->capacitate * sizeof(TElem));
    if (list->elemente == NULL || FORTEAZA_EROARE_MALLOC_LIST == 3) {
        if (list->elemente != NULL)
            free(list->elemente);
        free(list);
        return NULL;
    }

    return list;
}

void distrugeLista(MyList* list, DestroyFunc destroy) {
    if (list == NULL)
        return;

    if (destroy != NULL) {
        for (int i = 0; i < list->lungime; i++)
            destroy(list->elemente[i]);
    }

    free(list->elemente);
    free(list);
}

static int asiguraCapacitateLista(MyList* list) {
    if (list->lungime < list->capacitate)
        return 0;

    int nouaCapacitate = list->capacitate * 2;
    TElem* nou = (TElem*)realloc(list->elemente, nouaCapacitate * sizeof(TElem));
    //if (nou == NULL)
    //    return 1;

    list->elemente = nou;
    list->capacitate = nouaCapacitate;
    return 0;
}

int adaugaElement(MyList* list, TElem elem) {
    asiguraCapacitateLista(list);
    //if ( != 0)
    //    return 1;

    list->elemente[list->lungime] = elem;
    list->lungime++;
    return 0;
}

int stergeElement(MyList* list, int pos, DestroyFunc destroy) {
    if (pos < 0 || pos >= list->lungime)
        return 1;

    if (destroy != NULL)
        destroy(list->elemente[pos]);

    for (int i = pos; i < list->lungime - 1; i++)
        list->elemente[i] = list->elemente[i + 1];

    list->lungime--;
    return 0;
}

TElem getElement(MyList* list, int pos) {
    return list->elemente[pos];
}

void setElement(MyList* list, int pos, TElem elem) {
    list->elemente[pos] = elem;
}

int getLungimeLista(MyList* list) {
    return list->lungime;
}

MyList* copiazaLista(MyList* list, CopyFunc copy) {
    if (list == NULL)
        return NULL;

    MyList* copie = creeazaLista();
    //if (copie == NULL)
    //    return NULL;

    for (int i = 0; i < list->lungime; i++) {
        TElem elemCopiat = copy(list->elemente[i]);
        /*if (elemCopiat == NULL) {
            distrugeLista(copie, copy == NULL ? NULL : (DestroyFunc)free);
            return NULL;
        }*/
        adaugaElement(copie, elemCopiat);
        /*    distrugeLista(copie, (DestroyFunc)free);
            return NULL;
        }*/
    }

    return copie;
}