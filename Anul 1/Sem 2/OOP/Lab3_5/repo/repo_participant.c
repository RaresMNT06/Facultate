#include "repo_participant.h"
#include <stdlib.h>


/* Initializeaza repository-ul alocand dinamic spatiu pentru vectorul de pointeri.
   @param r: pointer catre structura Repo */
void init_repo(Repo *r) {
    (*r).lungime = 0;
    (*r).capacitate = 2; // Incepem cu o capacitate mica pentru a testa resize-ul
    (*r).participanti = (Participant **) malloc((*r).capacitate * sizeof(Participant *));
}

/* Adauga un participant in vectorul dinamic. Redimensioneaza daca este plin.
   @param r: pointer repo, p: pointer catre participantul de adaugat
   @return: 1 daca s-a reusit, 0 daca alocarea a esuat */
int adauga_repo(Repo *r, Participant *p) {
    if (p == NULL) {
        return 0;
    }
    if ((*r).lungime == (*r).capacitate) {
        int noua_capacitate = (*r).capacitate * 2;
        Participant **noi_participanti = (Participant **) realloc((*r).participanti,
                                                                  noua_capacitate * sizeof(Participant *));
        if (noi_participanti != NULL) {
            (*r).participanti = noi_participanti;
            (*r).capacitate = noua_capacitate;
        }
    }

    (*r).participanti[(*r).lungime] = p;
    (*r).lungime++;
    return 1;
}

/* Cauta si sterge un participant dupa ID-ul sau unic.
   @param r: pointer repo, id: ID-ul de 5 cifre cautat
   @return: 1 daca a fost sters, 0 daca nu a fost gasit */
int sterge_repo(Repo *r, int id) {
    int index_delete = -1;
    for (int i = 0; i < (*r).lungime; i++) {
        // Accesam ID-ul folosind paranteze: dereferentiem pointerul din vector
        if ((*(*r).participanti[i]).id == id) {
            index_delete = i;
            break;
        }
    }

    if (index_delete == -1) return 0;

    // Distrugem obiectul pentru a elibera memoria (nume, prenume, structura)
    distruge_participant((*r).participanti[index_delete]);

    // Shiftam pointerii la stanga pentru a ocupa golul
    for (int i = index_delete; i < (*r).lungime - 1; i++) {
        (*r).participanti[i] = (*r).participanti[i + 1];
    }
    (*r).lungime--;
    return 1;
}

/* Modifica scorul unui participant identificat prin ID.
   @param r: pointer repo, id: ID cautat, scor_nou: noua valoare
   @return: 1 pentru succes, 0 daca participantul nu exista */
int actualizeaza_repo(Repo *r, int id, int scor_nou) {
    for (int i = 0; i < (*r).lungime; i++) {
        if ((*(*r).participanti[i]).id == id) {
            (*(*r).participanti[i]).scor = scor_nou;
            return 1;
        }
    }
    return 0;
}

/* Elibereaza toata memoria ocupata de participanti si de vectorul de pointeri.
   @param r: pointer catre structura Repo */
void distruge_repo(Repo *r) {
    if (r == NULL) return;
    for (int i = 0; i < (*r).lungime; i++) {
        distruge_participant((*r).participanti[i]);
    }
    free((*r).participanti);
    (*r).participanti = NULL;
    (*r).lungime = 0;
    (*r).capacitate = 0;
}

/* Returneaza participantul de la o pozitie specifica din vector.
   @param r: pointer repo, index: pozitia dorita
   @return: pointer la Participant sau NULL daca indexul e invalid */
Participant *get_participant_la_index(Repo *r, int index) {
    if (index < 0 || index >= (*r).lungime) return NULL;
    return (*r).participanti[index];
}
