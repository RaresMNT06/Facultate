#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "service_masini.h"
#include "repo_masini.h"

class ServiceMasini : public QMainWindow {
    Q_OBJECT
public:
    ServiceMasini(QWidget* parent = nullptr);
    ~ServiceMasini();

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

    void afiseazaVehicule(const std::vector<Vehicul>& vehicule);
    void coloreazaRanduri();
};
