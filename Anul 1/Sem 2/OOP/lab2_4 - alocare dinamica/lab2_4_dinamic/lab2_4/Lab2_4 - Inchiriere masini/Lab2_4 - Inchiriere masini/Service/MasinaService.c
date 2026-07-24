#define _CRT_SECURE_NO_WARNINGS 
#include "MasinaService.h" 
#include <stdlib.h>
#include <string.h>

static void distrugeLista_Masini(void* lista) {
    distrugeLista((MyList*)lista, (DestroyFunc)distrugeMasina);
}

MasinaService* creeazaService(MyRepo* repo) {
    MasinaService* service = (MasinaService*)malloc(sizeof(MasinaService));
    //if (service == NULL)
    //    return NULL;

    service->repo = repo;
    service->undoList = creeazaLista();
    //if (service->undoList == NULL) {
    //    free(service);
    //    return NULL;
    //}

    return service;
}

void distrugeService(MasinaService* service) {
    if (service == NULL)
        return;

    distrugeRepo(service->repo);
    distrugeLista(service->undoList, (DestroyFunc)distrugeLista_Masini);
    free(service);
}

int esteLitera(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int esteCifra(char c) {
    return (c >= '0' && c <= '9');
}

int valideazaNrInmatriculare(const char* nrInmatriculare) {
    if (nrInmatriculare == NULL)
        return 0;

    int len = (int)strlen(nrInmatriculare);

    if (len == 9 && nrInmatriculare[1] != ' ') {
        if (!esteLitera(nrInmatriculare[0]) || !esteLitera(nrInmatriculare[1]))
            return 0;
        if (nrInmatriculare[2] != ' ')
            return 0;
        if (!esteCifra(nrInmatriculare[3]) || !esteCifra(nrInmatriculare[4]))
            return 0;
        /*if (nrInmatriculare[5] != ' ')
            return 0;*/
        if (!esteLitera(nrInmatriculare[6]) || !esteLitera(nrInmatriculare[7]) || !esteLitera(nrInmatriculare[8]))
            return 0;
        return 1;
    }

    if ((len == 8 || len == 9) && (nrInmatriculare[0] == 'B') && nrInmatriculare[1] == ' ') {
        if (len == 9) {
            if (!esteCifra(nrInmatriculare[2]) || !esteCifra(nrInmatriculare[3]) || !esteCifra(nrInmatriculare[4]))
                return 0;
            if (nrInmatriculare[5] != ' ')
                return 0;
            if (!esteLitera(nrInmatriculare[6]) || !esteLitera(nrInmatriculare[7]) || !esteLitera(nrInmatriculare[8]))
                return 0;
        }
        else {
            if (!esteCifra(nrInmatriculare[2]) || !esteCifra(nrInmatriculare[3]))
                return 0;
            if (nrInmatriculare[4] != ' ')
                return 0;
            if (!esteLitera(nrInmatriculare[5]) || !esteLitera(nrInmatriculare[6]) || !esteLitera(nrInmatriculare[7]))
                return 0;
        }
        return 1;
    }

    return 0;
}

int adaugaMasinaService(MasinaService* service, const char* nrInmatriculare, const char* model, const char* categorie) {
    if (!valideazaNrInmatriculare(nrInmatriculare))
        return 1;

    if (strlen(model) == 0 || strlen(categorie) == 0)
        return 1;

    int lungime = getLungime(service->repo);
    for (int i = 0; i < lungime; i++) {
        Masina* m = getMasina(service->repo, i);
        if (strcmp(m->nrInmatriculare, nrInmatriculare) == 0)
            return 3;
    }

    MyList* snapshot = getCopieLista(service->repo);
    if (snapshot != NULL)
        adaugaElement(service->undoList, snapshot);

    Masina* m = creeazaMasina(nrInmatriculare, model, categorie);
    return adaugaMasinaRepo(service->repo, m);
}

int modificaMasinaService(MasinaService* service, const char* nrInmatriculare, const char* modelNou, const char* categorieNoua) {
    if (strlen(modelNou) == 0 || strlen(categorieNoua) == 0)
        return 1;

    MyList* snapshot = getCopieLista(service->repo);
    if (snapshot != NULL)
        adaugaElement(service->undoList, snapshot);

    Masina* mNoua = creeazaMasina(nrInmatriculare, modelNou, categorieNoua);
    int rezultat = modificaMasinaRepo(service->repo, mNoua);
    distrugeMasina(mNoua);

    if (rezultat == 1)
        return 2;

    return 0;
}

int stergeMasinaService(MasinaService* service, const char* nrInmatriculare) {
    MyList* snapshot = getCopieLista(service->repo);
    if (snapshot != NULL)
        adaugaElement(service->undoList, snapshot);

    return stergeMasinaRepo(service->repo, nrInmatriculare);
}

Masina getMasinaService(MasinaService* service, int pos) {
    Masina* m = getMasina(service->repo, pos);
    return *m;
}

void filtreazaMasiniCategorie(MasinaService* service, const char* categorie, Masina* rezultate[], int* nrRezultate) {
    *nrRezultate = 0;
    int lungime = getLungime(service->repo);
    for (int i = 0; i < lungime; i++) {
        Masina* m = getMasina(service->repo, i);
        if (strcmp(m->categorie, categorie) == 0) {
            rezultate[*nrRezultate] = m;
            (*nrRezultate)++;
        }
    }
}

void filtreazaMasiniModel(MasinaService* service, const char* model, Masina* rezultate[], int* nrRezultate) {
    *nrRezultate = 0;
    int lungime = getLungime(service->repo);
    for (int i = 0; i < lungime; i++) {
        Masina* m = getMasina(service->repo, i);
        if (strstr(m->model, model) != NULL) {
            rezultate[*nrRezultate] = m;
            (*nrRezultate)++;
        }
    }
}

void filtreazaMasiniStatus(MasinaService* service, int status, Masina* rezultate[], int* nrRezultate) {
    *nrRezultate = 0;
    int lungime = getLungime(service->repo);
    for (int i = 0; i < lungime; i++) {
        Masina* m = getMasina(service->repo, i);
        if (m->esteInchiriata == status) {
            rezultate[*nrRezultate] = m;
            (*nrRezultate)++;
        }
    }
}

int inchiriazaMasinaService(MasinaService* service, const char* nrInmatriculare) {
    int lungime = getLungime(service->repo);
    for (int i = 0; i < lungime; i++) {
        Masina* m = getMasina(service->repo, i);
        if (strcmp(m->nrInmatriculare, nrInmatriculare) == 0) {
            if (m->esteInchiriata == 1)
                return 2;
            return setStareInchiriereRepo(service->repo, nrInmatriculare, 1);
        }
    }
    return 1;
}

int returneazaMasinaService(MasinaService* service, const char* nrInmatriculare) {
    return setStareInchiriereRepo(service->repo, nrInmatriculare, 0);
}

int undoService(MasinaService* service) {
    int n = getLungimeLista(service->undoList);
    if (n == 0)
        return 1;

    MyList* snapshot = (MyList*)getElement(service->undoList, n - 1);
    restaureazaLista(service->repo, snapshot);
    service->undoList->lungime--;
    return 0;
}

void sorteazaMasiniService(MasinaService* service, int tip, int revers, Masina* rezultate[], int* numar) {
    *numar = getLungime(service->repo);
    for (int i = 0; i < *numar; i++)
        rezultate[i] = getMasina(service->repo, i);

    for (int i = 0; i < *numar - 1; i++) {
        for (int j = i + 1; j < *numar; j++) {
            int r = 0;

            if (tip == 1)
                r = strcmp(rezultate[i]->model, rezultate[j]->model);
            else
                r = strcmp(rezultate[i]->categorie, rezultate[j]->categorie);

            int trebuieInversat = 0;
            if (revers == 0 && r > 0)
                trebuieInversat = 1;
            if (revers == 1 && r < 0)
                trebuieInversat = 1;

            if (trebuieInversat) {
                Masina* aux = rezultate[i];
                rezultate[i] = rezultate[j];
                rezultate[j] = aux;
            }
        }
    }
}