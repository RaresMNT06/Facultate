#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "participant.h"

/*
 * Testeaza crearea si distrugerea unui participant.
 * Acopera: creeaza_participant, distruge_participant.
 */
void test_creeaza_distruge() {
    Participant* p = creeaza_participant(12345, "Popescu", "Ion", 50);

    // Verificam daca alocarea a reusit
    assert(p != NULL);
    // Verificam daca datele au fost copiate corect (folosind paranteze ca in cod)
    assert((*p).id == 12345);
    assert(strcmp((*p).nume, "Popescu") == 0);
    assert(strcmp((*p).prenume, "Ion") == 0);
    assert((*p).scor == 50);

    // Distrugem si verificam indirect (prin rulare fara crash)
    distruge_participant(p);

    // Test pentru ramura de siguranta din distruge_participant (if p == NULL)
    distruge_participant(NULL);
}

/*
 * Testeaza toate ramurile de validare.
 * Acopera: validator_participant (toate return 0 si return 1).
 */
void test_validator() {
    // 1. Participant valid (Cazul de succes - return 1)
    Participant* p_ok = creeaza_participant(12345, "Popescu", "Ion", 50);
    assert(validator_participant(p_ok) == 1);

    // 2. ID invalid (sub 10000)
    Participant* p_id_mic = creeaza_participant(9999, "Popescu", "Ion", 50);
    assert(validator_participant(p_id_mic) == 0);

    // 3. ID invalid (peste 99999)
    Participant* p_id_mare = creeaza_participant(100000, "Popescu", "Ion", 50);
    assert(validator_participant(p_id_mare) == 0);

    // 4. Nume gol
    Participant* p_fara_nume = creeaza_participant(12345, "", "Ion", 50);
    assert(validator_participant(p_fara_nume) == 0);

    // 5. Prenume gol
    Participant* p_fara_prenume = creeaza_participant(12345, "Popescu", "", 50);
    assert(validator_participant(p_fara_prenume) == 0);

    // 6. Scor sub 0
    Participant* p_scor_negativ = creeaza_participant(12345, "Popescu", "Ion", -1);
    assert(validator_participant(p_scor_negativ) == 0);

    // 7. Scor peste 100
    Participant* p_scor_mare = creeaza_participant(12345, "Popescu", "Ion", 101);
    assert(validator_participant(p_scor_mare) == 0);

    // 8. Participant NULL
    assert(validator_participant(NULL) == 0);

    // Curatam memoria folosita in teste
    distruge_participant(p_ok);
    distruge_participant(p_id_mic);
    distruge_participant(p_id_mare);
    distruge_participant(p_fara_nume);
    distruge_participant(p_fara_prenume);
    distruge_participant(p_scor_negativ);
    distruge_participant(p_scor_mare);
}

/*
 * Testeaza compararea a doi participanti.
 * Acopera: sunt_identici.
 */
void test_identici() {
    Participant* p1 = creeaza_participant(11111, "A", "B", 10);
    Participant* p2 = creeaza_participant(11111, "X", "Y", 90); // Acelasi ID
    Participant* p3 = creeaza_participant(22222, "A", "B", 10); // ID diferit

    assert(sunt_identici(p1, p2) == 1);
    assert(sunt_identici(p1, p3) == 0);

    distruge_participant(p1);
    distruge_participant(p2);
    distruge_participant(p3);
}

// Functie care le apeleaza pe toate
void test_domain() {
    test_creeaza_distruge();
    test_validator();
    test_identici();
}