#include "teste.h"
#include "Entitate.h"
#include "Repository.h"
#include "Service.h"
#include <cassert>
#include <fstream>

void testEntitate() {
    Entitate e("ID001");
    assert(e.getId() == "ID001");
    // TODO: adauga teste pentru celelalte campuri
}

void testRepository() {
    std::ofstream f("test_temp.txt");
    f << "ID001\n";
    f << "ID002\n";
    f.close();

    Repository repo("test_temp.txt");
    assert(repo.size() == 2);
    assert(repo.getAll()[0].getId() == "ID001");
}

void testService() {
    std::ofstream f("test_temp.txt");
    f << "ID001\n";
    f << "ID002\n";
    f.close();

    Repository repo("test_temp.txt");
    Service srv(repo);
    assert(srv.getAll().size() == 2);
    // TODO: adauga teste pentru filtrare/sortare
}

void runAllTests() {
    testEntitate();
    testRepository();
    testService();
}
