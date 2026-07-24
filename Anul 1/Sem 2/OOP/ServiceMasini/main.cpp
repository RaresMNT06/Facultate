#include <QApplication>
#include "ServiceMasini.h"
#include "teste.h"

int main(int argc, char* argv[]) {
    runAllTests();

    QApplication a(argc, argv);
    ServiceMasini w;
    w.show();
    return a.exec();
}