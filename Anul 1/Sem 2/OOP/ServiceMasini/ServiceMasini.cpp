#include "ServiceMasini.h"
#include <QMessageBox>
#include <QHeaderView>

ServiceMasini::ServiceMasini(QWidget* parent) : QMainWindow(parent) {
    repo = new Repository("vehicule.txt");
    srv = new Service(*repo);

    // tabel
    tabel = new QTableWidget(this);
    tabel->setColumnCount(4);
    tabel->setHorizontalHeaderLabels({ "Nr. Matriculare", "Marca", "Tip", "Varsta" });
    tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // butoane si input
    btnFiltreaza = new QPushButton("Filtreaza");
    btnSorteaza = new QPushButton("Sorteaza dupa varsta");
    btnReset = new QPushButton("Reset");
    inputFiltru = new QLineEdit();

    // layout butoane
    QHBoxLayout* layoutButoane = new QHBoxLayout();
    QLabel* label = new QLabel("Tip:");
    layoutButoane->addWidget(label);
    layoutButoane->addWidget(inputFiltru);
    layoutButoane->addWidget(btnFiltreaza);
    layoutButoane->addWidget(btnSorteaza);
    layoutButoane->addWidget(btnReset);

    // layout principal
    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutButoane);
    layoutPrincipal->addWidget(tabel);

    QWidget* central = new QWidget(this);
    central->setLayout(layoutPrincipal);
    setCentralWidget(central);

    // conectare semnale
    connect(btnFiltreaza, &QPushButton::clicked, this, &ServiceMasini::filtreaza);
    connect(btnSorteaza, &QPushButton::clicked, this, &ServiceMasini::sorteaza);
    connect(btnReset, &QPushButton::clicked, this, &ServiceMasini::reset);
    connect(tabel, &QTableWidget::cellClicked, this, &ServiceMasini::selectieRand);

    afiseazaVehicule(srv->getAll());
}

ServiceMasini::~ServiceMasini() {
    delete srv;
    delete repo;
}

void ServiceMasini::afiseazaVehicule(const std::vector<Vehicul>& vehicule) {
    tabel->setRowCount(0);
    for (const auto& v : vehicule) {
        int rand = tabel->rowCount();
        tabel->insertRow(rand);
        tabel->setItem(rand, 0, new QTableWidgetItem(QString::fromStdString(v.getNrInmatriculare())));
        tabel->setItem(rand, 1, new QTableWidgetItem(QString::fromStdString(v.getMarca())));
        tabel->setItem(rand, 2, new QTableWidgetItem(QString::fromStdString(v.getTip())));
        tabel->setItem(rand, 3, new QTableWidgetItem(QString::number(v.getVarsta())));
    }
    coloreazaRanduri();
}

void ServiceMasini::coloreazaRanduri() {
    for (int i = 0; i < tabel->rowCount(); i++) {
        QString tip = tabel->item(i, 2)->text();
        QColor culoare;
        if (tip == "sedan") culoare = Qt::yellow;
        else if (tip == "SUV") culoare = Qt::gray;
        else if (tip == "cabriolet") culoare = Qt::green;
        else culoare = Qt::white;

        for (int j = 0; j < tabel->columnCount(); j++)
            tabel->item(i, j)->setBackground(culoare);
    }
}

void ServiceMasini::filtreaza() {
    std::string tip = inputFiltru->text().toStdString();
    afiseazaVehicule(srv->filtreazaDupaTip(tip));
}

void ServiceMasini::sorteaza() {
    afiseazaVehicule(srv->sorteazaDupaVarsta());
}

void ServiceMasini::reset() {
    inputFiltru->clear();
    afiseazaVehicule(srv->getAll());
}

void ServiceMasini::selectieRand(int rand, int coloana) {
    (void)coloana;
    int varsta = tabel->item(rand, 3)->text().toInt();
    if (varsta > 10)
        QMessageBox::information(this, "Atentie", "Animalul este in varsta si necesita un control");
}
