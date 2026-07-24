#include "teste.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <cassert>
#include <fstream>

/* Testeaza constructorul si getterii clasei Film */
void testFilm() {
    Film f("001", "aaaa", "abcd", "actiune");
    assert(f.getCod() == "001");
    assert(f.getTitlu() == "aaaa");
    assert(f.getAutor() == "abcd");
    assert(f.getGen() == "actiune");
}

/* Testeaza citirea din fisier si stocarea in vector */
void testRepository() {
    std::ofstream f("test_temp.txt");
    f << "001,aaaa,abcd,actiune\n";
    f << "002,bbbb,efgh,drama\n";
    f.close();

    Repository repo("test_temp.txt");
    assert(repo.size() == 2);
    assert(repo.getAll()[0].getTitlu() == "aaaa");
    assert(repo.getAll()[1].getGen() == "drama");
}

/* Testeaza filtrarea dupa gen si sortarea dupa titlu */
void testService() {
    std::ofstream f("test_temp.txt");
    f << "001,aaaa,abcd,actiune\n";
    f << "002,bbbb,efgh,drama\n";
    f << "005,eeee,aasd,actiune\n";
    f.close();

    Repository repo("test_temp.txt");
    Service srv(repo);

    // test filtrare dupa gen
    auto filtrate = srv.filtreazaDupaGen("actiune");
    assert(filtrate.size() == 2);

    // test sortare dupa titlu
    auto sortate = srv.sorteazaDupaTitlu();
    assert(sortate[0].getTitlu() == "aaaa");
    assert(sortate[1].getTitlu() == "bbbb");
    assert(sortate[2].getTitlu() == "eeee");
}

/* Ruleaza toate testele */
void runAllTests() {
    testFilm();
    testRepository();
    testService();
}