#include "repo.h"
#include "service.h"
#include "ui.h"
#include "teste.h"
#include <iostream>
#include <crtdbg.h>

/* Punctul de intrare al aplicatiei
   Ruleaza testele, porneste aplicatia si verifica memory leaks la final
   @param: -
   @return: 0 la terminare normala */
int main() {
    // Ruleaza toate testele unitare la pornirea aplicatiei
    runAllTests();

    // Bloc separat cu acolade - fortam distrugerea obiectelor
    // inainte de verificarea memory leaks
    {
        Repository repo;
        Service service{ repo };
        Ui ui{ service };

        // Populam repository-ul cu masini predefinite pentru testare rapida
        // Includem si statusul de inchiriere (cerinta din enunt)
        service.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina", false);
        service.adaugaMasina("CJ 02 XYZ", "BMW", "X5", "SUV", true);
        service.adaugaMasina("IS 03 AAA", "Toyota", "Corolla", "sedan", false);
        service.adaugaMasina("B 04 BBB", "Renault", "Megane", "hatchback", true);
        service.adaugaMasina("MM 05 CCC", "Volkswagen", "Golf", "hatchback", false);
        service.adaugaMasina("CJ 06 DDD", "Audi", "A4", "berlina", false);
        service.adaugaMasina("CJ 07 EEE", "Mercedes", "GLC", "SUV", true);
        service.adaugaMasina("B 08 FFF", "Skoda", "Octavia", "berlina", false);
        service.adaugaMasina("IS 09 GGG", "Hyundai", "Tucson", "SUV", false);
        service.adaugaMasina("MM 10 HHH", "Ford", "Fiesta", "hatchback", true);

        // Populam si lista de spalare cu 6 masini predefinite
        service.adaugaInListaSpalate("CJ 01 ABC");
        service.adaugaInListaSpalate("CJ 02 XYZ");
        service.adaugaInListaSpalate("IS 03 AAA");
        service.adaugaInListaSpalate("B 04 BBB");
        service.adaugaInListaSpalate("MM 05 CCC");
        service.adaugaInListaSpalate("CJ 06 DDD");

        // Porneste bucla principala a meniului
        ui.run();
    }
    // Toate obiectele din blocul de mai sus sunt distruse acum
    // Verificam daca au ramas alocari nealiberate
    if (_CrtDumpMemoryLeaks())
        std::cout << "Exista Memory Leaks!\n";
    else
        std::cout << "Nu exista Memory Leaks!\n";

    return 0;
}