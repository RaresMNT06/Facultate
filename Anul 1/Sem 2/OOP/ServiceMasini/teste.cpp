#include "teste.h"
#include "vehicul.h"
#include "repo_masini.h"
#include "service_masini.h"
#include <cassert>
#include <fstream>

void testVehicul() {
    Vehicul v("CJ01ABC", "Toyota", "sedan", 6);
    assert(v.getNrInmatriculare() == "CJ01ABC");
    assert(v.getMarca() == "Toyota");
    assert(v.getTip() == "sedan");
    assert(v.getVarsta() == 6);
}

void testRepository() {
    std::ofstream f("test_temp.txt");
    f << "CJ01ABC,Toyota,sedan,6\n";
    f << "CJ02DEF,Ford,SUV,13\n";
    f.close();

    Repository repo("test_temp.txt");
    assert(repo.size() == 2);
    assert(repo.getAll()[0].getNrInmatriculare() == "CJ01ABC");
    assert(repo.getAll()[1].getMarca() == "Ford");
}

void testService() {
    std::ofstream f("test_temp.txt");
    f << "CJ01ABC,Toyota,sedan,6\n";
    f << "CJ02DEF,Ford,SUV,13\n";
    f << "CJ03GHI,BMW,sedan,3\n";
    f.close();

    Repository repo("test_temp.txt");
    Service srv(repo);

    auto filtrate = srv.filtreazaDupaTip("sedan");
    assert(filtrate.size() == 2);

    auto sortate = srv.sorteazaDupaVarsta();
    assert(sortate[0].getVarsta() == 3);
    assert(sortate[1].getVarsta() == 6);
    assert(sortate[2].getVarsta() == 13);
}

void runAllTests() {
    testVehicul();
    testRepository();
    testService();
}
