#include "participant.h"
#include <stdlib.h>
#include <string.h>

/*
 * Creeaza un nou participant pe heap si aloca memorie pentru nume/prenume.
 * @param id: int (5 cifre)
 * @param nume, prenume: siruri de caractere
 * @param scor: int (0-100)
 * @return: pointer catre structura Participant creata sau NULL daca alocarea esueaza.
 */
Participant* creeaza_participant(int id, char* nume, char* prenume, int scor) {
    Participant* p = (Participant*)malloc(sizeof(Participant));
    if (p == NULL) return NULL;

    (*p).id = id;
    (*p).scor = scor;

    (*p).nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
    if ((*p).nume != NULL) strcpy((*p).nume, nume);

    (*p).prenume = (char*)malloc((strlen(prenume) + 1) * sizeof(char));
    if ((*p).prenume != NULL) strcpy((*p).prenume, prenume);

    return p;
}

/*
 * Valideaza datele unui participant conform regulilor de business.
 * @param p: pointer catre participantul de validat
 * @return: 1 daca participantul este valid, 0 altfel.
 */
int validator_participant(Participant* p) {
    if (p == NULL)
        return 0;
    if ((*p).id < 10000 || (*p).id > 99999)
        return 0;
    if (strlen((*p).nume) == 0 || strlen((*p).prenume) == 0)
        return 0;
    if ((*p).scor < 0 || (*p).scor > 100)
        return 0;
    return 1;
}

/*
 * Verifica daca doi participanti au acelasi ID.
 * @param p1, p2: pointeri catre participantii comparati
 * @return: 1 daca au acelasi ID, 0 altfel.
 */
int sunt_identici(Participant* p1, Participant* p2) {
    if ((*p1).id == (*p2).id)
        return 1;
    return 0;
}

/*
 * Elibereaza toata memoria ocupata de un participant (nume, prenume si structura).
 * @param p: pointer catre participantul ce trebuie distrus.
 */
void distruge_participant(Participant* p) {
    if (p == NULL) return;
    free((*p).nume);
    free((*p).prenume);
    free(p);
}