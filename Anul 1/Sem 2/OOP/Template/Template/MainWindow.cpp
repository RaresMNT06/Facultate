#include "MainWindow.h"
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    repo = new Repository("date.txt");
    srv = new Service(*repo);

    // tabel - TODO: schimba coloanele
    tabel = new QTableWidget(this);
    tabel->setColumnCount(2);
    tabel->setHorizontalHeaderLabels({ "ID", "TODO" });
    tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // butoane
    btnFiltreaza = new QPushButton("Filtreaza");
    btnSorteaza = new QPushButton("Sorteaza");
    btnReset = new QPushButton("Reset");
    inputFiltru = new QLineEdit();

    // layout
    QHBoxLayout* layoutButoane = new QHBoxLayout();
    QLabel* label = new QLabel("Filtru:");
    layoutButoane->addWidget(label);
    layoutButoane->addWidget(inputFiltru);
    layoutButoane->addWidget(btnFiltreaza);
    layoutButoane->addWidget(btnSorteaza);
    layoutButoane->addWidget(btnReset);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutButoane);
    layoutPrincipal->addWidget(tabel);

    QWidget* central = new QWidget(this);
    central->setLayout(layoutPrincipal);
    setCentralWidget(central);

    connect(btnFiltreaza, &QPushButton::clicked, this, &MainWindow::filtreaza);
    connect(btnSorteaza, &QPushButton::clicked, this, &MainWindow::sorteaza);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::reset);
    connect(tabel, &QTableWidget::cellClicked, this, &MainWindow::selectieRand);

    afiseaza(srv->getAll());
}

MainWindow::~MainWindow() {
    delete srv;
    delete repo;
}

void MainWindow::afiseaza(const std::vector<Entitate>& items) {
    tabel->setRowCount(0);
    for (const auto& e : items) {
        int rand = tabel->rowCount();
        tabel->insertRow(rand);
        tabel->setItem(rand, 0, new QTableWidgetItem(QString::fromStdString(e.getId())));
        // TODO: adauga celelalte coloane
    }
    coloreazaRanduri();
}

void MainWindow::coloreazaRanduri() {
    // TODO: adauga colorare dupa camp
}

void MainWindow::filtreaza() {
    // TODO: implementeaza filtrarea
}

void MainWindow::sorteaza() {
    // TODO: implementeaza sortarea
}

void MainWindow::reset() {
    inputFiltru->clear();
    afiseaza(srv->getAll());
}

void MainWindow::selectieRand(int rand, int coloana) {
    (void)coloana;
    // TODO: implementeaza selectia
}
