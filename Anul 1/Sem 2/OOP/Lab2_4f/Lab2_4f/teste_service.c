#include <assert.h>
#include <string.h>
#include "service_participant.h"

/* Testeaza adaugarea: succes, ID duplicat si validare esuata */
void sub_test_adauga_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s, &r);

    // 1. Succes
    assert(adauga_participant_service(&s, 10001, "Pop", "Ion", 50) == 1);
    assert(r.lungime == 1);

    // 2. ID Duplicat (acopera ramura return 0 din bucla de verificare duplicat)
    assert(adauga_participant_service(&s, 10001, "Alt", "Nume", 20) == 0);
    assert(r.lungime == 1);

    // 3. Validare esuata (ID prea mic - acopera ramura distruge_participant si return 0)
    assert(adauga_participant_service(&s, 99, "A", "B", 10) == 0);

    // 4. Validare esuata scor (pentru 100% coverage pe validator)
    assert(adauga_participant_service(&s, 10002, "A", "B", -1) == 0);

    distruge_repo(&r);
}

/* Testeaza actualizarea si stergerea din service */
void sub_test_modifica_sterge_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s, &r);

    adauga_participant_service(&s, 10001, "A", "B", 50);

    // Actualizare scor succes
    assert(actualizeaza_participant_service(&s, 10001, 80) == 1);

    // Actualizare scor invalid peste 100 (acopera if-ul din service)
    assert(actualizeaza_participant_service(&s, 10001, 150) == 0);

    // Actualizare scor invalid sub 0 (acopera cealalta parte a if-ului)
    assert(actualizeaza_participant_service(&s, 10001, -10) == 0);

    // Stergere succes
    assert(stergere_participant_service(&s, 10001) == 1);
    assert(r.lungime == 0);

    // Stergere ID inexistent (acopera ramura return 0 din repo apelata prin service)
    assert(stergere_participant_service(&s, 10001) == 0);

    distruge_repo(&r);
}

/* Testeaza sortarea dupa nume si scor (toate combinatiile) */
void sub_test_sortare_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s, &r);

    adauga_participant_service(&s, 10001, "B", "Ion", 90);
    adauga_participant_service(&s, 10002, "A", "Dan", 10);

    // 1. Sortare dupa NUME CRESCATOR (A, B)
    sorteaza_partcipanti_service(&s, 1, 0);
    assert(strcmp((*r.participanti[0]).nume, "A") == 0);

    // 2. Sortare dupa NUME DESCRESCATOR (B, A) -> ASTA LIPSEA
    sorteaza_partcipanti_service(&s, 1, 1);
    assert(strcmp((*r.participanti[0]).nume, "B") == 0);

    // 3. Sortare dupa SCOR CRESCATOR (10, 90)
    sorteaza_partcipanti_service(&s, 2, 0);
    assert((*r.participanti[0]).scor == 10);

    // 4. Sortare dupa SCOR DESCRESCATOR (90, 10)
    sorteaza_partcipanti_service(&s, 2, 1);
    assert((*r.participanti[0]).scor == 90);

    distruge_repo(&r);
}

/* Testeaza filtrarea scorului */
void sub_test_filtrare_service() {
    Repo r;
    init_repo(&r);
    Service s;
    init_service(&s, &r);

    adauga_participant_service(&s, 10001, "A", "B", 10);
    adauga_participant_service(&s, 10002, "C", "D", 80);

    // Filtram participantii cu scor < 50
    Repo f = filtrare_scor_service(&s, 50);
    assert(f.lungime == 1);
    assert((*f.participanti[0]).id == 10001);

    distruge_repo(&f);
    distruge_repo(&r);
}

/* --- FUNCTIA PE CARE O CHEMI IN MAIN.C --- */
void test_service() {
    sub_test_adauga_service();
    sub_test_modifica_sterge_service();
    sub_test_sortare_service();
    sub_test_filtrare_service();
}