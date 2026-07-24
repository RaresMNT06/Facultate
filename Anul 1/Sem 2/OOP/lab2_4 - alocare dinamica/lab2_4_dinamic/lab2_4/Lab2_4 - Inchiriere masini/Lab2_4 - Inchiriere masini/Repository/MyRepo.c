#define _CRT_SECURE_NO_WARNINGS
#include "MyRepo.h"
#include <stdlib.h>
#include <string.h>

int FORTEAZA_EROARE_MALLOC_REPO = 0;

MyRepo* creeazaRepo() {
    if (FORTEAZA_EROARE_MALLOC_REPO == 1)
        return NULL;

    MyRepo* repo = (MyRepo*)malloc(sizeof(MyRepo));
    if (repo == NULL || FORTEAZA_EROARE_MALLOC_REPO == 2) {
        if (repo != NULL)
            free(repo);
        return NULL;
    }

    repo->listaMasini = creeazaLista();
    if (repo->listaMasini == NULL || FORTEAZA_EROARE_MALLOC_REPO == 3) {
        if (repo->listaMasini != NULL)
            distrugeLista(repo->listaMasini, NULL);
        free(repo);
        return NULL;
    }

    return repo;
}

void distrugeRepo(MyRepo* repo) {
    if (repo == NULL)
        return;

    distrugeLista(repo->listaMasini, (DestroyFunc)distrugeMasina);
    free(repo);
}

int adaugaMasinaRepo(MyRepo* repo, Masina* m) {
    return adaugaElement(repo->listaMasini, m);
}

int modificaMasinaRepo(MyRepo* repo, Masina* masinaNoua) {
    int lungime = getLungimeLista(repo->listaMasini);
    for (int i = 0; i < lungime; i++) {
        Masina* m = (Masina*)getElement(repo->listaMasini, i);
        if (strcmp(m->nrInmatriculare, masinaNoua->nrInmatriculare) == 0) {
            free(m->model);
            free(m->categorie);

            m->model = (char*)malloc(strlen(masinaNoua->model) + 1);
            if (m->model != NULL)
                strcpy(m->model, masinaNoua->model);

            m->categorie = (char*)malloc(strlen(masinaNoua->categorie) + 1);
            if (m->categorie != NULL)
                strcpy(m->categorie, masinaNoua->categorie);

            return 0;
        }
    }
    return 1;
}

int stergeMasinaRepo(MyRepo* repo, const char* nrInmatriculare) {
    int lungime = getLungimeLista(repo->listaMasini);
    for (int i = 0; i < lungime; i++) {
        Masina* m = (Masina*)getElement(repo->listaMasini, i);
        if (strcmp(m->nrInmatriculare, nrInmatriculare) == 0)
            return stergeElement(repo->listaMasini, i, (DestroyFunc)distrugeMasina);
    }
    return 1;
}

int getLungime(MyRepo* repo) {
    return getLungimeLista(repo->listaMasini);
}

Masina* getMasina(MyRepo* repo, int pos) {
    return (Masina*)getElement(repo->listaMasini, pos);
}

int setStareInchiriereRepo(MyRepo* repo, const char* nrInmatriculare, int status) {
    int lungime = getLungimeLista(repo->listaMasini);
    for (int i = 0; i < lungime; i++) {
        Masina* m = (Masina*)getElement(repo->listaMasini, i);
        if (strcmp(m->nrInmatriculare, nrInmatriculare) == 0) {
            m->esteInchiriata = status;
            return 0;
        }
    }
    return 1;
}

MyList* getCopieLista(MyRepo* repo) {
    return copiazaLista(repo->listaMasini, (CopyFunc)copiazaMasina);
}

void restaureazaLista(MyRepo* repo, MyList* snapshot) {
    distrugeLista(repo->listaMasini, (DestroyFunc)distrugeMasina);
    repo->listaMasini = snapshot;
}