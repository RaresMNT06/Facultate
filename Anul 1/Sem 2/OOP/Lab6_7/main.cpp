#include "repo.h"
#include "service.h"
#include "ui.h"
#include "teste.h"
#include <crtdbg.h>

int main() {
    // Ruleaza toate testele la pornirea aplicatiei
    runAllTests();

    {
        // Bloc separat - obiectele sunt distruse la inchiderea acoladei
        Repository repo;
        Service service{ repo };
        Ui ui{ service };

        // Adaugam 5 masini predefinite la pornirea aplicatiei
        service.adaugaMasina("CJ 01 ABC", "Dacia", "Logan", "berlina");
        service.adaugaMasina("CJ 02 XYZ", "BMW", "X5", "SUV");
        service.adaugaMasina("IS 03 AAA", "Toyota", "Corolla", "sedan");
        service.adaugaMasina("B 04 BBB", "Renault", "Megane", "hatchback");
        service.adaugaMasina("MM 05 CCC", "Volkswagen", "Golf", "hatchback");

        // Porneste bucla principala a meniului
        ui.run();
    }

    // Acum toate obiectele sunt distruse, verificam memory leaks
    if (_CrtDumpMemoryLeaks())
        printf("Exista Memory Leaks!");
    else
        printf("Nu exista Memory Leaks!");

    return 0;
}