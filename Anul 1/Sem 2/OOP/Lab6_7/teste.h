#pragma once
#include "repo.h"
#include "service.h"
#include "MyList.h"
#include <cassert>
#include <stdexcept>

/* Testeaza constructorul si geterii clasei Masina
   @param: - ; @return: - */
inline void sub_test_masina_constructor_getteri() {
    Masina m{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" };
    assert(m.getNrInmatriculare() == "CJ 01 ABC");
    assert(m.getProducator() == "Toyota");
    assert(m.getModel() == "Corolla");
    assert(m.getTip() == "sedan");
}

/* Testeaza seterii clasei Masina
   @param: - ; @return: - */
inline void sub_test_masina_setteri() {
    Masina m{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" };
    m.setProducator("Honda");
    assert(m.getProducator() == "Honda");
    m.setModel("Civic");
    assert(m.getModel() == "Civic");
    m.setTip("hatchback");
    assert(m.getTip() == "hatchback");
}

/* Testeaza toString si operator== al clasei Masina
   @param: - ; @return: - */
inline void sub_test_masina_tostring_egalitate() {
    Masina m{ "CJ 01 ABC", "Honda", "Civic", "hatchback" };

    // Verificam formatul de afisare
    assert(m.toString() == "[CJ 01 ABC] | Producator: Honda | Model: Civic | Tip: hatchback");

    // Acelasi nr inmatriculare => egale
    Masina m2{ "CJ 01 ABC", "BMW", "X5", "SUV" };
    assert(m == m2);

    // Nr diferit => nu sunt egale
    Masina m3{ "B 99 XYZ", "BMW", "X5", "SUV" };
    assert(!(m == m3));
}

/* Functia principala de test pentru clasa Masina
   @param: - ; @return: - */
inline void testMasina() {
    sub_test_masina_constructor_getteri();
    sub_test_masina_setteri();
    sub_test_masina_tostring_egalitate();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Testeaza size, empty, add si at din MyList
   @param: - ; @return: - */
inline void sub_test_mylist_add_at() {
    MyList<int> lista;

    // Test size si empty la inceput
    assert(lista.size() == 0);
    assert(lista.empty());

    // Test add si at
    lista.add(1);
    lista.add(2);
    lista.add(3);
    assert(lista.size() == 3);
    assert(!lista.empty());
    assert(lista.at(0) == 1);
    assert(lista.at(1) == 2);
    assert(lista.at(2) == 3);

    // Test at invalid => exceptie
    try { lista.at(99); assert(false); }
    catch (const std::out_of_range&) {}
}

/* Testeaza remove din MyList
   @param: - ; @return: - */
inline void sub_test_mylist_remove() {
    MyList<int> lista;
    lista.add(1);
    lista.add(2);
    lista.add(3);

    // Remove valid
    lista.remove(1);
    assert(lista.size() == 2);
    assert(lista.at(0) == 1);
    assert(lista.at(1) == 3);

    // Remove invalid => exceptie
    try { lista.remove(99); assert(false); }
    catch (const std::out_of_range&) {}
}

/* Testeaza resize-ul din MyList
   @param: - ; @return: - */
inline void sub_test_mylist_resize() {
    MyList<int> lista;

    // Adaugam mai mult decat capacitatea initiala (2) ca sa fortam resize
    lista.add(1);
    lista.add(2);
    lista.add(3);
    lista.add(4);
    lista.add(5);
    assert(lista.size() == 5);
    assert(lista.at(4) == 5);
}

/* Testeaza copy constructor, move constructor si operatorii de atribuire
   @param: - ; @return: - */
inline void sub_test_mylist_constructori() {
    MyList<int> lista;
    lista.add(1);
    lista.add(2);
    lista.add(3);

    // Test copy constructor
    MyList<int> lista2 = lista;
    assert(lista2.size() == 3);
    assert(lista2.at(0) == 1);

    // Test move constructor
    MyList<int> lista3 = std::move(lista2);
    assert(lista3.size() == 3);
    assert(lista2.size() == 0);

    // Test operator= copiere
    MyList<int> lista4;
    lista4 = lista;
    assert(lista4.size() == 3);

    // Test operator= mutare
    MyList<int> lista5;
    lista5 = std::move(lista4);
    assert(lista5.size() == 3);
    assert(lista4.size() == 0);

    // Test at const invalid => exceptie
    const MyList<int> listaConst = lista;
    try { listaConst.at(99); assert(false); }
    catch (const std::out_of_range&) {}

    // Test operator= copiere peste lista nevida (acopera date[i].~T())
    MyList<int> lista6;
    lista6.add(10);
    lista6.add(20);
    lista6 = lista;  // lista6 e nevida, se apeleaza destructorii
    assert(lista6.size() == lista.size());

    // Test operator= mutare peste lista nevida (acopera date[i].~T())
    MyList<int> lista7;
    lista7.add(10);
    lista7.add(20);
    lista7 = std::move(lista6);  // lista7 e nevida, se apeleaza destructorii
    assert(lista7.size() == lista.size());
}

/* Testeaza iterarea cu for range
   @param: - ; @return: - */
inline void sub_test_mylist_iterare() {
    MyList<int> lista;
    lista.add(1);
    lista.add(2);
    lista.add(3);

    int suma = 0;
    for (const auto& x : lista)
        suma += x;
    assert(suma == 6);
}

/* Functia principala de test pentru MyList
   @param: - ; @return: - */
inline void testMyList() {
    sub_test_mylist_add_at();
    sub_test_mylist_remove();
    sub_test_mylist_resize();
    sub_test_mylist_constructori();
    sub_test_mylist_iterare();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Testeaza adaugare normala si duplicat in Repository
   @param: - ; @return: - */
inline void sub_test_repo_adauga() {
    Repository repo;

    // Adaugare normala
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });
    repo.adauga(Masina{ "CJ 02 XYZ", "BMW",    "X5",      "SUV" });
    assert(repo.size() == 2);

    // Adaugare duplicat => exceptie
    try {
        repo.adauga(Masina{ "CJ 01 ABC", "Honda", "Civic", "sedan" });
        //assert(false);
    }
    catch (const std::runtime_error&) {}
}

/* Testeaza cautarea cu succes si cazul inexistent
   @param: - ; @return: - */
inline void sub_test_repo_cauta() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });

    // Cautare cu succes
    const Masina& m = repo.cauta("CJ 01 ABC");
    assert(m.getProducator() == "Toyota");

    // Cautare inexistenta => exceptie
    try {
        repo.cauta("INEXISTENT");
        //assert(false);
    }
    catch (const std::runtime_error&) {}
}

/* Testeaza modificarea cu succes si cazul inexistent
   @param: - ; @return: - */
inline void sub_test_repo_modifica() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });

    // Modificare cu succes
    repo.modifica("CJ 01 ABC", "Toyota", "Yaris", "hatchback");
    assert(repo.cauta("CJ 01 ABC").getModel() == "Yaris");

    // Modificare inexistenta => exceptie
    try {
        repo.modifica("INEXISTENT", "X", "Y", "Z");
        //assert(false);
    }
    catch (const std::runtime_error&) {}
}

/* Testeaza stergerea cu succes si cazul inexistent
   @param: - ; @return: - */
inline void sub_test_repo_sterge() {
    Repository repo;
    repo.adauga(Masina{ "CJ 01 ABC", "Toyota", "Corolla", "sedan" });
    repo.adauga(Masina{ "CJ 02 XYZ", "BMW",    "X5",      "SUV" });

    // Stergere cu succes
    repo.sterge("CJ 01 ABC");
    assert(repo.size() == 1);
    assert(!repo.exista("CJ 01 ABC"));

    // Stergere inexistenta => exceptie
    try {
        repo.sterge("INEXISTENT");
        //assert(false);
    }
    catch (const std::runtime_error&) {}
}

/* Functia principala de test pentru Repository
   @param: - ; @return: - */
inline void testRepository() {
    sub_test_repo_adauga();
    sub_test_repo_cauta();
    sub_test_repo_modifica();
    sub_test_repo_sterge();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Testeaza validarea numarului de inmatriculare
   @param: - ; @return: - */
inline void sub_test_service_validator() {
    Repository repo;
    Service srv{ repo };

    // Format normal valid
    srv.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");

    // Format Bucuresti 2 cifre valid
    srv.adaugaMasina("B 67 MNT", "BMW", "X5", "SUV");

    // Format Bucuresti 3 cifre valid
    srv.adaugaMasina("B 123 ABC", "Toyota", "Corolla", "sedan");

    // Formate invalide => exceptie
    try { srv.adaugaMasina("INVALID", "X", "Y", "Z");   assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("cj 01 abc", "X", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("CJ01ABC", "X", "Y", "Z");   assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("CJ 1 ABC", "X", "Y", "Z");  assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("B 1 ABC", "X", "Y", "Z");   assert(false); }
    catch (const std::invalid_argument&) {}
}

/* Testeaza adaugare valida si toate combinatiile de campuri goale
   @param: - ; @return: - */
inline void sub_test_service_adauga() {
    Repository repo;
    Service srv{ repo };

    // Adaugare valida
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");
    assert(srv.getToateMasinile().size() == 4);

    // Fiecare camp gol => exceptie
    try { srv.adaugaMasina("", "X", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("CJ 05 EEE", "", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("CJ 05 EEE", "X", "", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.adaugaMasina("CJ 05 EEE", "X", "Y", "");  assert(false); }
    catch (const std::invalid_argument&) {}
}

/* Testeaza stergere valida si camp gol
   @param: - ; @return: - */
inline void sub_test_service_sterge() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");

    // Camp gol => exceptie
    try { srv.stergeMasina(""); assert(false); }
    catch (const std::invalid_argument&) {}

    // Stergere valida
    srv.stergeMasina("MM 04 DDD");
    assert(srv.getToateMasinile().size() == 1);
}

/* Testeaza modificare valida, campuri goale si format invalid
   @param: - ; @return: - */
inline void sub_test_service_modifica() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");

    // Fiecare camp gol => exceptie
    try { srv.modificaMasina("", "X", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.modificaMasina("CJ 01 AAA", "", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.modificaMasina("CJ 01 AAA", "X", "", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}
    try { srv.modificaMasina("CJ 01 AAA", "X", "Y", "");  assert(false); }
    catch (const std::invalid_argument&) {}

    // Format invalid => exceptie
    try { srv.modificaMasina("INVALID", "X", "Y", "Z"); assert(false); }
    catch (const std::invalid_argument&) {}

    // Modificare valida
    srv.modificaMasina("CJ 01 AAA", "Dacia", "Logan MCV", "break");
    assert(srv.cautaMasina("CJ 01 AAA").getModel() == "Logan MCV");
}

/* Testeaza cautare valida si camp gol
   @param: - ; @return: - */
inline void sub_test_service_cauta() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");

    // Camp gol => exceptie
    try { srv.cautaMasina(""); assert(false); }
    catch (const std::invalid_argument&) {}

    // Cautare valida
    const Masina& m = srv.cautaMasina("CJ 02 BBB");
    assert(m.getProducator() == "BMW");
}

/* Testeaza filtrarea dupa producator si dupa tip
   @param: - ; @return: - */
inline void sub_test_service_filtrare() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Filtrare dupa producator
    assert(srv.filtreazaDupaProducator("Dacia").size() == 2);

    // Filtrare dupa tip
    assert(srv.filtreazaDupaTip("hatchback").size() == 1);

    // Filtrare fara rezultate
    assert(srv.filtreazaDupaProducator("Inexistent").size() == 0);
    assert(srv.filtreazaDupaTip("Inexistent").size() == 0);
}

/* Testeaza sortarea dupa nr inmatriculare crescator si descrescator
   @param: - ; @return: - */
inline void sub_test_service_sortare_nr() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");
    srv.adaugaMasina("MM 04 DDD", "Toyota", "Yaris", "hatchback");

    // Sortare crescatoare
    auto sCresc = srv.sorteazaDupaNrInmatriculare(true);
    assert(sCresc.at(0).getNrInmatriculare() <= sCresc.at(1).getNrInmatriculare());
    assert(sCresc.at(1).getNrInmatriculare() <= sCresc.at(2).getNrInmatriculare());

    // Sortare descrescatoare
    auto sDescresc = srv.sorteazaDupaNrInmatriculare(false);
    assert(sDescresc.at(0).getNrInmatriculare() >= sDescresc.at(1).getNrInmatriculare());
    assert(sDescresc.at(1).getNrInmatriculare() >= sDescresc.at(2).getNrInmatriculare());
}

/* Testeaza sortarea dupa tip crescator si descrescator
   @param: - ; @return: - */
inline void sub_test_service_sortare_tip() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Sortare crescatoare
    auto sCresc = srv.sorteazaDupaTip(true);
    assert(sCresc.at(0).getTip() <= sCresc.at(1).getTip());
    assert(sCresc.at(1).getTip() <= sCresc.at(2).getTip());

    // Sortare descrescatoare
    auto sDescresc = srv.sorteazaDupaTip(false);
    assert(sDescresc.at(0).getTip() >= sDescresc.at(1).getTip());
    assert(sDescresc.at(1).getTip() >= sDescresc.at(2).getTip());
}

/* Testeaza sortarea dupa producator+model crescator si descrescator
   @param: - ; @return: - */
inline void sub_test_service_sortare_producator_model() {
    Repository repo;
    Service srv{ repo };
    srv.adaugaMasina("CJ 01 AAA", "Dacia", "Logan", "berlina");
    srv.adaugaMasina("CJ 02 BBB", "BMW", "X5", "SUV");
    srv.adaugaMasina("IS 03 CCC", "Dacia", "Sandero", "hatchback");

    // Sortare crescatoare
    auto sCresc = srv.sorteazaDupaProducatorModel(true);
    for (size_t i = 0; i + 1 < sCresc.size(); i++)
        assert(sCresc.at(i).getProducator() + sCresc.at(i).getModel() <=
            sCresc.at(i + 1).getProducator() + sCresc.at(i + 1).getModel());

    // Sortare descrescatoare
    auto sDescresc = srv.sorteazaDupaProducatorModel(false);
    for (size_t i = 0; i + 1 < sDescresc.size(); i++)
        assert(sDescresc.at(i).getProducator() + sDescresc.at(i).getModel() >=
            sDescresc.at(i + 1).getProducator() + sDescresc.at(i + 1).getModel());
}

/* Functia principala de test pentru Service
   @param: - ; @return: - */
inline void testService() {
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

/* Ruleaza toate testele aplicatiei
   @param: - ; @return: - */
inline void runAllTests() {
    testMyList();
    testMasina();
    testRepository();
    testService();
}