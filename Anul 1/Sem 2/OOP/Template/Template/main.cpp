#include <QApplication>
#include "MainWindow.h"
#include "teste.h"

int main(int argc, char *argv[]) {
    runAllTests();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
