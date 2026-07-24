#include <QApplication>
#include "Simulare_oop.h"
#include "teste.h"

int main(int argc, char* argv[]) {
    runAllTests();

    QApplication a(argc, argv);
    Simulare_oop w;
    w.show();
    return a.exec();
}