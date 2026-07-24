#include "repo.h"
#include "service.h"
#include "mainwindow.h"
#include "teste.h"
#include "iostream"
#include "crtdbg.h"

#include <QApplication>
#include <QMessageBox>
#include <memory>

/* Punctul de intrare al aplicatiei - ITERATIA 3 GUI cu Qt
   Foloseste Repository cu persistenta in fisier 'masini.txt'.
   Cerinta: NU mai folosim _CrtDumpMemoryLeaks pentru ca nu functioneaza cu Qt.
   @param argc, argv: parametri standard pentru QApplication
   @return: 0 la terminare normala */
int main(int argc, char* argv[]) {
    // Ruleaza testele unitare la pornire
    runAllTests();

    // QApplication trebuie creat inainte de orice widget Qt
    QApplication app(argc, argv);

    // Repository cu persistenta in fisier
    Repository repo{ "masini.txt" };

    // Daca fisierul era gol/inexistent, populam cu masini predefinite
    if (repo.size() == 0) {
        repo.adauga(Masina{ "CJ 01 ABC", "Dacia", "Logan", "berlina", false });
        repo.adauga(Masina{ "CJ 02 XYZ", "BMW", "X5", "SUV", true });
        repo.adauga(Masina{ "IS 03 AAA", "Toyota", "Corolla", "sedan", false });
        repo.adauga(Masina{ "B 04 BBB", "Renault", "Megane", "hatchback", true });
        repo.adauga(Masina{ "MM 05 CCC", "Volkswagen", "Golf", "hatchback", false });
        repo.adauga(Masina{ "CJ 06 DDD", "Audi", "A4", "berlina", false });
        repo.adauga(Masina{ "CJ 07 EEE", "Mercedes", "GLC", "SUV", true });
        repo.adauga(Masina{ "B 08 FFF", "Skoda", "Octavia", "berlina", false });
        repo.adauga(Masina{ "IS 09 GGG", "Hyundai", "Tucson", "SUV", false });
        repo.adauga(Masina{ "MM 10 HHH", "Ford", "Fiesta", "hatchback", true });
    }

    Service service{ repo };

    // Construim si afisam fereastra principala
    MainWindow mainWindow{ service };
    mainWindow.show();




    // Pornim event loop-ul Qt
    return app.exec();
}
