#ifndef SERVICE_H
#define SERVICE_H

#include "../repo/repo_participant.h"

typedef struct {
    Repo* repo;
} Service;

/* Initializeaza service-ul prin legarea la repo.
   @param service: pointer service, repo: pointer repo */
void init_service(Service* service, Repo* repo);

/* Creeaza, valideaza si adauga un participant in sistem.
   @param id: int (5 cifre), nume, prenume: siruri, scor: int
   @return: 1 succes, 0 eroare (validare esuata sau ID duplicat) */
int adauga_participant_service(Service* service, int id, char* nume, char* prenume, int scor);

/* Modifica scorul unui participant existent identificat prin ID.
   @param id: ID-ul cautat, scor_nou: noua valoare
   @return: 1 succes, 0 negasit */
int actualizeaza_participant_service(Service* service, int id, int scor_nou);

/* Elimina un participant din lista dupa ID.
   @param id: ID-ul participantului de sters
   @return: 1 succes, 0 negasit */
int stergere_participant_service(Service* service, int id);

/* Filtreaza lista returnand un Repo temporar cu elemente cu scor < prag.
   @param param: pragul de scor
   @return: structura Repo ce contine pointeri catre participanti */
Repo filtrare_scor_service(Service* service, int param);

/* Sorteaza lista de participanti (direct in repo) dupa nume sau scor.
   @param tip_sortare: 1-nume, 2-scor
   @param cres_desc: 0-crescator, 1-descrescator */
void sorteaza_partcipanti_service(Service* service, int tip_sortare, int cres_desc);

#endif