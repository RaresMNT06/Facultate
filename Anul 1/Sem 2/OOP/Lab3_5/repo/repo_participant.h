#ifndef REPO_H
#define REPO_H
#include "../domain/participant.h"

typedef struct {
    Participant** participanti; // Vector dinamic de pointeri catre Participanti
    int lungime;                // Numarul curent de elemente
    int capacitate;             // Capacitatea maxima alocata
} Repo;

/* Init repo: lungime = 0, aloca memorie initiala */
void init_repo(Repo* r);

/* Adauga p in r (cu resize daca e plin). Ret: 1 (succes), 0 (eroare)
   @param p: pointer catre participantul creat in Service */
int adauga_repo(Repo* r, Participant* p);

/* Modifica scor pt un ID de 5 cifre. Ret: 1 (succes), 0 (negasit) */
int actualizeaza_repo(Repo* r, int id, int scor_nou);

/* Sterge participantul dupa ID. Ret: 1 (succes), 0 (negasit) */
int sterge_repo(Repo* r, int id);

/* Elibereaza toata memoria din repo (participanti + vector) */
void distruge_repo(Repo* r);

/* Ret: Pointer la Participantul de la index */
Participant* get_participant_la_index(Repo* r, int index);

#endif