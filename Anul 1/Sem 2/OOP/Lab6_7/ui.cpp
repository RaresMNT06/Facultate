#include "ui.h"
#include <iostream>
#include <string>

/* Initializeaza Ui-ul cu o referinta la service
   @param service: referinta la service ; @return: - */
Ui::Ui(Service& service) noexcept : service{ service } {}

/* Afiseaza o lista MyList de masini numerotata
   @param masini: lista de masini de afisat ; @return: - */
void Ui::afiseazaMasini(const MyList<Masina>& masini) const {
    if (masini.empty()) {
        std::cout << "  (nicio masina)\n";
        return;
    }
    for (size_t i = 0; i < masini.size(); i++)
        std::cout << i + 1 << ". " << masini.at(i).toString() << "\n";
}

/* Afiseaza un vector de masini numerotata
   @param masini: lista de masini de afisat ; @return: - */
void Ui::afiseazaMasini(const std::vector<Masina>& masini) const {
    if (masini.empty()) {
        std::cout << "  (nicio masina)\n";
        return;
    }
    for (size_t i = 0; i < masini.size(); i++)
        std::cout << i + 1 << ". " << masini.at(i).toString() << "\n";
}

/* Citeste datele unei masini de la tastatura si o adauga prin service
   @param: - ; @return: - */
void Ui::adauga_masina() {
    std::string nr, prod, model, tip;
    std::cin.ignore();
    std::cout << "Nr. inmatriculare: "; std::getline(std::cin, nr);
    std::cout << "Producator: ";        std::getline(std::cin, prod);
    std::cout << "Model: ";             std::getline(std::cin, model);
    std::cout << "Tip: ";               std::getline(std::cin, tip);
    try {
        service.adaugaMasina(nr, prod, model, tip);
        std::cout << "Masina adaugata cu succes!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare de la tastatura si sterge masina prin service
   @param: - ; @return: - */
void Ui::sterge_masina() {
    std::string nr;
    std::cin.ignore();
    std::cout << "Nr. inmatriculare de sters: "; std::getline(std::cin, nr);
    try {
        service.stergeMasina(nr);
        std::cout << "Masina stearsa cu succes!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare si datele noi de la tastatura si modifica masina prin service
   @param: - ; @return: - */
void Ui::modifica_masina() {
    std::string nr, prod, model, tip;
    std::cin.ignore();
    std::cout << "Nr. inmatriculare de modificat: "; std::getline(std::cin, nr);
    std::cout << "Producator nou: ";                  std::getline(std::cin, prod);
    std::cout << "Model nou: ";                       std::getline(std::cin, model);
    std::cout << "Tip nou: ";                         std::getline(std::cin, tip);
    try {
        service.modificaMasina(nr, prod, model, tip);
        std::cout << "Masina modificata cu succes!\n";
    }
    catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare de la tastatura si afiseaza masina gasita
   @param: - ; @return: - */
void Ui::cauta_masina() {
    std::string nr;
    std::cin.ignore();
    std::cout << "Nr. inmatriculare de cautat: "; std::getline(std::cin, nr);
    try {
        const Masina& m = service.cautaMasina(nr);
        std::cout << "Gasit: " << m.toString() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Afiseaza toate masinile din lista
   @param: - ; @return: - */
void Ui::afisare_masini() {
    afiseazaMasini(service.getToateMasinile());
}

/* Afiseaza submeniul de filtrare, citeste criteriul si afiseaza rezultatele
   @param: - ; @return: - */
void Ui::filtrare_masini() {
    std::cout << "Criteriu:\n";
    std::cout << "1. Producator\n";
    std::cout << "2. Tip\n";
    std::cout << "Optiune: ";
    int opt; std::cin >> opt;

    std::vector<Masina> rezultat;
    if (opt == 1) {
        std::string prod;
        std::cin.ignore();
        std::cout << "Producator: "; std::getline(std::cin, prod);
        rezultat = service.filtreazaDupaProducator(prod);
    }
    else if (opt == 2) {
        std::string tip;
        std::cin.ignore();
        std::cout << "Tip: "; std::getline(std::cin, tip);
        rezultat = service.filtreazaDupaTip(tip);
    }
    else {
        std::cout << "Optiune invalida!\n";
        return;
    }
    afiseazaMasini(rezultat);
}

/* Afiseaza submeniul de sortare, citeste criteriul si modul si afiseaza rezultatele
   @param: - ; @return: - */
void Ui::sortare_masini() {
    std::cout << "Criteriu:\n";
    std::cout << "1. Nr. inmatriculare\n";
    std::cout << "2. Tip\n";
    std::cout << "3. Producator + Model\n";
    std::cout << "Optiune: ";
    int opt; std::cin >> opt;

    if (opt < 1 || opt > 3) {
        std::cout << "Optiune invalida!\n";
        return;
    }

    std::cout << "Mod:\n";
    std::cout << "1. Crescator\n";
    std::cout << "2. Descrescator\n";
    std::cout << "Optiune: ";
    int mod; std::cin >> mod;

    if (mod < 1 || mod > 2) {
        std::cout << "Optiune invalida!\n";
        return;
    }

    const bool crescator = (mod == 1);

    std::vector<Masina> rezultat;
    if (opt == 1)
        rezultat = service.sorteazaDupaNrInmatriculare(crescator);
    else if (opt == 2)
        rezultat = service.sorteazaDupaTip(crescator);
    else
        rezultat = service.sorteazaDupaProducatorModel(crescator);

    afiseazaMasini(rezultat);
}

/* Afiseaza meniul principal si proceseaza comenzile utilizatorului
   @param: - ; @return: - */
void Ui::run() {
    while (true) {
        std::cout << "\n--- INCHIRIERE MASINI ---\n";
        std::cout << "1. Adauga masina\n";
        std::cout << "2. Sterge masina\n";
        std::cout << "3. Modifica masina\n";
        std::cout << "4. Cauta masina\n";
        std::cout << "5. Afiseaza toate masinile\n";
        std::cout << "6. Filtrare masini\n";
        std::cout << "7. Sortare masini\n";
        std::cout << "0. Iesire\n";
        std::cout << "Comanda: ";

        int opt; std::cin >> opt;
        switch (opt) {
        case 1: adauga_masina();   break;
        case 2: sterge_masina();   break;
        case 3: modifica_masina(); break;
        case 4: cauta_masina();    break;
        case 5: afisare_masini();  break;
        case 6: filtrare_masini(); break;
        case 7: sortare_masini();  break;
        case 0: return;
        default: std::cout << "Comanda invalida!\n";
        }
    }
}