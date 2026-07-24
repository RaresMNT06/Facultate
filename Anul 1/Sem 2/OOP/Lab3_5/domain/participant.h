#ifndef PARTICIPANT_H
#define PARTICIPANT_H

typedef struct {
    int id;         // ID-ul de 5 cifre
    char* nume;     // Dinamic (alocat cu malloc)
    char* prenume;  // Dinamic (alocat cu malloc)
    int scor;       // Intre 0 si 100
} Participant;

/* Constructor: creeaza un participant pe Heap */
Participant* creeaza_participant(int id, char* nume, char* prenume, int scor);

/* Destructor: elibereaza toata memoria unui participant */
void distruge_participant(Participant* p);

/* Validare: verifica regulile de business (ID 5 cifre, nume existent, scor 0-100) */
int validator_participant(Participant* p);

/* Identitate: compara daca doi participanti sunt aceeasi persoana (dupa ID) */
int sunt_identici(Participant* p1, Participant* p2);

#endif