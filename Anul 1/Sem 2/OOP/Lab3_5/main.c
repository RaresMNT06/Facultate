#include "repo/repo_participant.h"
#include "service/service_participant.h"
#include "ui/ui.h"


void test_domain();
void test_repo();
void test_service();

int main() {

    test_domain();
    test_repo();
    test_service();

    Repo repo;
    init_repo(&repo);

    Service service;
    init_service(&service, &repo);

    UI ui;
    init_ui(&ui, &service);

    run_ui(&ui);

    distruge_repo(&repo);


    return 0;
}