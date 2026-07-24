#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "Service.h"
#include "Repository.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void filtreaza();
    void sorteaza();
    void reset();
    void selectieRand(int rand, int coloana);

private:
    QTableWidget* tabel;
    QPushButton* btnFiltreaza;
    QPushButton* btnSorteaza;
    QPushButton* btnReset;
    QLineEdit* inputFiltru;

    Repository* repo;
    Service* srv;

    void afiseaza(const std::vector<Entitate>& items);
    void coloreazaRanduri();
};
