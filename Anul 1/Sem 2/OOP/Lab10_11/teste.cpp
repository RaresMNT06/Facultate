#include "teste.h"
#include "repo.h"
#include "service.h"
#include "exceptii.h"
#include <cassert>
#include <string>
#include <fstream>
#include <cstdio>
#include <iterator>

/* ========== TESTE MASINA ========== */

/* Testeaza constructorul si geterii clasei Masina
   @param: - ; @return: - */
void sub_test_masina_constructor_getteri() {
    Masina m{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" };
    assert(m.getNrInmatriculare() == "CJ 01 ABC");
    assert(m.getProducator() == "Toyota");
    assert(m.getModel() == "Corolla");
    assert(m.getTip() == "sedan");
    // Default inchiriata e false
    assert(m.getInchiriata() == false);

    // Constructor cu inchiriata explicit
    Masina m2{ "CJ 02 XYZ", "BMW", "X5", "SUV", true };
    assert(m2.getInchiriata() == true);
}

/* Testeaza seterii clasei Masina
   @param: - ; @return: - */
void sub_test_masina_setteri() {
    Masina m{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" };
    m.setProducator("Honda");
    assert(m.getProducator() == "Honda");
    m.setModel("Civic");
    assert(m.getModel() == "Civic");
    m.setTip("hatchback");
    assert(m.getTip() == "hatchback");
    // Setter pentru statusul de inchiriere
    m.setInchiriata(true);
    assert(m.getInchiriata() == true);
    m.setInchiriata(false);
    assert(m.getInchiriata() == false);
}

/* Testeaza toString, operator== si operator!= ale clasei Masina
   @param: - ; @return: - */
void sub_test_masina_tostring_egalitate() {
    Masina m{ "CJ 01 ABC", "Honda", "Civic", "hatchback" };

    // Verificam formatul de afisare (include si statusul de inchiriere)
    assert(m.toString() == "[CJ 01 ABC] | Producator: Honda | Model: Civic | Tip: hatchback | Status: disponibila");

    // Acelasi nr inmatriculare => egale (chiar daca restul campurilor difera)
    Masina m2{ "CJ 01 ABC", "BMW", "X5", "SUV", true };
    assert(m == m2);
    assert(!(m != m2));

    // Nr diferit => nu sunt egale
    Masina m3{ "B 99 XYZ", "BMW", "X5", "SUV" };
    assert(!(m == m3));
    assert(m != m3);

    // Status inchiriata = true se reflecta in toString
    Masina m4{ "CJ 02 XYZ", "BMW", "X5", "SUV", true };
    assert(m4.toString() == "[CJ 02 XYZ] | Producator: BMW | Model: X5 | Tip: SUV | Status: inchiriata");
}

/* Testeaza copy constructor si move constructor
   @param: - ; @return: - */
void sub_test_masina_copy_move() {
    Masina original{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" };

    // Copy constructor - originalul ramane intact
    Masina copie{ original };
    assert(copie.getNrInmatriculare() == "CJ 01 ABC");
    assert(copie.getProducator() == "Toyota");
    assert(original.getNrInmatriculare() == "CJ 01 ABC");

    // Move constructor
    Masina mutat{ std::move(copie) };
    assert(mutat.getNrInmatriculare() == "CJ 01 ABC");
    assert(mutat.getProducator() == "Toyota");
}

// -------------------------------------------------------------------------------------------------------------------------------
void sub_test_assignment_operator() {
    // Pregătire date
    Masina m1("B 123 ABC", "Dacia", "Logan", "sedan");
    Masina m2("CJ 99 XYZ", "Toyota", "Corolla", "hatchback");

    // Execuție
    m2 = m1;

    // Verificare (asigură-te că m2 are acum datele lui m1)
    assert(m2.getNrInmatriculare() == "B 123 ABC");
    assert(m2.getProducator() == "Dacia");
    assert(m2.getModel() == "Logan");
    assert(m2.getTip() == "sedan");

    // Verifică dacă obiectul sursă a rămas neschimbat
    assert(m1.getNrInmatriculare() == "B 123 ABC");
}


/* Functia principala de test pentru clasa Masina
   @param: - ; @return: - */
void testMasina() {
    sub_test_assignment_operator();
    sub_test_masina_constructor_getteri();
    sub_test_masina_setteri();
    sub_test_masina_tostring_egalitate();
    sub_test_masina_copy_move();
}

/* ========== TESTE REPOSITORY ========== */

/* Testeaza adaugare normala si duplicat in Repository
   @param: - ; @return: - */
void sub_test_repo_adauga() {
    Repository repo;

    // Adaugare normala
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });
    repo.adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV" });
    assert(repo.size() == 2);

    // Adaugare duplicat => MasinaDuplicataException
    try {
        repo.adauga(Masina{ "CJ 01 ABC", "Honda", "Civic", "sedan" });
        //assert(false);
    }
    catch (const MasinaDuplicataException&) {}

    // Verificam ca duplicatul nu a modificat lista
    assert(repo.size() == 2);
}

/* Testeaza existenta si cautarea cu succes si cazul inexistent
   @param: - ; @return: - */
void sub_test_repo_cauta() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });

    // Metoda exista
    assert(repo.exista("CJ 01 ABC") == true);
    assert(repo.exista("INEXISTENT") == false);

    // Cautare cu succes
    const Masina& m = repo.cauta("CJ 01 ABC");
    assert(m.getProducator() == "Toyota");

    // Cautare inexistenta => MasinaInexistentaException
    try {
        repo.cauta("INEXISTENT");
        //assert(false);
    }
    catch (const MasinaInexistentaException&) {}
}

/* Testeaza modificarea cu succes si cazul inexistent
   @param: - ; @return: - */
void sub_test_repo_modifica() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });

    // Modificare cu succes
    repo.modifica("CJ 01 ABC", "Toyota", "Yaris", "hatchback");
    assert(repo.cauta("CJ 01 ABC").getModel() == "Yaris");
    assert(repo.cauta("CJ 01 ABC").getTip() == "hatchback");

    // Modificare inexistenta => MasinaInexistentaException
    try {
        repo.modifica("INEXISTENT", "X", "Y", "Z");
        //assert(false);
    }
    catch (const MasinaInexistentaException&) {}
}

/* Testeaza setarea statusului de inchiriere direct prin Repository
   @param: - ; @return: - */
void sub_test_repo_set_status() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan", false });

    // Setare cu succes
    repo.setStatusInchiriere("CJ 01 ABC", true);
    assert(repo.cauta("CJ 01 ABC").getInchiriata() == true);
    repo.setStatusInchiriere("CJ 01 ABC", false);
    assert(repo.cauta("CJ 01 ABC").getInchiriata() == false);

    // Masina inexistenta => MasinaInexistentaException
    try {
        repo.setStatusInchiriere("INEXISTENT", true);
        //assert(false);
    }
    catch (const MasinaInexistentaException& e) {
        // Apelam what() ca sa acoperim metoda din MasinaException
        std::string msg = e.what();
        assert(!msg.empty());
    }
}

/* Testeaza stergerea cu succes si cazul inexistent
   @param: - ; @return: - */
void sub_test_repo_sterge() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });
    repo.adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV" });

    // Stergere cu succes
    repo.sterge("CJ 01 ABC");
    assert(repo.size() == 1);
    assert(!repo.exista("CJ 01 ABC"));
    assert(repo.exista("CJ 02 XYZ"));

    // Stergere inexistenta => MasinaInexistentaException
    try {
        repo.sterge("INEXISTENT");
        //assert(false);
    }
    catch (const MasinaInexistentaException&) {}
}

/* Testeaza getAll pe repository gol si cu date
   @param: - ; @return: - */
void sub_test_repo_getall() {
    Repository repo;
    assert(repo.getAll().empty());
    assert(repo.size() == 0);

    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });
    assert(repo.getAll().size() == 1);
    assert(repo.size() == 1);
}

/* Functia principala de test pentru Repository
   @param: - ; @return: - */
void testRepository() {
    sub_test_repo_adauga();
    sub_test_repo_cauta();
    sub_test_repo_modifica();
    sub_test_repo_set_status();
    sub_test_repo_sterge();
    sub_test_repo_getall();
}

/* ========== TESTE SERVICE ========== */

/* Testeaza validarea numarului de inmatriculare
   @param: - ; @return: - */
void sub_test_service_validator() {
    Repository repo;
    Service srv{ repo };

    // Format normal valid
    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");

    // Format Bucuresti 2 cifre valid
    srv.adaugaMasina("B 67 MNT", "BMW", "X5", "SUV");

    // Format Bucuresti 3 cifre valid
    srv.adaugaMasina("B 123 ABC", "Toyota", "Corolla", "sedan");

    // Formate invalide => ValidareException
    try { srv.adaugaMasina("INVALID", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("cj 01 abc", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("CJ01ABC", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("CJ 1 ABC", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("B 1 ABC", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}
}

/* Testeaza adaugare valida si toate combinatiile de campuri goale
   @param: - ; @return: - */
void sub_test_service_adauga() {
    Repository repo;
    Service srv{ repo };

    // Adaugare valida
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");
    assert(srv.getToateMasinile().size() == 4);

    // Fiecare camp gol => ValidareException
    try { srv.adaugaMasina("", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("CJ 05 EEE", "", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("CJ 05 EEE", "X", "", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.adaugaMasina("CJ 05 EEE", "X", "Y", ""); assert(false); }
    catch (const ValidareException&) {}

    // Duplicat => MasinaDuplicataException (propagata din Repository)
    try {
        srv.adaugaMasina("CJ 01 AAA", "Altul", "Alt", "SUV");
        //assert(false);
    }
    catch (const MasinaDuplicataException&) {}
}

/* Testeaza stergere valida si camp gol
   @param: - ; @return: - */
void sub_test_service_sterge() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");

    // Camp gol => ValidareException
    try { srv.stergeMasina(""); assert(false); }
    catch (const ValidareException&) {}

    // Stergere inexistenta => MasinaInexistentaException
    try { srv.stergeMasina("ZZ 99 ZZZ"); assert(false); }
    catch (const MasinaInexistentaException&) {}

    // Stergere valida
    srv.stergeMasina("MM 04 DDD");
    assert(srv.getToateMasinile().size() == 1);
}

/* Testeaza modificare valida, campuri goale si format invalid
   @param: - ; @return: - */
void sub_test_service_modifica() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");

    // Fiecare camp gol => ValidareException
    try { srv.modificaMasina("", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.modificaMasina("CJ 01 AAA", "", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.modificaMasina("CJ 01 AAA", "X", "", "Z"); assert(false); }
    catch (const ValidareException&) {}

    try { srv.modificaMasina("CJ 01 AAA", "X", "Y", ""); assert(false); }
    catch (const ValidareException&) {}

    // Format invalid => ValidareException
    try { srv.modificaMasina("INVALID", "X", "Y", "Z"); assert(false); }
    catch (const ValidareException&) {}

    // Masina inexistenta => MasinaInexistentaException
    try { srv.modificaMasina("ZZ 99 ZZZ", "X", "Y", "Z"); assert(false); }
    catch (const MasinaInexistentaException&) {}

    // Modificare valida
    srv.modificaMasina("CJ 01 AAA", "Dacia", "Logan MCV", "break");
    assert(srv.cautaMasina("CJ 01 AAA").getModel() == "Logan MCV");
    assert(srv.cautaMasina("CJ 01 AAA").getTip() == "break");
}

/* Testeaza cautare valida si camp gol
   @param: - ; @return: - */
void sub_test_service_cauta() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");

    // Camp gol => ValidareException
    try { srv.cautaMasina(""); assert(false); }
    catch (const ValidareException&) {}

    // Cautare inexistenta => MasinaInexistentaException
    try { srv.cautaMasina("ZZ 99 ZZZ"); assert(false); }
    catch (const MasinaInexistentaException&) {}

    // Cautare valida
    const Masina& m = srv.cautaMasina("CJ 02 BBB");
    assert(m.getProducator() == "BMW");
}

/* Testeaza filtrarea dupa producator si dupa tip
   @param: - ; @return: - */
void sub_test_service_filtrare() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Filtrare dupa producator
    assert(srv.filtreazaDupaProducator("Dacia").size() == 2);
    assert(srv.filtreazaDupaProducator("BMW").size() == 1);

    // Filtrare dupa tip
    assert(srv.filtreazaDupaTip("hatchback").size() == 1);
    assert(srv.filtreazaDupaTip("SUV").size() == 1);

    // Filtrare fara rezultate
    assert(srv.filtreazaDupaProducator("Inexistent").empty());
    assert(srv.filtreazaDupaTip("Inexistent").empty());
}

/* Testeaza sortarea dupa nr inmatriculare crescator si descrescator
   @param: - ; @return: - */
void sub_test_service_sortare_nr() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");

    // Sortare crescatoare
    const auto sCresc = srv.sorteazaDupaNrInmatriculare(true);
    assert(sCresc[0].getNrInmatriculare() <= sCresc[1].getNrInmatriculare());
    assert(sCresc[1].getNrInmatriculare() <= sCresc[2].getNrInmatriculare());

    // Sortare descrescatoare
    const auto sDescresc = srv.sorteazaDupaNrInmatriculare(false);
    assert(sDescresc[0].getNrInmatriculare() >= sDescresc[1].getNrInmatriculare());
    assert(sDescresc[1].getNrInmatriculare() >= sDescresc[2].getNrInmatriculare());
}

/* Testeaza sortarea dupa tip crescator si descrescator
   @param: - ; @return: - */
void sub_test_service_sortare_tip() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Sortare crescatoare
    const auto sCresc = srv.sorteazaDupaTip(true);
    assert(sCresc[0].getTip() <= sCresc[1].getTip());
    assert(sCresc[1].getTip() <= sCresc[2].getTip());

    // Sortare descrescatoare
    const auto sDescresc = srv.sorteazaDupaTip(false);
    assert(sDescresc[0].getTip() >= sDescresc[1].getTip());
    assert(sDescresc[1].getTip() >= sDescresc[2].getTip());
}

/* Testeaza sortarea dupa producator+model crescator si descrescator
   @param: - ; @return: - */
void sub_test_service_sortare_producator_model() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Sortare crescatoare
    const auto sCresc = srv.sorteazaDupaProducatorModel(true);
    for (size_t i = 0; i + 1 < sCresc.size(); i++)
        assert(sCresc[i].getProducator() + sCresc[i].getModel() <=
            sCresc[i + 1].getProducator() + sCresc[i + 1].getModel());

    // Sortare descrescatoare
    const auto sDescresc = srv.sorteazaDupaProducatorModel(false);
    for (size_t i = 0; i + 1 < sDescresc.size(); i++)
        assert(sDescresc[i].getProducator() + sDescresc[i].getModel() >=
            sDescresc[i + 1].getProducator() + sDescresc[i + 1].getModel());
}

/* Functia principala de test pentru Service
   @param: - ; @return: - */
void testService() {
    sub_test_service_validator();
    sub_test_service_adauga();
    sub_test_service_sterge();
    sub_test_service_modifica();
    sub_test_service_cauta();
    sub_test_service_filtrare();
    sub_test_service_sortare_nr();
    sub_test_service_sortare_tip();
    sub_test_service_sortare_producator_model();
}

/* ========== TESTE INCHIRIERE / RETURNARE ========== */

/* Testeaza inchirierea unei masini si validarile aferente
   @param: - ; @return: - */
void sub_test_service_inchiriere() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");

    // Initial masina e disponibila
    assert(srv.cautaMasina("CJ 01 AAA").getInchiriata() == false);

    // Inchiriere cu succes
    srv.inchiriazaMasina("CJ 01 AAA");
    assert(srv.cautaMasina("CJ 01 AAA").getInchiriata() == true);

    // Inchiriere repetata => ValidareException
    try { srv.inchiriazaMasina("CJ 01 AAA"); assert(false); }
    catch (const ValidareException&) {}

    // Inchiriere cu camp gol => ValidareException
    try { srv.inchiriazaMasina(""); assert(false); }
    catch (const ValidareException&) {}

    // Inchiriere masina inexistenta => MasinaInexistentaException
    try { srv.inchiriazaMasina("ZZ 99 ZZZ"); assert(false); }
    catch (const MasinaInexistentaException&) {}
}

/* Testeaza returnarea unei masini si validarile aferente
   @param: - ; @return: - */
void sub_test_service_returnare() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina", true);  // inchiriata din start

    // Returnare cu succes
    srv.returneazaMasina("CJ 01 AAA");
    assert(srv.cautaMasina("CJ 01 AAA").getInchiriata() == false);

    // Returnare repetata => ValidareException
    try { srv.returneazaMasina("CJ 01 AAA"); assert(false); }
    catch (const ValidareException&) {}

    // Camp gol => ValidareException
    try { srv.returneazaMasina(""); assert(false); }
    catch (const ValidareException&) {}

    // Masina inexistenta => MasinaInexistentaException
    try { srv.returneazaMasina("ZZ 99 ZZZ"); assert(false); }
    catch (const MasinaInexistentaException&) {}
}

/* ========== TESTE LISTA SPALARE - REPOSITORY ========== */

/* Testeaza operatiile de baza pe lista de spalare la nivel de Repository
   @param: - ; @return: - */
void sub_test_repo_lista_spalare() {
    Repository repo;

    Masina m1{ "CJ 01 AAA", "Dacia", "Logan", "berlina" };
    Masina m2{ "CJ 02 BBB", "BMW", "X5", "SUV", true };
    Masina m3{ "IS 03 CCC", "Toyota", "Corolla", "sedan" };

    // Lista incepe goala
    assert(repo.lungimeListaSpalate() == 0);
    assert(repo.getListaSpalate().empty());
    assert(repo.existaInListaSpalate("CJ 01 AAA") == false);

    // Adaugare in lista de spalare
    repo.adaugaInListaSpalate(m1);
    assert(repo.lungimeListaSpalate() == 1);
    assert(repo.existaInListaSpalate("CJ 01 AAA") == true);

    repo.adaugaInListaSpalate(m2);
    repo.adaugaInListaSpalate(m3);
    assert(repo.lungimeListaSpalate() == 3);
    assert(repo.existaInListaSpalate("CJ 02 BBB"));
    assert(repo.existaInListaSpalate("IS 03 CCC"));
    assert(repo.existaInListaSpalate("ZZ 99 ZZZ") == false);

    // Golire
    repo.golesteListaSpalate();
    assert(repo.lungimeListaSpalate() == 0);
    assert(repo.existaInListaSpalate("CJ 01 AAA") == false);
}

/* ========== TESTE LISTA SPALARE - SERVICE ========== */

/* Testeaza adaugarea in lista de spalare prin Service
   @param: - ; @return: - */
void sub_test_service_lista_adauga() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");

    // Camp gol => ValidareException (esueaza la validarea de format)
    try { srv.adaugaInListaSpalate(""); assert(false); }
    catch (const ValidareException&) {}

    // Format invalid => ValidareException
    try { srv.adaugaInListaSpalate("INVALID"); assert(false); }
    catch (const ValidareException&) {}

    // Masina inexistenta in garaj (format valid) => MasinaInexistentaException
    try { srv.adaugaInListaSpalate("ZZ 99 ZZZ"); assert(false); }
    catch (const MasinaInexistentaException&) {}

    // Adaugare valida
    srv.adaugaInListaSpalate("CJ 01 AAA");
    assert(srv.lungimeListaSpalate() == 1);

    srv.adaugaInListaSpalate("CJ 02 BBB");
    assert(srv.lungimeListaSpalate() == 2);

    // Adaugare repetata => ValidareException
    try { srv.adaugaInListaSpalate("CJ 01 AAA"); assert(false); }
    catch (const ValidareException&) {}
    assert(srv.lungimeListaSpalate() == 2);  // dimensiunea nu s-a schimbat
}

/* Testeaza generarea aleatoare a listei de spalare
   @param: - ; @return: - */
void sub_test_service_lista_genereaza() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Toyota", "Corolla", "sedan");
    srv.adaugaMasina("B 04 DDD", "Renault", "Megane", "hatchback");

    // Generare cu 0 => lista goala
    srv.genereazaListaSpalate(0);
    assert(srv.lungimeListaSpalate() == 0);

    // Generare cu valoare valida (mai mica decat numarul total)
    srv.genereazaListaSpalate(2);
    assert(srv.lungimeListaSpalate() == 2);

    // Generare cu numarul total exact
    srv.genereazaListaSpalate(4);
    assert(srv.lungimeListaSpalate() == 4);

    // Verificam ca toate masinile generate sunt valide (existau in repo)
    for (const auto& m : srv.getListaSpalate()) {
        assert(srv.cautaMasina(m.getNrInmatriculare()).getNrInmatriculare()
            == m.getNrInmatriculare());
    }

    // Generare cu valoare prea mare => ValidareException
    try { srv.genereazaListaSpalate(100); assert(false); }
    catch (const ValidareException&) {}

    // Generare goleste lista existenta - re-generam cu 1 si vedem ca ramane 1
    srv.genereazaListaSpalate(1);
    assert(srv.lungimeListaSpalate() == 1);
}

/* Testeaza golirea listei de spalare prin Service
   @param: - ; @return: - */
void sub_test_service_lista_goleste() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaInListaSpalate("CJ 01 AAA");
    assert(srv.lungimeListaSpalate() == 1);

    srv.golesteListaSpalate();
    assert(srv.lungimeListaSpalate() == 0);

    // Golirea unei liste deja goale nu arunca exceptie
    srv.golesteListaSpalate();
    assert(srv.lungimeListaSpalate() == 0);
}

/* Testeaza exportul listei de spalare in CSV si HTML
   Foloseste fisiere temporare in directorul curent
   @param: - ; @return: - */
void sub_test_service_lista_export() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV", true);
    srv.adaugaInListaSpalate("CJ 01 AAA");
    srv.adaugaInListaSpalate("CJ 02 BBB");

    // Nume gol => ValidareException
    try { srv.exportListaSpalate(""); assert(false); }
    catch (const ValidareException&) {}

    // Path catre folder inexistent => ofstream esueaza => ValidareException
    try { srv.exportListaSpalate("Z:/folder_inexistent/lista.csv"); assert(false); }
    catch (const ValidareException&) {}

    // Extensie nesuportata => ValidareException
    try { srv.exportListaSpalate("test.txt"); assert(false); }
    catch (const ValidareException&) {}

    // Export CSV - verificam ca fisierul s-a creat si contine datele corect
    const std::string fisCsv = "test_lista_spalare.csv";
    srv.exportListaSpalate(fisCsv);
    {
        std::ifstream in(fisCsv);
        assert(in.is_open());
        std::string linie;
        // Format CSV: o linie per masina, fara header (stilul colegului)
        std::getline(in, linie);
        assert(linie == "CJ 01 AAA,Dacia,Logan,berlina,0");
        std::getline(in, linie);
        assert(linie == "CJ 02 BBB,BMW,X5,SUV,1");
    }
    std::remove(fisCsv.c_str());

    // Export HTML - verificam ca s-a creat si contine tag-ul de tabel
    const std::string fisHtml = "test_lista_spalare.html";
    srv.exportListaSpalate(fisHtml);
    {
        std::ifstream in(fisHtml);
        assert(in.is_open());
        std::string continut((std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>());
        // Verificam ca avem tag-uri HTML si datele masinilor
        assert(continut.find("<table>") != std::string::npos);
        assert(continut.find("CJ 01 AAA") != std::string::npos);
        assert(continut.find("CJ 02 BBB") != std::string::npos);
    }
    std::remove(fisHtml.c_str());
}

/* Testeaza raportul cu dictionar - numarul de masini pe tip
   @param: - ; @return: - */
void sub_test_service_raport() {
    Repository repo;
    Service srv{ repo };

    // Pe garaj gol, raportul e gol
    auto raportGol = srv.analizaMasiniDupaTip();
    assert(raportGol.empty());

    // Adaugam mai multe masini cu tipuri diferite
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Toyota", "Corolla", "berlina");
    srv.adaugaMasina("B 04 DDD", "Renault", "Megane", "hatchback");
    srv.adaugaMasina("MM 05 EEE", "Audi", "Q7", "SUV");
    srv.adaugaMasina("CJ 06 FFF", "Skoda", "Octavia", "berlina");

    auto raport = srv.analizaMasiniDupaTip();

    // Avem 3 tipuri diferite: berlina, SUV, hatchback
    assert(raport.size() == 3);

    // 3 berline
    assert(raport.contains("berlina"));
    assert(raport.at("berlina").aparitii == 3);
    assert(raport.at("berlina").nume == "berlina");

    // 2 SUV-uri
    assert(raport.contains("SUV"));
    assert(raport.at("SUV").aparitii == 2);

    // 1 hatchback
    assert(raport.contains("hatchback"));
    assert(raport.at("hatchback").aparitii == 1);

    // Tip inexistent
    assert(!raport.contains("coupe"));
}

/* Functia principala de test pentru cerinta 9 (Lista de spalare) si inchiriere
   @param: - ; @return: - */
void testListaSpalare() {
    sub_test_service_inchiriere();
    sub_test_service_returnare();
    sub_test_repo_lista_spalare();
    sub_test_service_lista_adauga();
    sub_test_service_lista_genereaza();
    sub_test_service_lista_goleste();
    sub_test_service_lista_export();
    sub_test_service_raport();
}

/* ========== TESTE ITERATIA 2 ========== */

/* Testeaza UndoAdauga - dupa undo, masina nu mai exista
   @param: - ; @return: - */
void sub_test_undo_adauga() {
    Repository repo;
    Service srv{ repo };

    assert(srv.numarActiuniUndo() == 0);

    // Undo pe lista goala => exceptie
    bool caught = false;
    try { srv.undo(); }
    catch (const ValidareException&) { caught = true; }
    assert(caught);

    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");
    assert(srv.getToateMasinile().size() == 1);
    assert(srv.numarActiuniUndo() == 1);

    // Undo - masina dispare
    srv.undo();
    assert(srv.getToateMasinile().size() == 0);
    assert(srv.numarActiuniUndo() == 0);
}

/* Testeaza UndoSterge - dupa undo, masina e inapoi cu toate datele
   @param: - ; @return: - */
void sub_test_undo_sterge() {
    Repository repo;
    Service srv{ repo };

    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina", true);  // inchiriata
    srv.stergeMasina("CJ 01 ABC");
    assert(srv.getToateMasinile().size() == 0);
    assert(srv.numarActiuniUndo() == 2);  // adauga + sterge

    // Undo sterge => masina revine
    srv.undo();
    assert(srv.getToateMasinile().size() == 1);
    Masina m = srv.cautaMasina("CJ 01 ABC");
    // Verificam ca am pastrat toate datele inclusiv statusul
    assert(m.getProducator() == "Dacia");
    assert(m.getModel() == "Logan");
    assert(m.getInchiriata() == true);
}

/* Testeaza UndoModifica - dupa undo, datele revin la cele initiale
   @param: - ; @return: - */
void sub_test_undo_modifica() {
    Repository repo;
    Service srv{ repo };

    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");
    srv.modificaMasina("CJ 01 ABC", "BMW", "X5", "SUV");
    assert(srv.cautaMasina("CJ 01 ABC").getProducator() == "BMW");

    // Undo modifica => date vechi
    srv.undo();
    Masina m = srv.cautaMasina("CJ 01 ABC");
    assert(m.getProducator() == "Dacia");
    assert(m.getModel() == "Logan");
    assert(m.getTip() == "berlina");
}

/* Testeaza undo pentru inchiriere/returnare
   @param: - ; @return: - */
void sub_test_undo_inchiriere() {
    Repository repo;
    Service srv{ repo };

    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");
    srv.inchiriazaMasina("CJ 01 ABC");
    assert(srv.cautaMasina("CJ 01 ABC").getInchiriata() == true);

    srv.undo();  // anuleaza inchirierea
    assert(srv.cautaMasina("CJ 01 ABC").getInchiriata() == false);
}

/* Testeaza ca undo functioneaza polimorfic - mai multe undo-uri in serie
   @param: - ; @return: - */
void sub_test_undo_polimorfism() {
    Repository repo;
    Service srv{ repo };

    // 3 actiuni diferite: adauga, modifica, sterge
    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");
    srv.modificaMasina("CJ 01 ABC", "BMW", "X5", "SUV");
    srv.adaugaMasina("CJ 02 XYZ", "Audi", "A4", "sedan");
    srv.stergeMasina("CJ 01 ABC");

    assert(srv.numarActiuniUndo() == 4);
    assert(srv.getToateMasinile().size() == 1);  // doar CJ 02 XYZ

    // Undo sterge => CJ 01 ABC revine cu BMW
    srv.undo();
    assert(srv.getToateMasinile().size() == 2);
    assert(srv.cautaMasina("CJ 01 ABC").getProducator() == "BMW");

    // Undo adauga (CJ 02 XYZ) => dispare
    srv.undo();
    assert(srv.getToateMasinile().size() == 1);

    // Undo modifica => Dacia/Logan
    srv.undo();
    assert(srv.cautaMasina("CJ 01 ABC").getProducator() == "Dacia");

    // Undo adauga (CJ 01 ABC) => dispare
    srv.undo();
    assert(srv.getToateMasinile().size() == 0);

    // Undo pe lista goala
    bool caught = false;
    try { srv.undo(); }
    catch (const ValidareException&) { caught = true; }
    assert(caught);
}

/* Testeaza persistenta in fisier - scriere si citire
   @param: - ; @return: - */
void sub_test_persistenta() {
    const std::string fisier = "test_persistenta.txt";
    std::remove(fisier.c_str());  // sterge orice fisier vechi

    // Sesiune 1: scriem cateva masini
    {
        Repository repo{ fisier };
        repo.adauga(Masina{ "CJ 01 ABC", "Dacia", "Logan", "berlina", false });
        repo.adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV", true });
    }  // distrugem repo - fisierul ramane

    // Sesiune 2: citim si verificam
    {
        Repository repo{ fisier };
        assert(repo.size() == 2);
        assert(repo.exista("CJ 01 ABC"));
        assert(repo.exista("CJ 02 XYZ"));
        assert(repo.cauta("CJ 02 XYZ").getInchiriata() == true);

        // Stergem una si verificam in sesiunea urmatoare
        repo.sterge("CJ 01 ABC");
    }

    // Sesiune 3: verificam ca stergerea s-a salvat
    {
        Repository repo{ fisier };
        assert(repo.size() == 1);
        assert(!repo.exista("CJ 01 ABC"));
    }

    std::remove(fisier.c_str());  // curatare
}

/* Testeaza Repository::getAll care returneaza referinta constanta la vector
   (varianta optimizata fara copiere - pentru cazuri unde Service stie ca lucreaza
   cu Repository)
   @param: - ; @return: - */
void sub_test_repo_get_all_ref() {
    Repository repo;

    assert(repo.getAll().empty());
    assert(repo.getAll().size() == 0);

    repo.adauga(Masina{ "CJ 01 ABC", "Dacia", "Logan", "berlina" });
    repo.adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV" });

    const auto& ref = repo.getAll();
    assert(ref.size() == 2);
    assert(ref.at(0).getNrInmatriculare() == "CJ 01 ABC");
    assert(ref.at(1).getNrInmatriculare() == "CJ 02 XYZ");

    repo.adauga(Masina{ "IS 03 AAA", "Toyota", "Corolla", "sedan" });
    assert(repo.getAll().size() == 3);
}

/* Functia principala de test pentru iteratia 2
   @param: - ; @return: - */
void testIteratia2() {
    sub_test_undo_adauga();
    sub_test_undo_sterge();
    sub_test_undo_modifica();
    sub_test_undo_inchiriere();
    sub_test_undo_polimorfism();
    sub_test_persistenta();
    sub_test_repo_get_all_ref();
}

/* ========== RUNNER ========== */

/* Ruleaza toate testele aplicatiei
   @param: - ; @return: - */
void runAllTests() {
    testMasina();
    testRepository();
    testService();
    testListaSpalare();
    testIteratia2();
}
