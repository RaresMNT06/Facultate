#pragma once

#include "service.h"
#include "cos_model.h"
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>

/* Fereastra CRUD pentru cos (lista de spalare) - cerinta iteratia 4
   Foloseste QTableView + CosModel (cerinta Model/View)
   Butoane: Goleste, Genereaza

   Modelul CosModel este observer la Service. Cand cosul se schimba din
   orice alta fereastra (Main, alt CosCrud, etc.), modelul primeste
   notificare automat si tabelul se redeseneaza. */
class CosCrud : public QWidget {
    Q_OBJECT

private:
    Service& service;
    CosModel* model;        // modelul Qt - sursa de date pentru tabel

    QTableView* tabel;      // view-ul Qt - afiseaza modelul
    QPushButton* btnGoleste;
    QPushButton* btnGenereaza;
    QSpinBox* inputNrGenerare;
    QLabel* lblTotal;

    /* Construieste UI-ul ferestrei
       @param: - ; @return: - */
    void initUI();

    /* Conecteaza butoanele la slot-uri
       @param: - ; @return: - */
    void connectSignals();

    /* Actualizeaza eticheta cu numarul total de masini
       @param: - ; @return: - */
    void actualizeazaTotal();

public:
    /* Constructor - construieste fereastra si inregistreaza modelul
       @param service: referinta la service ; @param parent: parintele Qt
       @return: - */
    explicit CosCrud(Service& service, QWidget* parent = nullptr);

    /* Destructor - sterge modelul (care se de-inregistreaza din observatori)
       @param: - ; @return: - */
    ~CosCrud() override;

private slots:
    /* Slot pentru butonul Goleste - cheama service.golesteListaSpalate()
       Service va apela notifyAll() care actualizeaza toate ferestrele */
    void onGoleste();

    /* Slot pentru butonul Genereaza - genereaza N masini random in cos
       N e luat din QSpinBox */
    void onGenereaza();
};
