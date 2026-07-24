#ifndef TESTE_H
#define TESTE_H 

#include "Domain/Masina.h"
#include "Repository/MyRepo.h"
#include "MyList.h"
#include "Service/MasinaService.h"
#include <assert.h> 
#include <string.h>
#include <stdio.h>

extern int FORTEAZA_EROARE_MALLOC1;
extern int FORTEAZA_EROARE_MALLOC2;
extern int FORTEAZA_EROARE_MALLOC_LIST;
extern int FORTEAZA_EROARE_MALLOC_REPO;

void ruleazaToateTestele();

void testCoverageComplet() {
    // creeazaMasina -- ramurile de eroare malloc
    FORTEAZA_EROARE_MALLOC1 = 1;
    assert(creeazaMasina("CJ 01 ABC", "Dacia", "SUV") == NULL);
    FORTEAZA_EROARE_MALLOC1 = 2;
    assert(creeazaMasina("CJ 01 ABC", "Dacia", "SUV") == NULL);
    FORTEAZA_EROARE_MALLOC1 = 0;

    // creeazaLista -- ramurile de eroare malloc
    FORTEAZA_EROARE_MALLOC_LIST = 1;
    assert(creeazaLista() == NULL);
    FORTEAZA_EROARE_MALLOC_LIST = 2;
    assert(creeazaLista() == NULL);
    FORTEAZA_EROARE_MALLOC_LIST = 3;
    assert(creeazaLista() == NULL);
    FORTEAZA_EROARE_MALLOC_LIST = 0;

    // creeazaRepo -- ramurile de eroare malloc
    FORTEAZA_EROARE_MALLOC_REPO = 1;
    assert(creeazaRepo() == NULL);
    FORTEAZA_EROARE_MALLOC_REPO = 2;
    assert(creeazaRepo() == NULL);
    FORTEAZA_EROARE_MALLOC_REPO = 3;
    assert(creeazaRepo() == NULL);
    FORTEAZA_EROARE_MALLOC_REPO = 0;
}

void testList() {
    // creeazaLista, getLungimeLista -- lista goala
    MyList* list = creeazaLista();
    assert(getLungimeLista(list) == 0);

    Masina* m1 = creeazaMasina("CJ 01 ABC", "Dacia", "SUV");
    Masina* m2 = creeazaMasina("B 12 ABC", "Audi", "Sedan");
    Masina* m3 = creeazaMasina("IS 99 POS", "BMW", "Sport");

    // adaugaElement, getLungimeLista, getElement -- adaugare si accesare elemente
    adaugaElement(list, m1);
    adaugaElement(list, m2);
    adaugaElement(list, m3);
    assert(getLungimeLista(list) == 3);
    assert(getElement(list, 0) == m1);

    // setElement -- modificare element la pozitie
    Masina* m4 = creeazaMasina("CJ 77 WOO", "Skoda", "Berlina");
    setElement(list, 0, m4);
    assert(getElement(list, 0) == m4);
    setElement(list, 0, m1);
    distrugeMasina(m4);

    // copiazaLista -- copie profunda independenta
    MyList* copie = copiazaLista(list, (CopyFunc)copiazaMasina);
    assert(getLungimeLista(copie) == 3);
    assert(getElement(copie, 0) != getElement(list, 0)); // pointeri diferiti
    assert(strcmp(((Masina*)getElement(copie, 0))->model, "Dacia") == 0);
    distrugeLista(copie, (DestroyFunc)distrugeMasina);

    // copiazaLista -- cazul NULL
    assert(copiazaLista(NULL, (CopyFunc)copiazaMasina) == NULL);

    // stergeElement -- stergere la mijloc, elementele se shifteaza corect
    assert(stergeElement(list, 1, (DestroyFunc)distrugeMasina) == 0);
    assert(getLungimeLista(list) == 2);
    assert(strcmp(((Masina*)getElement(list, 1))->model, "BMW") == 0);

    // stergeElement -- pozitie invalida returneaza eroare
    assert(stergeElement(list, 99, (DestroyFunc)distrugeMasina) == 1);

    // stergeElement -- fara destroy (NULL), elementul nu e eliberat de lista
    assert(stergeElement(list, 0, NULL) == 0);
    distrugeMasina(m1);

    // distrugeLista -- cu destroy si cazul NULL
    distrugeLista(list, (DestroyFunc)distrugeMasina);
    distrugeLista(NULL, NULL);
}

void testDomain() {
    // creeazaMasina -- campurile sunt initializate corect
    Masina* m = creeazaMasina("CJ 01 ABC", "Dacia", "SUV");
    assert(strcmp(m->nrInmatriculare, "CJ 01 ABC") == 0);
    assert(strcmp(m->model, "Dacia") == 0);
    assert(strcmp(m->categorie, "SUV") == 0);
    assert(m->esteInchiriata == 0);

    // copiazaMasina -- copia are aceleasi date ca originalul
    Masina* m2 = copiazaMasina(m);
    assert(strcmp(m2->nrInmatriculare, "CJ 01 ABC") == 0);
    assert(strcmp(m2->model, "Dacia") == 0);
    assert(strcmp(m2->categorie, "SUV") == 0);
    assert(m2->esteInchiriata == 0);

    // copiazaMasina -- cazul NULL
    assert(copiazaMasina(NULL) == NULL);

    // distrugeMasina -- inclusiv cazul NULL (ramura de safety)
    distrugeMasina(m);
    distrugeMasina(m2);
    distrugeMasina(NULL);
}

void testRepo() {
    // creeazaRepo, getLungime -- repo gol
    MyRepo* repo = creeazaRepo();
    assert(getLungime(repo) == 0);

    Masina* m1 = creeazaMasina("CJ 01 ABC", "Dacia", "SUV");
    Masina* m2 = creeazaMasina("B 12 ABC", "Audi", "Sedan");
    Masina* m3 = creeazaMasina("IS 99 POS", "BMW", "Sport");

    // adaugaMasinaRepo, getLungime -- adaugare si numarare corecta
    adaugaMasinaRepo(repo, m1);
    adaugaMasinaRepo(repo, m2);
    adaugaMasinaRepo(repo, m3);
    assert(getLungime(repo) == 3);

    // modificaMasinaRepo -- masina existenta se modifica corect
    Masina* mNou = creeazaMasina("CJ 01 ABC", "Logan", "Berlina");
    int rez = modificaMasinaRepo(repo, mNou);
    assert(rez == 0);
    assert(strcmp(getMasina(repo, 0)->model, "Logan") == 0);

    // modificaMasinaRepo -- masina inexistenta returneaza eroare
    Masina* mInexistent = creeazaMasina("CJ 99 ZZZ", "Test", "Test");
    assert(modificaMasinaRepo(repo, mInexistent) == 1);

    // setStareInchiriereRepo -- succes si cazul masinii inexistente
    assert(setStareInchiriereRepo(repo, "CJ 01 ABC", 1) == 0);
    assert(getMasina(repo, 0)->esteInchiriata == 1);
    assert(setStareInchiriereRepo(repo, "XX 00 XXX", 1) == 1);

    distrugeMasina(mInexistent);
    distrugeMasina(mNou);
    distrugeRepo(repo);
}

void testSterge() {
    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "SUV");
    adaugaMasinaService(service, "B 12 ABC", "Audi", "Sedan");

    // stergeMasinaService -- masina existenta se sterge corect
    assert(stergeMasinaService(service, "CJ 01 ABC") == 0);
    assert(getLungime(service->repo) == 1);

    // stergeMasinaService -- masina inexistenta returneaza eroare
    assert(stergeMasinaService(service, "XX 00 XXX") == 1);

    // stergeMasinaRepo -- direct pe repo, succes si inexistent
    assert(stergeMasinaRepo(repo, "B 12 ABC") == 0);
    assert(getLungime(repo) == 0);
    assert(stergeMasinaRepo(repo, "B 12 ABC") == 1);

    distrugeService(service);
}

void testUndo() {
    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    // undoService -- fara operatii anterioare returneaza eroare
    assert(undoService(service) == 1);

    // undoService -- undo dupa adauga
    adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "SUV");
    assert(getLungime(service->repo) == 1);
    assert(undoService(service) == 0);
    assert(getLungime(service->repo) == 0);

    // undoService -- undo dupa modifica
    adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "SUV");
    modificaMasinaService(service, "CJ 01 ABC", "Logan", "Berlina");
    assert(strcmp(getMasina(service->repo, 0)->model, "Logan") == 0);
    assert(undoService(service) == 0);
    assert(strcmp(getMasina(service->repo, 0)->model, "Dacia") == 0);

    // undoService -- undo dupa sterge
    stergeMasinaService(service, "CJ 01 ABC");
    assert(getLungime(service->repo) == 0);
    assert(undoService(service) == 0);
    assert(getLungime(service->repo) == 1);

    // undoService -- undo multiplu consecutiv
    adaugaMasinaService(service, "B 12 ABC", "Audi", "Sedan");
    adaugaMasinaService(service, "IS 99 POS", "BMW", "Sport");
    assert(getLungime(service->repo) == 3);
    assert(undoService(service) == 0);
    assert(getLungime(service->repo) == 2);
    assert(undoService(service) == 0);
    assert(getLungime(service->repo) == 1);

    distrugeService(service);
}

void testFiltrareStatus() {
    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "SUV");
    adaugaMasinaService(service, "B 12 ABC", "Audi", "Sedan");
    inchiriazaMasinaService(service, "CJ 01 ABC");

    Masina* rezultate[10];
    int nrRezultate = 0;

    // filtreazaMasiniStatus -- doar masinile inchiriate
    filtreazaMasiniStatus(service, 1, rezultate, &nrRezultate);
    assert(nrRezultate == 1);
    assert(strcmp(rezultate[0]->nrInmatriculare, "CJ 01 ABC") == 0);

    // filtreazaMasiniStatus -- doar masinile libere
    filtreazaMasiniStatus(service, 0, rezultate, &nrRezultate);
    assert(nrRezultate == 1);
    assert(strcmp(rezultate[0]->nrInmatriculare, "B 12 ABC") == 0);

    distrugeService(service);
}

void testGetCopieSiRestaureaza() {
    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "SUV");

    // getCopieLista -- copia are acelasi numar de elemente
    MyList* copie = getCopieLista(repo);
    assert(copie != NULL);
    assert(getLungimeLista(copie) == 1);

    // restaureazaLista -- lista curenta e inlocuita cu snapshot-ul
    restaureazaLista(repo, copie);
    assert(getLungime(repo) == 1);

    distrugeService(service);
}

void testService() {
    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    // adaugaMasinaService -- nr inmatriculare invalid
    assert(adaugaMasinaService(service, "INVALID", "Model", "Categorie") == 1);
    // adaugaMasinaService -- adaugare corecta
    assert(adaugaMasinaService(service, "B 123 ABC", "Bucuresti", "SUV") == 0);
    assert(adaugaMasinaService(service, "CJ 01 ABC", "Cluj", "SUV") == 0);
    // adaugaMasinaService -- duplicat
    assert(adaugaMasinaService(service, "CJ 01 ABC", "Altceva", "Altceva") == 3);

    // returneazaMasinaService -- masina inexistenta
    assert(returneazaMasinaService(service, "NR GRESIT") == 1);

    // modificaMasinaService -- modificare corecta
    int rezModif = modificaMasinaService(service, "B 123 ABC", "Model Nou", "Premium");
    assert(rezModif == 0);
    // modificaMasinaService -- masina inexistenta
    assert(modificaMasinaService(service, "NR GRESIT", "Model", "Categorie") == 2);
    // modificaMasinaService -- date invalide (model si categorie goale)
    assert(modificaMasinaService(service, "CJ 01 ABC", "", "SUV") == 1);
    assert(modificaMasinaService(service, "CJ 01 ABC", "Dacia", "") == 1);

    // inchiriazaMasinaService -- succes, deja inchiriata, inexistenta
    assert(inchiriazaMasinaService(service, "CJ 01 ABC") == 0);
    assert(inchiriazaMasinaService(service, "CJ 01 ABC") == 2);
    assert(inchiriazaMasinaService(service, "XX 00 XXX") == 1);
    // returneazaMasinaService -- succes
    assert(returneazaMasinaService(service, "CJ 01 ABC") == 0);

    Masina* rezultate[10];
    int nrRezultate = 0;

    // filtreazaMasiniCategorie -- gaseste masinile din categoria data
    filtreazaMasiniCategorie(service, "SUV", rezultate, &nrRezultate);
    assert(nrRezultate == 1);
    assert(strcmp(rezultate[0]->categorie, "SUV") == 0);

    // filtreazaMasiniModel -- cautare partiala dupa model
    filtreazaMasiniModel(service, "Mode", rezultate, &nrRezultate);
    assert(nrRezultate == 1);
    assert(strcmp(rezultate[0]->model, "Model Nou") == 0);

    // sorteazaMasiniService -- dupa model crescator
    int nSort;
    sorteazaMasiniService(service, 1, 0, rezultate, &nSort);
    assert(nSort == 2);
    assert(strcmp(rezultate[0]->model, "Cluj") == 0);

    // sorteazaMasiniService -- dupa categorie descrescator
    sorteazaMasiniService(service, 2, 1, rezultate, &nSort);
    assert(strcmp(rezultate[0]->categorie, "SUV") == 0);

    // sorteazaMasiniService -- dupa categorie crescator
    sorteazaMasiniService(service, 2, 0, rezultate, &nSort);
    assert(nSort == 2);

    // getMasinaService -- returneaza masina de la pozitia data
    Masina m = getMasinaService(service, 0);
    assert(strcmp(m.nrInmatriculare, "B 123 ABC") == 0);

    distrugeService(service);
}

void testValidariSpecifice() {
    // valideazaNrInmatriculare -- cazuri invalide diverse
    assert(valideazaNrInmatriculare("B  ABC") == 0);
    assert(valideazaNrInmatriculare(NULL) == 0);
    assert(valideazaNrInmatriculare("12 01 ABC") == 0);
    assert(valideazaNrInmatriculare("CJ-01 ABC") == 0);
    assert(valideazaNrInmatriculare("CJ XX ABC") == 0);
    assert(valideazaNrInmatriculare("CJ 01 123") == 0);
    assert(valideazaNrInmatriculare("B 12A ABC") == 0);
    assert(valideazaNrInmatriculare("B 123-ABC") == 0);
    assert(valideazaNrInmatriculare("B 123 123") == 0);
    assert(valideazaNrInmatriculare("B 1A ABC") == 0);
    assert(valideazaNrInmatriculare("B 12-ABC") == 0);
    assert(valideazaNrInmatriculare("B 12 123") == 0);

    MyRepo* repo = creeazaRepo();
    MasinaService* service = creeazaService(repo);

    // valideazaNrInmatriculare -- formate valide (Bucuresti 3 cifre, 2 cifre, provincie)
    assert(adaugaMasinaService(service, "B 123 ABC", "Model", "Cat") == 0);
    assert(adaugaMasinaService(service, "B 12 ABC", "Model", "Cat") == 0);
    assert(adaugaMasinaService(service, "CJ 01 ABC", "Model", "Cat") == 0);

    // valideazaNrInmatriculare -- formate invalide (prea scurt, prea lung, etc)
    assert(adaugaMasinaService(service, "B 1 ABC", "Model", "Cat") == 1);
    assert(adaugaMasinaService(service, "B 1234 ABC", "Model", "Cat") == 1);
    assert(adaugaMasinaService(service, "C 123 ABC", "Model", "Cat") == 1);
    assert(adaugaMasinaService(service, "CJ 1 ABC", "Model", "Cat") == 1);

    // adaugaMasinaService -- model sau categorie goale
    assert(adaugaMasinaService(service, "CJ 01 ABC", "", "SUV") == 1);
    assert(adaugaMasinaService(service, "CJ 01 ABC", "Dacia", "") == 1);

    distrugeService(service);
}

void testExtraSafety() {
    // distrugeService, distrugeRepo -- cazul NULL (nu crapa)
    distrugeService(NULL);
    distrugeRepo(NULL);
    assert(1);
}

void ruleazaToateTestele() {
    testCoverageComplet();
    testList();
    testDomain();
    testRepo();
    testService();
    testSterge();
    testUndo();
    testFiltrareStatus();
    testGetCopieSiRestaureaza();
    testValidariSpecifice();
    testExtraSafety();
}

#endif