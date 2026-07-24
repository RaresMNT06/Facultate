#include "ui.h"
#include "Exceptii.h"
#include <iostream>
#include <string>
#include <limits>

/* Initializeaza Ui-ul cu o referinta la service
   @param service: referinta la service ; @return: - */
Ui::Ui(Service& service) noexcept : service{ service } {}

/* Afiseaza o lista de masini numerotata
   @param masini: lista de masini de afisat ; @return: - */
void Ui::afiseazaMasini(const std::vector<Masina>& masini) const {
    if (masini.empty()) {
        std::cout << "  (nicio masina)\n";
        return;
    }
    size_t index = 1;
    for (const auto& m : masini) {
        std::cout << index << ". " << m.toString() << "\n";
        ++index;
    }
}

/* Citeste datele unei masini de la tastatura si o adauga prin service
   @param: - ; @return: - */
void Ui::adaugaMasina() {
    std::string nr, prod, model, tip;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare: "; std::getline(std::cin, nr);
    std::cout << "Producator: ";        std::getline(std::cin, prod);
    std::cout << "Model: ";             std::getline(std::cin, model);
    std::cout << "Tip: ";               std::getline(std::cin, tip);
    try {
        service.adaugaMasina(nr, prod, model, tip);
        std::cout << "Masina adaugata cu succes!\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare de la tastatura si sterge masina prin service
   @param: - ; @return: - */
void Ui::stergeMasina() {
    std::string nr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare de sters: "; std::getline(std::cin, nr);
    try {
        service.stergeMasina(nr);
        std::cout << "Masina stearsa cu succes!\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare si datele noi de la tastatura si modifica masina prin service
   @param: - ; @return: - */
void Ui::modificaMasina() {
    std::string nr, prod, model, tip;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare de modificat: "; std::getline(std::cin, nr);
    std::cout << "Producator nou: ";                  std::getline(std::cin, prod);
    std::cout << "Model nou: ";                       std::getline(std::cin, model);
    std::cout << "Tip nou: ";                         std::getline(std::cin, tip);
    try {
        service.modificaMasina(nr, prod, model, tip);
        std::cout << "Masina modificata cu succes!\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare de la tastatura si afiseaza masina gasita
   @param: - ; @return: - */
void Ui::cautaMasina() {
    std::string nr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare de cautat: "; std::getline(std::cin, nr);
    try {
        const Masina& m = service.cautaMasina(nr);
        std::cout << "Gasit: " << m.toString() << "\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Afiseaza toate masinile din lista
   @param: - ; @return: - */
void Ui::afisareMasini() {
    afiseazaMasini(service.getToateMasinile());
}

/* Afiseaza submeniul de filtrare, citeste criteriul si afiseaza rezultatele
   @param: - ; @return: - */
void Ui::filtrareMasini() {
    std::cout << "Criteriu:\n";
    std::cout << "1. Producator\n";
    std::cout << "2. Tip\n";
    std::cout << "Optiune: ";
    int opt; std::cin >> opt;

    std::vector<Masina> rezultat;
    if (opt == 1) {
        std::string prod;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Producator: "; std::getline(std::cin, prod);
        rezultat = service.filtreazaDupaProducator(prod);
    }
    else if (opt == 2) {
        std::string tip;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
void Ui::sortareMasini() {
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

/* Citeste nrInmatriculare si marcheaza masina ca inchiriata prin service
   @param: - ; @return: - */
void Ui::inchiriereMasina() {
    std::string nr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare de inchiriat: "; std::getline(std::cin, nr);
    try {
        service.inchiriazaMasina(nr);
        std::cout << "Masina inchiriata cu succes!\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Citeste nrInmatriculare si marcheaza masina ca returnata prin service
   @param: - ; @return: - */
void Ui::returnareMasina() {
    std::string nr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nr. inmatriculare de returnat: "; std::getline(std::cin, nr);
    try {
        service.returneazaMasina(nr);
        std::cout << "Masina returnata cu succes!\n";
    }
    catch (const MasinaException& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

/* Submeniu pentru cerinta 9: gestionarea listei de masini de spalat
   Optiuni: Goleste, Adauga, Genereaza, Export, Afiseaza
   Dupa fiecare actiune se afiseaza numarul total de masini din lista de spalat
   @param: - ; @return: - */
void Ui::meniuSpalare() {
    while (true) {
        std::cout << "\n--- LISTA DE SPALARE ---\n";
        std::cout << "1. Goleste lista\n";
        std::cout << "2. Adauga in lista (dupa nr. inmatriculare)\n";
        std::cout << "3. Genereaza lista (selectie aleatoare)\n";
        std::cout << "4. Afiseaza lista\n";
        std::cout << "5. Export in fisier (CSV sau HTML)\n";
        std::cout << "0. Inapoi la meniul principal\n";
        std::cout << "Comanda: ";

        int opt; std::cin >> opt;

        if (opt == 0) return;

        switch (opt) {
        case 1: {
            // Goleste lista
            service.golesteListaSpalate();
            std::cout << "Lista de spalare a fost golita.\n";
            break;
        }
        case 2: {
            // Adauga o masina dupa nr. inmatriculare
            std::string nr;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nr. inmatriculare de adaugat: "; std::getline(std::cin, nr);
            try {
                service.adaugaInListaSpalate(nr);
                std::cout << "Masina adaugata in lista de spalare.\n";
            }
            catch (const MasinaException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            // Genereaza lista cu n masini aleatoare
            std::cout << "Numar de masini de generat: ";
            size_t n; std::cin >> n;
            try {
                service.genereazaListaSpalate(n);
                std::cout << "Lista de spalare generata cu " << n << " masini.\n";
            }
            catch (const MasinaException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            // Afiseaza lista curenta
            afiseazaMasini(service.getListaSpalate());
            break;
        }
        case 5: {
            // Export in fisier - se face DOAR la cerere (cosul nu e persistent)
            std::string fisier;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nume fisier (cu extensia .csv sau .html): ";
            std::getline(std::cin, fisier);
            try {
                service.exportListaSpalate(fisier);
                std::cout << "Lista exportata in '" << fisier << "'.\n";
            }
            catch (const MasinaException& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
            break;
        }
        default:
            std::cout << "Comanda invalida!\n";
        }

        // Cerinta din enunt: dupa fiecare actiune se afiseaza
        // numarul total de masini din lista de spalare
        std::cout << "[Numar total masini in lista de spalare: "
            << service.lungimeListaSpalate() << "]\n";
    }
}

/* Afiseaza raportul cu numarul de masini grupate dupa tip
   Foloseste un dictionar (std::map) populat de Service
   @param: - ; @return: - */
void Ui::afiseazaRaport() {
    auto raport = service.analizaMasiniDupaTip();
    if (raport.empty()) {
        std::cout << "Nu exista masini in garaj pentru raport.\n";
        return;
    }
    std::cout << "\n--- RAPORT: numar masini pe tip ---\n";
    // Range-based for peste dictionar (cheia e ordonata alfabetic in map)
    for (const auto& [tip, dto] : raport) {
        std::cout << tip << " : " << dto.aparitii << " masini\n";
    }
}

/* Afiseaza meniul principal si proceseaza comenzile utilizatorului
   Ruleaza in bucla pana la alegerea iesirii (optiunea 0)
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
        std::cout << "8. Inchiriere masina\n";
        std::cout << "9. Returnare masina\n";
        std::cout << "10. Lista de spalare (cerinta 9)\n";
        std::cout << "11. Raport masini pe tip\n";
        std::cout << "0. Iesire\n";
        std::cout << "Comanda: ";

        int opt; std::cin >> opt;
        switch (opt) {
        case 1:  adaugaMasina();     break;
        case 2:  stergeMasina();     break;
        case 3:  modificaMasina();   break;
        case 4:  cautaMasina();      break;
        case 5:  afisareMasini();    break;
        case 6:  filtrareMasini();   break;
        case 7:  sortareMasini();    break;
        case 8:  inchiriereMasina(); break;
        case 9:  returnareMasina();  break;
        case 10: meniuSpalare();     break;
        case 11: afiseazaRaport();   break;
        case 0: return;
        default: std::cout << "Comanda invalida!\n";
        }
    }
}