#include <assert.h>
#include <stdlib.h>
#include "repo_participant.h"

/* Testeaza init si distruge */
/* @param: - ; @return: - */
void sub_test_init_distruge() {
    Repo r;
    init_repo(&r);
    assert(r.lungime == 0);
    assert(r.capacitate == 2);
    assert(r.participanti != NULL);

    distruge_repo(&r);
    assert(r.lungime == 0);

    // Test siguranta NULL
    distruge_repo(NULL);
}

/* Testeaza adaugare, resize si cazul NULL */
/* @param: - ; @return: - */
void sub_test_adauga_resize() {
    Repo r;
    init_repo(&r);

    // 1. Testam adaugare NULL pentru 100% coverage pe ramura de eroare
    assert(adauga_repo(&r, NULL) == 0);

    // 2. Adaugam normal pana la resize
    Participant* p1 = creeaza_participant(10001, "A", "A", 50);
    Participant* p2 = creeaza_participant(10002, "B", "B", 70);
    Participant* p3 = creeaza_participant(10003, "C", "C", 90);

    assert(adauga_repo(&r, p1) == 1);
    assert(adauga_repo(&r, p2) == 1);

    // Fortam resize (realloc)
    assert(adauga_repo(&r, p3) == 1);
    assert(r.lungime == 3);
    assert(r.capacitate == 4);

    distruge_repo(&r);
}

/* Testeaza stergere si shiftare */
/* @param: - ; @return: - */
void sub_test_sterge() {
    Repo r;
    init_repo(&r);
    Participant* p1 = creeaza_participant(111, "X", "X", 10);
    Participant* p2 = creeaza_participant(222, "Y", "Y", 20);
    adauga_repo(&r, p1);
    adauga_repo(&r, p2);

    // Stergere succes (face si shiftarea pointerilor)
    assert(sterge_repo(&r, 111) == 1);
    assert(r.lungime == 1);
    assert((*r.participanti[0]).id == 222);

    // Stergere esuata
    assert(sterge_repo(&r, 999) == 0);

    distruge_repo(&r);
}

/* Testeaza actualizare */
/* @param: - ; @return: - */
void sub_test_actualizeaza() {
    Repo r;
    init_repo(&r);
    Participant* p = creeaza_participant(100, "A", "B", 10);
    adauga_repo(&r, p);

    assert(actualizeaza_repo(&r, 100, 50) == 1);
    assert((*r.participanti[0]).scor == 50);

    // Actualizare esuata
    assert(actualizeaza_repo(&r, 200, 50) == 0);

    distruge_repo(&r);
}

/* Testeaza acces index si limite */
/* @param: - ; @return: - */
void sub_test_get_index() {
    Repo r;
    init_repo(&r);
    Participant* p = creeaza_participant(10, "X", "Y", 50);
    adauga_repo(&r, p);

    assert(get_participant_la_index(&r, 0) != NULL);
    assert(get_participant_la_index(&r, -1) == NULL);
    assert(get_participant_la_index(&r, 5) == NULL);

    distruge_repo(&r);
}

/* Functia principala de test Repo */
/* @param: - ; @return: - */
void test_repo() {
    sub_test_init_distruge();
    sub_test_adauga_resize();
    sub_test_sterge();
    sub_test_actualizeaza();
    sub_test_get_index();
}