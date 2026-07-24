#include "service_participant.h"
#include "mysort.h" // Adaugat pentru a folosi sortarea generica
#include <string.h>

/* Initializeaza service-ul prin legarea la un repository */
/* @param s: pointer service, r: pointer repo */
/* @return: - */
void init_service(Service* s, Repo* r) {
    (*s).repo = r;
}

/* Creeaza un participant, il valideaza si il adauga in repo */
/* @param s: service, id: int, nume/prenume: siruri, scor: int */
/* @return: 1 daca a fost adaugat, 0 daca e invalid sau duplicat */
int adauga_participant_service(Service* s, int id, char* nume, char* prenume, int scor) {
    // Cream participantul dinamic (Saptamana 2)
    Participant* p = creeaza_participant(id, nume, prenume, scor);

    // Validare
    if (validator_participant(p) == 0) {
        distruge_participant(p); // Eliberam memoria daca e invalid
        return 0;
    }

    // Verificare duplicat dupa ID
    Repo* r = (*s).repo;
    for (int i = 0; i < (*r).lungime; i++) {
        Participant* existent = get_participant_la_index(r, i);
        if ((*existent).id == id) {
            distruge_participant(p); // Eliberam memoria daca exista deja
            return 0;
        }
    }

    // Adaugare in repo
    return adauga_repo((*s).repo, p);
}

/* Valideaza noul scor si actualizeaza datele unui participant existent prin ID */
/* @param s: service, id: int, scor_nou: int */
/* @return: 1 pentru succes, 0 pentru scor invalid sau participant negasit */
int actualizeaza_participant_service(Service* s, int id, int scor_nou) {
    if (scor_nou < 0 || scor_nou > 100) return 0;
    return actualizeaza_repo((*s).repo, id, scor_nou);
}

/* Sterge un participant din sistem pe baza ID-ului */
/* @param s: service, id: int */
/* @return: 1 daca a fost sters, 0 daca nu a fost gasit */
int stergere_participant_service(Service* s, int id) {
    return sterge_repo((*s).repo, id);
}

/* Filtreaza lista returnand doar participantii cu scor mai mic decat pragul */
/* @param s: service, param: pragul de scor (int) */
/* @return: O structura Repo (copie) continand pointeri catre elementele filtrate */
Repo filtrare_scor_service(Service* s, int param) {
    Repo rezultat;
    init_repo(&rezultat);
    Repo* r_original = (*s).repo;

    for (int i = 0; i < (*r_original).lungime; i++) {
        Participant* p = get_participant_la_index(r_original, i);
        if ((*p).scor < param) {
            // Cream o copie a participantului pentru lista filtrata
            // Astfel UI-ul poate da distruge_repo fara sa afecteze lista principala
            Participant* p_copie = creeaza_participant((*p).id, (*p).nume, (*p).prenume, (*p).scor);
            adauga_repo(&rezultat, p_copie);
        }
    }
    return rezultat;
}

/* --- FUNCTIA VECHE COMENTATA --- */
/*
void sorteaza_partcipanti_service(Service* s, int tip_sortare, int cres_desc) {
    Repo* r = (*s).repo;
    int n = (*r).lungime;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int trebuie_schimbat = 0;
            Participant* p1 = (*r).participanti[i];
            Participant* p2 = (*r).participanti[j];

            if (tip_sortare == 1) { // Sortare dupa NUME
                int comp = strcmp((*p1).nume, (*p2).nume);
                if (cres_desc == 0) { // Crescator
                    if (comp > 0) trebuie_schimbat = 1;
                }
                else { // Descrescator
                    if (comp < 0) trebuie_schimbat = 1;
                }
            }
            else { // Sortare dupa SCOR
                if (cres_desc == 0) { // Crescator
                    if ((*p1).scor > (*p2).scor) trebuie_schimbat = 1;
                }
                else { // Descrescator
                    if ((*p1).scor < (*p2).scor) trebuie_schimbat = 1;
                }
            }

            if (trebuie_schimbat) {
                // Interschimbam doar adresele pointerilor
                Participant* aux = (*r).participanti[i];
                (*r).participanti[i] = (*r).participanti[j];
                (*r).participanti[j] = aux;
            }
        }
    }
}
*/



int cmp_nume_cresc(Participant* p1, Participant* p2) {
    return strcmp(p1->nume, p2->nume);
}

int cmp_nume_desc(Participant* p1, Participant* p2) {
    return strcmp(p2->nume, p1->nume);
}

int cmp_scor_cresc(Participant* p1, Participant* p2) {
    return p1->scor - p2->scor;
}

int cmp_scor_desc(Participant* p1, Participant* p2) {
    return p2->scor - p1->scor;
}

/* Sorteaza lista de participanti in functie de criteriu si ordine utilizand sortarea generica */
/* @param s: service, tip_sortare: 1-nume/2-scor, cres_desc: 0-cresc/1-desc */
/* @return: - (sortarea se face direct pe datele din repo) */
void sorteaza_partcipanti_service(Service* s, int tip_sortare, int cres_desc) {
    Repo* r = (*s).repo;

    if (tip_sortare == 1) { // Sortare dupa NUME
        if (cres_desc == 0) sortare_generica((*r).participanti, (*r).lungime, cmp_nume_cresc);
        else sortare_generica((*r).participanti, (*r).lungime, cmp_nume_desc);
    }
    else { // Sortare dupa SCOR
        if (cres_desc == 0) sortare_generica((*r).participanti, (*r).lungime, cmp_scor_cresc);
        else sortare_generica((*r).participanti, (*r).lungime, cmp_scor_desc);
    }
}