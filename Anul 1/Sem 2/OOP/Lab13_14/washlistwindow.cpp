#include "washlistwindow.h"
#include "exceptii.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QMessageBox>

/* Constructor - construieste UI-ul si conecteaza signals
   @param service: referinta la service ; @param parent: parintele Qt
   @return: - */
WashListWindow::WashListWindow(Service& service, QWidget* parent)
    : QWidget(parent), service{ service } {
    setWindowTitle("Lista de spalare");
    resize(600, 500);
    initUI();
    connectSignals();
    reload();
}

/* Construieste interfata grafica
   @param: - ; @return: - */
void WashListWindow::initUI() {
    // Lista de masini de spalat (centru)
    lista = new QListWidget(this);

    // Group box pentru actiuni - inputuri si butoane
    auto* actionGroup = new QGroupBox("Actiuni");
    auto* actionLayout = new QGridLayout();

    // Linia 1: Adauga dupa nr inmatriculare
    actionLayout->addWidget(new QLabel("Nr. inmatriculare:"), 0, 0);
    inputNrInm = new QLineEdit();
    actionLayout->addWidget(inputNrInm, 0, 1);
    btnAdauga = new QPushButton("Adauga");
    actionLayout->addWidget(btnAdauga, 0, 2);

    // Linia 2: Genereaza N masini
    actionLayout->addWidget(new QLabel("Numar de generat:"), 1, 0);
    inputNrGenerare = new QSpinBox();
    inputNrGenerare->setRange(1, 1000);
    inputNrGenerare->setValue(3);
    actionLayout->addWidget(inputNrGenerare, 1, 1);
    btnGenereaza = new QPushButton("Genereaza");
    actionLayout->addWidget(btnGenereaza, 1, 2);

    // Linia 3: Export in fisier
    actionLayout->addWidget(new QLabel("Fisier (.csv sau .html):"), 2, 0);
    inputFisier = new QLineEdit();
    inputFisier->setPlaceholderText("ex: lista.csv");
    actionLayout->addWidget(inputFisier, 2, 1);
    btnExport = new QPushButton("Export");
    actionLayout->addWidget(btnExport, 2, 2);

    actionGroup->setLayout(actionLayout);

    // Butoane utilitare jos
    btnGoleste = new QPushButton("Goleste lista");
    btnRefresh = new QPushButton("Refresh");

    auto* utilLayout = new QHBoxLayout();
    utilLayout->addWidget(btnGoleste);
    utilLayout->addWidget(btnRefresh);

    // Eticheta cu numarul total - cerinta din enunt
    lblTotal = new QLabel("Total: 0 masini");
    lblTotal->setStyleSheet("font-weight: bold; font-size: 14px;");

    // Layout principal: vertical
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Masini de spalat:"));
    mainLayout->addWidget(lista);
    mainLayout->addWidget(actionGroup);
    mainLayout->addLayout(utilLayout);
    mainLayout->addWidget(lblTotal);
}

/* Conecteaza signal-urile la slot-uri
   @param: - ; @return: - */
void WashListWindow::connectSignals() {
    connect(btnGoleste, &QPushButton::clicked, this, &WashListWindow::onGoleste);
    connect(btnAdauga, &QPushButton::clicked, this, &WashListWindow::onAdauga);
    connect(btnGenereaza, &QPushButton::clicked, this, &WashListWindow::onGenereaza);
    connect(btnExport, &QPushButton::clicked, this, &WashListWindow::onExport);
    connect(btnRefresh, &QPushButton::clicked, this, &WashListWindow::onRefresh);
}

/* Reincarca lista din service si actualizeaza eticheta de total
   Apelata dupa fiecare operatie - cerinta din enunt
   @param: - ; @return: - */
void WashListWindow::reload() {
    lista->clear();
    auto masini = service.getListaSpalate();
    for (const auto& m : masini) {
        lista->addItem(QString::fromStdString(m.toString()));
    }
    // Cerinta: dupa fiecare operatie afisam numarul total
    lblTotal->setText(QString("Total: %1 masini").arg(service.lungimeListaSpalate()));
}

/* Slot Goleste - sterge toate masinile din lista
   @param: - ; @return: - */
void WashListWindow::onGoleste() {
    service.golesteListaSpalate();
    reload();
}

/* Slot Adauga - adauga masina cu nrInm din input
   @param: - ; @return: - */
void WashListWindow::onAdauga() {
    try {
        service.adaugaInListaSpalate(inputNrInm->text().toStdString());
        reload();
    }
    catch (const MasinaException& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

/* Slot Genereaza - umple lista cu N masini random
   @param: - ; @return: - */
void WashListWindow::onGenereaza() {
    try {
        size_t n = static_cast<size_t>(inputNrGenerare->value());
        service.genereazaListaSpalate(n);
        reload();
    }
    catch (const MasinaException& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

/* Slot Export - salveaza lista in fisier CSV sau HTML
   @param: - ; @return: - */
void WashListWindow::onExport() {
    try {
        service.exportListaSpalate(inputFisier->text().toStdString());
        QMessageBox::information(this, "Succes",
            QString("Lista exportata in: ") + inputFisier->text());
    }
    catch (const MasinaException& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

/* Slot Refresh - util daca s-au schimbat datele in alta fereastra
   @param: - ; @return: - */
void WashListWindow::onRefresh() {
    reload();
}
