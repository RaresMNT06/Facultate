#include "Simulare_oop.h"
#include <QMessageBox>

/* Constructor - initializeaza repo, service si UI */
Simulare_oop::Simulare_oop(QWidget* parent) : QMainWindow(parent) {
    repo = new Repository("filme.txt");
    srv = new Service(*repo);

    // lista de filme
    lista = new QListWidget(this);

    // zona de descriere - doar citire
    descriere = new QTextEdit(this);
    descriere->setReadOnly(true);

    // butoane si input
    btnFiltreaza = new QPushButton("Filtreaza");
    btnSorteaza = new QPushButton("Sorteaza dupa titlu");
    btnReset = new QPushButton("Reset");
    inputFiltru = new QLineEdit();

    // layout butoane
    QHBoxLayout* layoutButoane = new QHBoxLayout();
    QLabel* label = new QLabel("Gen:");
    layoutButoane->addWidget(label);
    layoutButoane->addWidget(inputFiltru);
    layoutButoane->addWidget(btnFiltreaza);
    layoutButoane->addWidget(btnSorteaza);
    layoutButoane->addWidget(btnReset);

    // layout principal
    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutButoane);
    layoutPrincipal->addWidget(lista);
    layoutPrincipal->addWidget(descriere);

    QWidget* central = new QWidget(this);
    central->setLayout(layoutPrincipal);
    setCentralWidget(central);

    // conectare semnale la sloturi
    connect(btnFiltreaza, &QPushButton::clicked, this, &Simulare_oop::filtreaza);
    connect(btnSorteaza, &QPushButton::clicked, this, &Simulare_oop::sorteaza);
    connect(btnReset, &QPushButton::clicked, this, &Simulare_oop::reset);
    connect(lista, &QListWidget::itemClicked, this, &Simulare_oop::selectieFilm);

    // afisare initiala
    afiseaza(srv->getAll());
}

/* Destructor - elibereaza memoria */
Simulare_oop::~Simulare_oop() {
    delete srv;
    delete repo;
}

/* Afiseaza filmele in lista si le coloreaza dupa gen */
void Simulare_oop::afiseaza(const std::vector<Film>& filme) {
    lista->clear();
    for (const auto& f : filme) {
        QString text = QString::fromStdString(f.getCod() + " - " + f.getTitlu() + " - " + f.getAutor() + " - " + f.getGen());
        QListWidgetItem* item = new QListWidgetItem(text);

        // colorare dupa gen
        if (f.getGen() == "comedie") item->setBackground(Qt::lightGray);
        else if (f.getGen() == "drama") item->setBackground(Qt::darkGreen);
        else if (f.getGen() == "actiune") item->setBackground(Qt::blue);
        else if (f.getGen() == "horror") item->setBackground(Qt::red);

        lista->addItem(item);
    }
}



/* Filtreaza filmele dupa genul din inputFiltru */
void Simulare_oop::filtreaza() {
    std::string gen = inputFiltru->text().toStdString();
    afiseaza(srv->filtreazaDupaGen(gen));
}

/* Sorteaza filmele dupa titlu */
void Simulare_oop::sorteaza() {
    afiseaza(srv->sorteazaDupaTitlu());
}

/* Reseteaza lista si sterge inputul */
void Simulare_oop::reset() {
    inputFiltru->clear();
    afiseaza(srv->getAll());
}

/* La selectie afiseaza descrierea in QTextEdit */
void Simulare_oop::selectieFilm(QListWidgetItem* item) {
    int index = lista->row(item);
    const auto& filme = srv->getAll();
    if (index < 0 || index >= (int)filme.size()) return;

    const Film& f = filme[index];
    QString desc = QString("\"%1\" este un film scris de [%2] si face parte din genul [%3]")
        .arg(QString::fromStdString(f.getTitlu()))
        .arg(QString::fromStdString(f.getAutor()))
        .arg(QString::fromStdString(f.getGen()));
    descriere->setText(desc);
}