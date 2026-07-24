#include "repo_participant.h"
#include "service_participant.h"
#include "ui.h"
#include <crtdbg.h>
#include <stdio.h>

void test_domain();
void test_repo();
void test_service();

void populeaza_date(Service* s) {
    // Adăugăm 5 participanți cu date diferite pentru a testa sortările/filtrările
    adauga_participant_service(s, 10001, "Munteanu", "Rares", 95);
    adauga_participant_service(s, 22222, "Mocanu", "Edy", 88);
    adauga_participant_service(s, 33333, "Leah", "Rares", 45);
    adauga_participant_service(s, 44444, "Nicuta", "Ioana", 100);
    adauga_participant_service(s, 55555, "Gherasim", "Stefan", 12);
}


int main() {
   
    
    test_domain();
    test_repo();
    test_service();
    
    Repo repo;
    init_repo(&repo);

    Service service;
    init_service(&service, &repo);
    populeaza_date(&service);

    UI ui;
    init_ui(&ui, &service);

    run_ui(&ui);

    distruge_repo(&repo);

    if (_CrtDumpMemoryLeaks() != 0)
        printf("!!!Avem memory leak!!!");
    

    return 0;
}