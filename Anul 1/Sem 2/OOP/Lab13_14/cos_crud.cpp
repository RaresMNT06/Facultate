#include "cos_crud.h"
#include "exceptii.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

/* Constructor - construieste fereastra
   Modelul se inregistreaza automat ca observer in constructorul sau
   @param service: referinta la service ; @param parent: parintele Qt
   @return: - */
CosCrud::CosCrud(Service& service, QWidget* parent)
    : QWidget(parent), service{ service } {
    setWindowTitle("Cos CRUD - lista de spalare");
    resize(600, 450);

    // Cream modelul (se inregistreaza automat ca observer in constructor)
    model = new CosModel(service, this);

    initUI();
    connectSignals();
    actualizeazaTotal();
}

/* Destructor - sterge modelul (care la randul lui se de-inregistreaza)
   Setarea ca 'this' parent in new CosModel face ca Qt sa-l stearga automat,
   dar punem destructor explicit pentru claritate
   @param: - ; @return: - */
CosCrud::~CosCrud() {
    // model este sters automat de Qt prin parent-child mechanism
    // (am dat 'this' ca parent in constructor)
    // dar destructorul CosModel apeleaza service.removeObserver()
}

/* Construieste UI-ul ferestrei
   @param: - ; @return: - */
void CosCrud::initUI() {
    // Tabelul cu modelul nostru
    tabel = new QTableView(this);
    tabel->setModel(model);

    // Cand utilizatorul da click pe un rand, selecteaza tot randul
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setSelectionMode(QAbstractItemView::SingleSelection);

    // Coloanele se intind sa umple latimea disponibila
    tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    

    // Nu permitem editarea direct in tabel
    tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Inputuri pentru Genereaza
    inputNrGenerare = new QSpinBox(this);
    inputNrGenerare->setRange(1, 1000);
    inputNrGenerare->setValue(3);

    // Butoane
    btnGenereaza = new QPushButton("Genereaza", this);
    btnGoleste = new QPushButton("Goleste lista", this);

    // Eticheta cu numarul total
    lblTotal = new QLabel("Total: 0 masini", this);

    // Layout pentru butoane (orizontal: input nr + buton Genereaza)
    auto* genLayout = new QHBoxLayout();
    genLayout->addWidget(new QLabel("Numar de generat:"));
    genLayout->addWidget(inputNrGenerare);
    genLayout->addWidget(btnGenereaza);

    // Layout principal vertical
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Masini in cos (lista de spalare):"));
    mainLayout->addWidget(tabel);
    mainLayout->addLayout(genLayout);
    mainLayout->addWidget(btnGoleste);
    mainLayout->addWidget(lblTotal);
}

/* Conecteaza butoanele la slot-uri
   @param: - ; @return: - */
void CosCrud::connectSignals() {
    connect(btnGoleste, &QPushButton::clicked, this, &CosCrud::onGoleste);
    connect(btnGenereaza, &QPushButton::clicked, this, &CosCrud::onGenereaza);
}

/* Actualizeaza eticheta cu totalul - apelata manual dupa fiecare operatie
   Tabelul se actualizeaza automat prin Observer pattern
   @param: - ; @return: - */
void CosCrud::actualizeazaTotal() {
    lblTotal->setText(QString("Total: %1 masini").arg(service.lungimeListaSpalate()));
}

/* Slot Goleste - apeleaza service, Observer face restul (actualizare automata)
   @param: - ; @return: - */
void CosCrud::onGoleste() {
    service.golesteListaSpalate();
    actualizeazaTotal();  // doar pentru eticheta - tabelul se actualizeaza singur
}

/* Slot Genereaza - genereaza N masini random
   @param: - ; @return: - */
void CosCrud::onGenereaza() {
    try {
        size_t n = static_cast<size_t>(inputNrGenerare->value());
        service.genereazaListaSpalate(n);
        actualizeazaTotal();
    }
    catch (const MasinaException& e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}
