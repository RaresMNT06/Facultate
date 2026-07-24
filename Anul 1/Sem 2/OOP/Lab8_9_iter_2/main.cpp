#include "repo.h"
#include "repo_dictionar.h"
#include "service.h"
#include "ui.h"
#include "teste.h"
#include <iostream>
#include <memory>
#include <crtdbg.h>

/* Punctul de intrare al aplicatiei
   Iteratia 2: la pornire utilizatorul alege ce tip de repo foloseste
   - Repository (cu vector + persistenta in fisier)
   - RepoDictionar (cu map + probabilitate de eroare)
   Foloseste polimorfism prin RepoAbstract
   @param: - ; @return: 0 la terminare normala */
int main() {
    // Ruleaza toate testele unitare la pornirea aplicatiei
    runAllTests();

    // Bloc separat cu acolade - fortam distrugerea obiectelor inainte de _CrtDumpMemoryLeaks
    {
        // Meniu de alegere a tipului de repository
        std::cout << "\n=== ALEGE TIP REPOSITORY ===\n";
        std::cout << "1. Repository normal (cu persistenta in fisier 'masini.txt')\n";
        std::cout << "2. Repository cu dictionar (cu probabilitate de eroare)\n";
        std::cout << "Optiune: ";

        int alegere = 1;
        std::cin >> alegere;

        // Folosim unique_ptr la RepoAbstract pentru polimorfism + gestionare automata a memoriei
        std::unique_ptr<RepoAbstract> repo;

        if (alegere == 2) {
            // Cere probabilitatea de eroare
            std::cout << "Introdu probabilitatea de eroare (intre 0 si 1): ";
            double p = 0.0;
            std::cin >> p;
            try {
                repo = std::make_unique<RepoDictionar>(p);
                // Adaugam cateva masini predefinite (ne asumam ca probabilitatea e mica)
                repo->adauga(Masina{ "CJ 01 ABC", "Dacia", "Logan", "berlina", false });
                repo->adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV", true });
                repo->adauga(Masina{ "IS 03 AAA", "Toyota", "Corolla", "sedan", false });
                std::cout << "Repository cu dictionar creat cu probabilitate " << p << "\n";
            }
            catch (const MasinaException& e) {
                std::cout << "Eroare la initializare: " << e.what() << "\n";
                return 1;
            }
        }
        else {
            // Repository normal cu persistenta
            repo = std::make_unique<Repository>("masini.txt");
            std::cout << "Repository creat din fisierul 'masini.txt'\n";

            // Daca fisierul era gol/inexistent, populam cu mesini predefinite
            if (repo->size() == 0) {
                repo->adauga(Masina{ "CJ 01 ABC", "Dacia", "Logan", "berlina", false });
                repo->adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV", true });
                repo->adauga(Masina{ "IS 03 AAA", "Toyota", "Corolla", "sedan", false });
                repo->adauga(Masina{ "B 04 BBB", "Renault", "Megane", "hatchback", true });
                repo->adauga(Masina{ "MM 05 CCC", "Volkswagen", "Golf", "hatchback", false });
                repo->adauga(Masina{ "CJ 06 DDD", "Audi", "A4", "berlina", false });
                repo->adauga(Masina{ "CJ 07 EEE", "Mercedes", "GLC", "SUV", true });
                repo->adauga(Masina{ "B 08 FFF", "Skoda", "Octavia", "berlina", false });
                repo->adauga(Masina{ "IS 09 GGG", "Hyundai", "Tucson", "SUV", false });
                repo->adauga(Masina{ "MM 10 HHH", "Ford", "Fiesta", "hatchback", true });
            }
        }

        // Service-ul lucreaza prin referinta abstracta - polimorfism!
        Service service{ *repo };
        Ui ui{ service };

        // Porneste bucla principala a meniului
        ui.run();
        // unique_ptr elibereaza automat memoria la iesirea din bloc
    }

    if (_CrtDumpMemoryLeaks())
        std::cout << "Exista Memory Leaks!\n";
    else
        std::cout << "Nu exista Memory Leaks!\n";

    return 0;
}
