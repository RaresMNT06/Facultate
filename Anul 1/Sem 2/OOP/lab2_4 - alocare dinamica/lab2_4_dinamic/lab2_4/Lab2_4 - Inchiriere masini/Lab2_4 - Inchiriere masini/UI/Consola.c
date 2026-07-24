#define _CRT_SECURE_NO_WARNINGS 
#include "Consola.h" 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

Consola* creeazaConsola(MasinaService* service) {
    Consola* ui = (Consola*)malloc(sizeof(Consola));
    if (ui != NULL)
        ui->service = service;

    return ui;
}

void distrugeConsola(Consola* ui) {
    free(ui);
}

void printMeniu() {
    printf("\n--- INCHIRIERI MASINI ---\n");
    printf("1. Adauga masina\n");
    printf("2. Modifica masina\n");
    printf("3. Gestiune Inchiriere/Retur\n");
    printf("4. Filtrare masini\n");
    printf("5. Sortare masini\n");
    printf("6. Afisare masini\n");
    printf("7. Sterge masina\n");
    printf("8. Undo\n");
    printf("0. Iesire\n");
    printf("Comanda: ");
}

char* citesteStringDinamic() {
    int capacitate = 10;
    int lungime = 0;
    char* str = (char*)malloc(capacitate * sizeof(char));
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (lungime + 1 >= capacitate) {
            capacitate *= 2;
            char* nou = (char*)realloc(str, capacitate * sizeof(char));
            if (nou != NULL)
                str = nou;
        }
        if (str != NULL)
            str[lungime++] = (char)c;
    }
    if (str != NULL)
        str[lungime] = '\0';
    return str;
}

void uiAdauga(Consola* ui) {
    (void)getc(stdin);
    printf("Nr. inmatriculare (JJ CC LLL): ");
    char* nrInmatriculare = citesteStringDinamic();

    printf("Model: ");
    char* model = citesteStringDinamic();

    printf("Categorie: ");
    char* categorie = citesteStringDinamic();

    int rez = adaugaMasinaService(ui->service, nrInmatriculare, model, categorie);
    if (rez == 0)
        printf("Masina adaugata cu succes\n");
    else if (rez == 1)
        printf("Date invalide!\n");
    else if (rez == 3)
        printf("Eroare: Exista deja o masina cu acest numar de inmatriculare!\n");
    else
        printf("Eroare la adaugare!\n");

    free(nrInmatriculare);
    free(model);
    free(categorie);
}

void uiModifica(Consola* ui) {
    (void)getc(stdin);
    printf("Nr. inmatriculare (JJ CC LLL): ");
    char* nrInmatriculare = citesteStringDinamic();

    printf("Model nou: ");
    char* modelNou = citesteStringDinamic();

    printf("Categorie noua: ");
    char* categorieNoua = citesteStringDinamic();

    int rezultat = modificaMasinaService(ui->service, nrInmatriculare, modelNou, categorieNoua);
    if (rezultat == 0)
        printf("Masina a fost modificata cu succes\n");
    else if (rezultat == 1)
        printf("Datele noi sunt invalide!\n");
    else
        printf("Nu am gasit nicio masina cu numarul %s!\n", nrInmatriculare);

    free(nrInmatriculare);
    free(modelNou);
    free(categorieNoua);
}

void uiAfisare(Consola* ui) {
    int n = getLungime(ui->service->repo);
    if (n == 0) {
        printf("Momentan nu sunt masini in baza de date\n");
        return;
    }
    printf("\n--- LISTA MASINI ---\n");
    for (int i = 0; i < n; i++) {
        Masina* m = getMasina(ui->service->repo, i);
        if (m != NULL)
            printf("%d. [%s] | Model: %s | Categorie: %s | Status: %s\n", i + 1, m->nrInmatriculare, m->model, m->categorie, m->esteInchiriata == 1 ? "INCHIRIATA" : "LIBERA");
    }
}

void uiSterge(Consola* ui) {
    (void)getc(stdin);
    printf("Nr. inmatriculare: ");
    char* nrInmatriculare = citesteStringDinamic();

    int rezultat = stergeMasinaService(ui->service, nrInmatriculare);
    if (rezultat == 0)
        printf("Masina a fost stearsa cu succes\n");
    else
        printf("Eroare: Masina nu a fost gasita!\n");

    free(nrInmatriculare);
}

void uiFiltrare(Consola* ui) {
    printf("\nCriteriu:\n");
    printf("1. Categorie\n");
    printf("2. Model\n");
    printf("3. Status (libera/inchiriata)\n");
    printf("Optiune: ");

    int optiune;
    (void)scanf("%d", &optiune);
    (void)getc(stdin);

    if (optiune == 3) {
        uiFiltrareStatus(ui);
        return;
    }

    int nTotal = getLungime(ui->service->repo);
    Masina** rezultate = (Masina**)malloc(nTotal * sizeof(Masina*));
    int nrRezultate = 0;

    printf("Introduceti textul de cautat: ");
    char* criteriu = citesteStringDinamic();

    if (optiune == 1)
        filtreazaMasiniCategorie(ui->service, criteriu, rezultate, &nrRezultate);
    else if (optiune == 2)
        filtreazaMasiniModel(ui->service, criteriu, rezultate, &nrRezultate);
    else {
        printf("Optiune invalida!\n");
        free(criteriu);
        free(rezultate);
        return;
    }

    if (nrRezultate == 0)
        printf("Nu s-au gasit masini care sa corespunda criteriului\n");
    else {
        printf("--- REZULTATE FILTRARE ---\n");
        for (int i = 0; i < nrRezultate; i++)
            printf("%d. [%s] | %s | %s\n", i + 1, rezultate[i]->nrInmatriculare, rezultate[i]->model, rezultate[i]->categorie);
    }

    free(criteriu);
    free(rezultate);
}

void uiFiltrareStatus(Consola* ui) {
    printf("Status:\n");
    printf("1. Libere\n");
    printf("2. Inchiriate\n");
    printf("Optiune: ");

    int optiune;
    (void)scanf("%d", &optiune);
    (void)getc(stdin);

    if (optiune != 1 && optiune != 2) {
        printf("Optiune invalida!\n");
        return;
    }

    int status = (optiune == 2) ? 1 : 0;
    int nTotal = getLungime(ui->service->repo);
    Masina** rezultate = (Masina**)malloc(nTotal * sizeof(Masina*));
    int nrRezultate = 0;

    filtreazaMasiniStatus(ui->service, status, rezultate, &nrRezultate);

    if (nrRezultate == 0)
        printf("Nu s-au gasit masini\n");
    else {
        printf("--- REZULTATE ---\n");
        for (int i = 0; i < nrRezultate; i++)
            printf("%d. [%s] | %s | %s | %s\n", i + 1, rezultate[i]->nrInmatriculare, rezultate[i]->model, rezultate[i]->categorie, rezultate[i]->esteInchiriata == 1 ? "INCHIRIATA" : "LIBERA");
    }

    free(rezultate);
}

void uiInchiriaza(Consola* ui) {
    (void)getc(stdin);
    printf("Nr. inmatriculare: ");
    char* nrInmatriculare = citesteStringDinamic();
    int rezultat = inchiriazaMasinaService(ui->service, nrInmatriculare);
    if (rezultat == 0)
        printf("Masina a fost inchiriata\n");
    else if (rezultat == 2)
        printf("Eroare: Masina este deja inchiriata!\n");
    else
        printf("Eroare: Masina nu a fost gasita!\n");

    free(nrInmatriculare);
}

void uiReturneaza(Consola* ui) {
    (void)getc(stdin);
    printf("Nr. inmatriculare: ");
    char* nrInmatriculare = citesteStringDinamic();

    int rezultat = returneazaMasinaService(ui->service, nrInmatriculare);
    if (rezultat == 0)
        printf("Masina a fost returnata cu succes\n");
    else
        printf("Eroare: Masina nu a fost gasita!\n");

    free(nrInmatriculare);
}

void uiGestiuneStare(Consola* ui) {
    printf("\n--- GESTIUNE STARE ---\n");
    printf("1. Inchiriaza masina\n");
    printf("2. Returneaza masina\n");
    printf("Optiune: ");

    int optiune;
    (void)scanf("%d", &optiune);

    if (optiune == 1)
        uiInchiriaza(ui);
    else if (optiune == 2)
        uiReturneaza(ui);
    else
        printf("Optiune invalida!\n");
}

void uiSortare(Consola* ui) {
    printf("Criteriu:\n");
    printf("1. Model\n");
    printf("2. Categorie\n");
    printf("Optiune: ");

    int optiune, revers;
    (void)scanf("%d", &optiune);

    printf("Mod: \n");
    printf("1. Crescator\n");
    printf("2. Descrescator\n");
    (void)scanf("%d", &revers);

    int invers = (revers == 2);

    int nTotal = getLungime(ui->service->repo);
    if (nTotal == 0) {
        printf("Nimic de sortat\n");
        return;
    }

    Masina** rezultate = (Masina**)malloc(nTotal * sizeof(Masina*));
    int numar = 0;

    if (optiune == 1 || optiune == 2) {
        sorteazaMasiniService(ui->service, optiune, invers, rezultate, &numar);
        printf("\n--- LISTA SORTATA ---\n");
        for (int i = 0; i < numar; i++)
            printf("%d. [%s] | Model: %s | Categorie: %s\n", i + 1, rezultate[i]->nrInmatriculare, rezultate[i]->model, rezultate[i]->categorie);
    }
    else
        printf("Optiune invalida!\n");

    free(rezultate);
}

void uiUndo(Consola* ui) {
    int rezultat = undoService(ui->service);
    if (rezultat == 0)
        printf("Undo efectuat cu succes\n");
    else
        printf("Nu mai sunt operatii de anulat!\n");
}

void ruleazaConsola(Consola* ui) {
    int gata = 0;
    int comanda;
    while (!gata) {
        printMeniu();
        if (scanf("%d", &comanda) != 1) {
            while (getchar() != '\n');
            continue;
        }
        switch (comanda) {
        case 1:
            uiAdauga(ui);
            break;
        case 2:
            uiModifica(ui);
            break;
        case 3:
            uiGestiuneStare(ui);
            break;
        case 4:
            uiFiltrare(ui);
            break;
        case 5:
            uiSortare(ui);
            break;
        case 6:
            uiAfisare(ui);
            break;
        case 7:
            uiSterge(ui);
            break;
        case 8:
            uiUndo(ui);
            break;
        case 0:
            gata = 1;
            break;
        default:
            printf("Comanda invalida!\n");
        }
    }
}