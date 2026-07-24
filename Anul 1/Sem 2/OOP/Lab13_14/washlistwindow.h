#pragma once

#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>

/* A doua fereastra a aplicatiei - gestioneaza lista de spalare (cerinta 9)
   Operatii: Goleste, Adauga (dupa nr inmatriculare), Genereaza (random),
   Export (CSV/HTML). Dupa fiecare operatie afiseaza numarul total de masini. */
class WashListWindow : public QWidget {
    Q_OBJECT

private:
    Service& service;

    QListWidget* lista;
    QLineEdit* inputNrInm;
    QSpinBox* inputNrGenerare;
    QLineEdit* inputFisier;
    QLabel* lblTotal;

    QPushButton* btnGoleste;
    QPushButton* btnAdauga;
    QPushButton* btnGenereaza;
    QPushButton* btnExport;
    QPushButton* btnRefresh;

    /* Construieste UI-ul ferestrei
       @param: - ; @return: - */
    void initUI();

    /* Conecteaza signal-urile butoanelor la slot-uri
       @param: - ; @return: - */
    void connectSignals();

    /* Reincarca lista de spalare din service si actualizeaza eticheta cu totalul
       @param: - ; @return: - */
    void reload();

public:
    /* Constructor
       @param service: referinta la service ; @param parent: parintele Qt
       @return: - */
    explicit WashListWindow(Service& service, QWidget* parent = nullptr);

private slots:
    /* Goleste lista de spalare */
    void onGoleste();

    /* Adauga masina (cu nrInm din input) in lista de spalare */
    void onAdauga();

    /* Genereaza random N masini in lista */
    void onGenereaza();

    /* Exporta lista in fisier CSV sau HTML */
    void onExport();

    /* Refresh lista (apelat manual daca s-au schimbat datele in alta fereastra) */
    void onRefresh();
};
