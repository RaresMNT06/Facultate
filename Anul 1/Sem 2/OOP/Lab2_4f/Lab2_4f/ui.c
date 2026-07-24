#include "ui.h"
#include <stdio.h>


void init_ui(UI* ui, Service* s) {
    (*ui).service = s;
}

/* Afiseaza elementele din orice structura de tip Repo */
/* @param: r (Repo) */
/* @return: - */
void afisare_lista(Repo r) {
    if (r.lungime == 0) {
        printf("Lista este goala.\n");
        return;
    }
    for (int i = 0; i < r.lungime; i++) {
        // r.participanti[i] este acum un pointer catre Participant
        Participant* p = r.participanti[i];
        printf("%d. [ID: %d] %s %s | Scor: %d\n", i + 1, (*p).id, (*p).nume, (*p).prenume, (*p).scor);
    }
}

/* Citeste datele si apeleaza service-ul pentru adaugare */
/* @param: ui (UI) */
/* @return: - */
void ui_adauga(UI* ui) {
    char nume[50], prenume[50];
    int id, scor;
    printf("ID (5 cifre): "); scanf_s("%d", &id);
    printf("Nume: "); scanf("%s", nume);
    printf("Prenume: "); scanf("%s", prenume);
    printf("Scor: "); scanf_s("%d", &scor);

    if (adauga_participant_service((*ui).service, id, nume, prenume, scor)) {
        printf("Participant adaugat cu succes!\n");
    }
    else {
        printf("Date invalide sau lista plina sau acelasi patiipant!\n");
    }
}

/* Modifica scorul unui participant existent */
/* @param: ui (UI) */
/* @return: - */
void ui_actualizeaza(UI* ui) {
    int id, scor_nou;
    printf("ID participant: "); scanf_s("%d", &id);
    printf("Scor nou: "); scanf_s("%d", &scor_nou);

    if (actualizeaza_participant_service((*ui).service, id, scor_nou)) {
        printf("Actualizare reusita!\n");
    }
    else {
        printf("Participant negasit sau scor invalid!\n");
    }
}

/* Sterge un participant din lista */
/* @param: ui (UI) */
/* @return: - */
void ui_sterge(UI* ui) {
    int id;
    printf("ID participant de sters: "); scanf_s("%d", &id);

    if (stergere_participant_service((*ui).service, id)) {
        printf("Participant eliminat!\n");
    }
    else {
        printf("Participantul nu a fost gasit!\n");
    }
}

/* Citeste criteriile si sorteaza lista originala */
/* @param: ui (UI) */
/* @return: - */
void ui_sorteaza(UI* ui) {
    int tip, ordine;
    printf("Criteriu (1. Nume, 2. Scor): "); scanf_s("%d", &tip);
    printf("Ordine (0. Crescator, 1. Descrescator): "); scanf_s("%d", &ordine);

    sorteaza_partcipanti_service((*ui).service, tip, ordine);
    printf("Lista a fost sortata.\n");
    afisare_lista(*((*(*ui).service).repo));
}

/* Filtreaza lista dupa scorul minim */
/* @param: ui (UI) */
/* @return: - */
void ui_filtrare(UI* ui) {
    int prag;
    printf("Afiseaza participantii cu scor mai mic decat: ");
    scanf_s("%d", &prag);

    // Generam lista filtrata
    Repo filtrat = filtrare_scor_service((*ui).service, prag);
    afisare_lista(filtrat);

    // OBLIGATORIU pentru Saptamana 2: curatam copia temporara din memorie
    distruge_repo(&filtrat);
}

void run_ui(UI* ui) {
    int ruleaza = 1;
    int comanda;
    while (ruleaza) {
        printf("\n--- MENIU ---\n");
        printf("1. Adauga participant\n");
        printf("2. Afiseaza toti\n");
        printf("3. Filtrare scor\n");
        printf("4. Actualizeaza scor\n");
        printf("5. Sterge participant\n");
        printf("6. Sorteaza lista\n");
        printf("0. Iesire\n");
        printf("Comanda: ");

        if (scanf_s("%d", &comanda) != 1) {
            printf("Comanda invalida!\n");
            continue;
        }

        switch (comanda) {
        case 1: ui_adauga(ui); break;
        case 2: afisare_lista(*((*(*ui).service).repo)); break;
        case 3: ui_filtrare(ui); break;
        case 4: ui_actualizeaza(ui); break;
        case 5: ui_sterge(ui); break;
        case 6: ui_sorteaza(ui); break;
        case 0: ruleaza = 0; break;
        default: printf("Comanda invalida!\n");
        }
    }
}