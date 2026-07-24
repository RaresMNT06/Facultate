#include "mainwindow.h"
#include "washlistwindow.h"
#include "cos_crud.h"
#include "cos_forme.h"
#include "exceptii.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QDialog>
#include <QString>

#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>

/* Constructor - primeste service-ul si construieste UI-ul
   @param service: referinta la service ; @param parent: parintele Qt
   @return: - */
MainWindow::MainWindow(Service& service, QWidget* parent)
    : QWidget(parent), service{ service } {
    setWindowTitle("Inchiriere Masini");
    resize(900, 600);
    initUI();
    connectSignals();
    reloadList();
}

/* Construieste interfata grafica
   Layout-ul: orizontal cu 2 panouri - lista in stanga, controale in dreapta
   @param: - ; @return: - */
void MainWindow::initUI() {
    // ===== Panoul stang: Lista de masini =====
    listaMasini = new QListWidget(this);
    listaMasini->setMinimumWidth(450);

    // Tabel cu aceleasi date afisate pe coloane
    tabelMasini = new QTableWidget(this);
    tabelMasini->setColumnCount(5);

    QStringList headers;
    headers << "Nr. Inm." << "Producator" << "Model" << "Tip" << "Status";
    tabelMasini->setHorizontalHeaderLabels(headers);

    tabelMasini->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabelMasini->setSelectionMode(QAbstractItemView::SingleSelection);
    tabelMasini->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabelMasini->setSortingEnabled(true);
    tabelMasini->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabelMasini->setMinimumHeight(200);

    // ===== Panoul drept: Inputuri si butoane =====
    // Group box pentru campurile de input
    auto* inputGroup = new QGroupBox("Date masina");
    auto* inputLayout = new QGridLayout();

    inputNrInm = new QLineEdit();
    inputProducator = new QLineEdit();
    inputModel = new QLineEdit();
    inputTip = new QLineEdit();
    inputInchiriata = new QCheckBox("Inchiriata");

    inputLayout->addWidget(new QLabel("Nr. inmatriculare:"), 0, 0);
    inputLayout->addWidget(inputNrInm, 0, 1);
    inputLayout->addWidget(new QLabel("Producator:"), 1, 0);
    inputLayout->addWidget(inputProducator, 1, 1);
    inputLayout->addWidget(new QLabel("Model:"), 2, 0);
    inputLayout->addWidget(inputModel, 2, 1);
    inputLayout->addWidget(new QLabel("Tip:"), 3, 0);
    inputLayout->addWidget(inputTip, 3, 1);
    inputLayout->addWidget(inputInchiriata, 4, 0, 1, 2);
    inputGroup->setLayout(inputLayout);

    // Group box pentru butoanele CRUD
    auto* crudGroup = new QGroupBox("Operatii");
    auto* crudLayout = new QGridLayout();

    btnAdd = new QPushButton("Add");
    btnUpdate = new QPushButton("Update");
    btnRemove = new QPushButton("Remove");
    btnInchiriere = new QPushButton("Inchiriere");
    btnReturnare = new QPushButton("Returnare");

    crudLayout->addWidget(btnAdd, 0, 0);
    crudLayout->addWidget(btnUpdate, 0, 1);
    crudLayout->addWidget(btnRemove, 0, 2);
    crudLayout->addWidget(btnInchiriere, 1, 0);
    crudLayout->addWidget(btnReturnare, 1, 1);
    crudGroup->setLayout(crudLayout);

    // Group box pentru filtrare/sortare
    auto* filterGroup = new QGroupBox("Filtrare si sortare");
    auto* filterLayout = new QGridLayout();

    btnFilterProducator = new QPushButton("Filter by Producator");
    btnFilterTip = new QPushButton("Filter by Tip");
    btnSortNr = new QPushButton("Sort by Nr");
    btnSortTip = new QPushButton("Sort by Tip");
    btnSortProdModel = new QPushButton("Sort by Prod+Model");
    btnAfiseazaToate = new QPushButton("Afiseaza toate");

    filterLayout->addWidget(btnFilterProducator, 0, 0);
    filterLayout->addWidget(btnFilterTip, 0, 1);
    filterLayout->addWidget(btnSortNr, 1, 0);
    filterLayout->addWidget(btnSortTip, 1, 1);
    filterLayout->addWidget(btnSortProdModel, 2, 0);
    filterLayout->addWidget(btnAfiseazaToate, 2, 1);
    filterGroup->setLayout(filterLayout);

    // Group box pentru utilitare
    auto* utilGroup = new QGroupBox("Utilitare");
    auto* utilLayout = new QHBoxLayout();

    btnUndo = new QPushButton("Undo");
    btnRaport = new QPushButton("Raport pe tip");
    btnLista = new QPushButton("Lista spalare");

    utilLayout->addWidget(btnUndo);
    utilLayout->addWidget(btnRaport);
    utilLayout->addWidget(btnLista);
    utilGroup->setLayout(utilLayout);

    // Iteratia 4: group box separat pentru ferestrele cu Observer Pattern
    auto* observerGroup = new QGroupBox("Cos (Observer Pattern)");
    auto* observerLayout = new QHBoxLayout();
    btnCosCRUD = new QPushButton("Deschide Cos CRUD");
    btnCosReadOnly = new QPushButton("Deschide Cos Forme");
    observerLayout->addWidget(btnCosCRUD);
    observerLayout->addWidget(btnCosReadOnly);
    observerGroup->setLayout(observerLayout);

    // Eticheta de status
    statusLabel = new QLabel("Gata");
    statusLabel->setStyleSheet("color: green;");

    // Asamblam panoul drept
    auto* rightPanel = new QVBoxLayout();
    rightPanel->addWidget(inputGroup);
    rightPanel->addWidget(crudGroup);
    rightPanel->addWidget(filterGroup);
    rightPanel->addWidget(utilGroup);
    rightPanel->addWidget(observerGroup);
    rightPanel->addStretch();  // impinge totul in sus

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Cream un layout vertical care contine lista SUS si tabelul JOS
    auto* stangaLayout = new QVBoxLayout();
    stangaLayout->addWidget(new QLabel("Lista masini:"));
    stangaLayout->addWidget(listaMasini);
    stangaLayout->addWidget(new QLabel("Tabel masini:"));
    stangaLayout->addWidget(tabelMasini);

    // Layout principal orizontal: in stanga panoul cu lista+tabel, in dreapta butoanele
    auto* mainHLayout = new QHBoxLayout();
    mainHLayout->addLayout(stangaLayout, 1);
    mainHLayout->addLayout(rightPanel);

    // Layout vertical pentru tot - cu status bar jos
    auto* mainVLayout = new QVBoxLayout(this);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->addWidget(statusLabel);

    // ===== Prob Lab: Generare dinamică butoane tipuri =====


    auto* tipGroup = new QGroupBox("Tipuri Masini");
    tipLayout = new QGridLayout();
    tipGroup->setLayout(tipLayout);

    // Luăm raportul de tipuri din service (map-ul pe care l-ai folosit și la onRaport)
    auto raport = service.analizaMasiniDupaTip();

    int row = 0;
    for (auto const& [tip, dto] : raport) {
        // Creăm un buton pentru fiecare tip găsit
        QString numeTip = QString::fromStdString(tip);
        QPushButton* btnTip = new QPushButton(numeTip);

        tipLayout->addWidget(btnTip, row++, 0);

        
        int nrMasini = dto.aparitii;
        connect(btnTip, &QPushButton::clicked, [this, numeTip, nrMasini]() {
            QMessageBox::information(this, "Detalii Tip",
                "Exista " + QString::number(nrMasini) + " masini de tipul " + numeTip);
            });
    }

    
    rightPanel->addWidget(tipGroup);

}

/* Conecteaza signals-urile butoanelor la slot-urile corespunzatoare
   In Qt, butoanele emit signal "clicked" cand sunt apasate
   Slot-urile sunt metodele care reactioneaza la signal
   @param: - ; @return: - */
void MainWindow::connectSignals() {
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdate);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(btnInchiriere, &QPushButton::clicked, this, &MainWindow::onInchiriere);
    connect(btnReturnare, &QPushButton::clicked, this, &MainWindow::onReturnare);
    connect(btnFilterProducator, &QPushButton::clicked, this, &MainWindow::onFilterProducator);
    connect(btnFilterTip, &QPushButton::clicked, this, &MainWindow::onFilterTip);
    connect(btnSortNr, &QPushButton::clicked, this, &MainWindow::onSortNr);
    connect(btnSortTip, &QPushButton::clicked, this, &MainWindow::onSortTip);
    connect(btnSortProdModel, &QPushButton::clicked, this, &MainWindow::onSortProdModel);
    connect(btnAfiseazaToate, &QPushButton::clicked, this, &MainWindow::onAfiseazaToate);
    connect(btnUndo, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(btnRaport, &QPushButton::clicked, this, &MainWindow::onRaport);
    connect(btnLista, &QPushButton::clicked, this, &MainWindow::onDeschideLista);

    // Iteratia 4: conectare butoane noi pentru ferestrele cu Observer
    connect(btnCosCRUD, &QPushButton::clicked, this, &MainWindow::onDeschideCosCRUD);
    connect(btnCosReadOnly, &QPushButton::clicked, this, &MainWindow::onDeschideCosReadOnly);

    // Cand utilizatorul selecteaza o masina, populam campurile automat
    connect(listaMasini, &QListWidget::itemSelectionChanged, this, &MainWindow::onItemSelected);
}

/* Reincarca lista de masini din service
   @param: - ; @return: - */
void MainWindow::reloadList() {
    displayList(service.getToateMasinile());
}

void MainWindow::updateDynamicButtons() {
    
    QLayoutItem* item;
    while ((item = tipLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget(); 
        }
        delete item; 
    }

    
    auto raport = service.analizaMasiniDupaTip();
    int row = 0;
    for (auto const& [tip, dto] : raport) {
        QString numeTip = QString::fromStdString(tip);
        QPushButton* btn = new QPushButton(numeTip);
        tipLayout->addWidget(btn, row++, 0);

        int nr = dto.aparitii;
        connect(btn, &QPushButton::clicked, [this, numeTip, nr]() {
            QMessageBox::information(this, "Info",
                "Tip: " + numeTip + "\nMasini: " + QString::number(nr));
            });
    }
}

/* Afiseaza masinile in AMBELE: lista (sus) si tabel (jos)
   Lista afiseaza ca string concatenat, tabelul pe coloane separate
   @param masini: vectorul de masini ; @return: - */
void MainWindow::displayList(const std::vector<Masina>& masini) {
    // Populam lista (la fel ca inainte)
    listaMasini->clear();
    for (const auto& m : masini) {
        listaMasini->addItem(QString::fromStdString(m.toString()));
    }

    // Populam tabelul
    tabelMasini->setSortingEnabled(false);  // dezactivam temporar sortarea
    tabelMasini->setRowCount(0);
    tabelMasini->setRowCount(static_cast<int>(masini.size()));

    for (int i = 0; i < static_cast<int>(masini.size()); ++i) {
        const auto& m = masini.at(i);
        tabelMasini->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m.getNrInmatriculare())));
        tabelMasini->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m.getProducator())));
        tabelMasini->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m.getModel())));
        tabelMasini->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(m.getTip())));
        tabelMasini->setItem(i, 4, new QTableWidgetItem(m.getInchiriata() ? "inchiriata" : "disponibila"));
    }

    tabelMasini->setSortingEnabled(true);  // reactivam sortarea
} 

/* Slot Add - foloseste datele din campurile de input
   @param: - ; @return: - */
void MainWindow::onAdd() {
    try {
        service.adaugaMasina(
            inputNrInm->text().toStdString(),
            inputProducator->text().toStdString(),
            inputModel->text().toStdString(),
            inputTip->text().toStdString(),
            inputInchiriata->isChecked()
        );
        reloadList();
        updateDynamicButtons();
        statusLabel->setText("Masina adaugata cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot Update - foloseste nrInm din input pentru a identifica masina
   @param: - ; @return: - */
void MainWindow::onUpdate() {
    try {
        service.modificaMasina(
            inputNrInm->text().toStdString(),
            inputProducator->text().toStdString(),
            inputModel->text().toStdString(),
            inputTip->text().toStdString()
        );
        reloadList();
        statusLabel->setText("Masina modificata cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
    updateDynamicButtons();
}

/* Slot Remove - foloseste nrInm din input
   @param: - ; @return: - */
void MainWindow::onRemove() {
    try {
        service.stergeMasina(inputNrInm->text().toStdString());
        reloadList();
        statusLabel->setText("Masina stearsa cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
    updateDynamicButtons();
}

/* Slot Inchiriere - marcheaza masina (nrInm din input) ca inchiriata
   @param: - ; @return: - */
void MainWindow::onInchiriere() {
    try {
        service.inchiriazaMasina(inputNrInm->text().toStdString());
        reloadList();
        statusLabel->setText("Masina inchiriata cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot Returnare - marcheaza masina ca disponibila
   @param: - ; @return: - */
void MainWindow::onReturnare() {
    try {
        service.returneazaMasina(inputNrInm->text().toStdString());
        reloadList();
        statusLabel->setText("Masina returnata cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot filtrare dupa producator - foloseste textul din inputProducator
   @param: - ; @return: - */
void MainWindow::onFilterProducator() {
    try {
        auto rez = service.filtreazaDupaProducator(inputProducator->text().toStdString());
        displayList(rez);
        statusLabel->setText(QString("Filtrare: %1 masini gasite").arg(rez.size()));
        statusLabel->setStyleSheet("color: blue;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot filtrare dupa tip
   @param: - ; @return: - */
void MainWindow::onFilterTip() {
    try {
        auto rez = service.filtreazaDupaTip(inputTip->text().toStdString());
        displayList(rez);
        statusLabel->setText(QString("Filtrare: %1 masini gasite").arg(rez.size()));
        statusLabel->setStyleSheet("color: blue;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot sortare dupa nr inmatriculare
   @param: - ; @return: - */
void MainWindow::onSortNr() {
    displayList(service.sorteazaDupaNrInmatriculare(true));
    statusLabel->setText("Sortat dupa nr. inmatriculare");
    statusLabel->setStyleSheet("color: blue;");
}

/* Slot sortare dupa tip
   @param: - ; @return: - */
void MainWindow::onSortTip() {
    displayList(service.sorteazaDupaTip(true));
    statusLabel->setText("Sortat dupa tip");
    statusLabel->setStyleSheet("color: blue;");
}

/* Slot sortare dupa producator + model
   @param: - ; @return: - */
void MainWindow::onSortProdModel() {
    displayList(service.sorteazaDupaProducatorModel(true));
    statusLabel->setText("Sortat dupa producator + model");
    statusLabel->setStyleSheet("color: blue;");
}

/* Slot afiseaza toate (resetare filtru/sortare)
   @param: - ; @return: - */
void MainWindow::onAfiseazaToate() {
    reloadList();
    statusLabel->setText("Afisate toate masinile");
    statusLabel->setStyleSheet("color: black;");
}

/* Slot Undo - apel polimorfic la service.undo()
   @param: - ; @return: - */
void MainWindow::onUndo() {
    try {
        service.undo();
        reloadList();
        statusLabel->setText("Undo aplicat cu succes!");
        statusLabel->setStyleSheet("color: green;");
    }
    catch (const MasinaException& e) {
        statusLabel->setText(QString("Eroare: ") + e.what());
        statusLabel->setStyleSheet("color: red;");
    }
}

/* Slot Raport - afiseaza dialog cu raportul dupa tip
   @param: - ; @return: - */
void MainWindow::onRaport() {
    auto raport = service.analizaMasiniDupaTip();
    if (raport.empty()) {
        QMessageBox::information(this, "Raport", "Nu exista masini in garaj!");
        return;
    }

    QString text = "Numar masini pe tip:\n\n";
    for (const auto& [tip, dto] : raport) {
        text += QString::fromStdString(tip) + " : " +
                QString::number(dto.aparitii) + " masini\n";
    }
    QMessageBox::information(this, "Raport pe tip", text);
}

/* Slot deschidere fereastra lista de spalare
   Construieste fereastra si o afiseaza ne-modal (poti folosi ambele in paralel)
   @param: - ; @return: - */
void MainWindow::onDeschideLista() {
    // Aceasta e a 2-a fereastra (cerinta: minim 2 ferestre)
    auto* washWin = new WashListWindow(service);
    washWin->setAttribute(Qt::WA_DeleteOnClose);  // se sterge automat la inchidere
    washWin->show();
}

/* Iteratia 4: deschide o instanta noua de CosCrud (cu tabel + butoane)
   Fiecare apasare creeaza o fereastra noua - se pot deschide multiple,
   toate inregistrate ca observatori la service prin modelul lor intern
   @param: - ; @return: - */
void MainWindow::onDeschideCosCRUD() {
    auto* fereastra = new CosCrud(service);
    fereastra->setAttribute(Qt::WA_DeleteOnClose);
    fereastra->show();
}

/* Iteratia 4: deschide o instanta noua de CosForme (cu desene)
   Fiecare apasare creeaza o fereastra noua, fiecare se inregistreaza ca
   observer la service in constructor si de-inregistreaza in destructor
   @param: - ; @return: - */
void MainWindow::onDeschideCosReadOnly() {
    auto* fereastra = new CosForme(service);
    fereastra->setAttribute(Qt::WA_DeleteOnClose);
    fereastra->show();
}

/* Slot apelat cand utilizatorul selecteaza o masina din lista
   Populeaza automat campurile cu datele masinii selectate
   @param: - ; @return: - */
void MainWindow::onItemSelected() {
    auto items = listaMasini->selectedItems();
    if (items.isEmpty()) return;

    // Extragem nr inmatriculare din textul afisat (e in format "[NR] | ...")
    QString text = items.first()->text();
    int posStart = text.indexOf('[');
    int posEnd = text.indexOf(']');
    if (posStart == -1 || posEnd == -1) return;

    QString nrInm = text.mid(posStart + 1, posEnd - posStart - 1);

    try {
        Masina m = service.cautaMasina(nrInm.toStdString());
        inputNrInm->setText(QString::fromStdString(m.getNrInmatriculare()));
        inputProducator->setText(QString::fromStdString(m.getProducator()));
        inputModel->setText(QString::fromStdString(m.getModel()));
        inputTip->setText(QString::fromStdString(m.getTip()));
        inputInchiriata->setChecked(m.getInchiriata());
    }
    catch (const MasinaException&) {
        // Daca nu gasim, lasam campurile cum sunt
    }
}
