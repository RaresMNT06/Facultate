#pragma once

#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

/* Fereastra principala a aplicatiei - gestioneaza masinile
   Toate functionalitatile din UI-ul consolei sunt accesibile aici prin butoane:
   CRUD (Add/Update/Remove), filtrare, sortare, inchiriere/returnare, undo, raport.
   Lista de spalare se deschide intr-o fereastra separata (WashListWindow). */
class MainWindow : public QWidget {
    Q_OBJECT  // macro obligatoriu pentru clasele Qt cu signals/slots

private:
    Service& service;  // referinta la service - nu detinem service-ul

    // ===== UI elements =====
    // Lista de masini (centru-stanga)
    QListWidget* listaMasini;
    QTableWidget* tabelMasini;

    // Campuri de input (dreapta sus) - pentru add/update
    QLineEdit* inputNrInm;
    QLineEdit* inputProducator;
    QLineEdit* inputModel;
    QLineEdit* inputTip;
    QCheckBox* inputInchiriata;

    // Butoane de actiune (dreapta mijloc)
    QPushButton* btnAdd;
    QPushButton* btnUpdate;
    QPushButton* btnRemove;
    QPushButton* btnInchiriere;
    QPushButton* btnReturnare;

    // Butoane de filtrare/sortare (dreapta jos)
    QPushButton* btnFilterProducator;
    QPushButton* btnFilterTip;
    QPushButton* btnSortNr;
    QPushButton* btnSortTip;
    QPushButton* btnSortProdModel;

    // Butoane utilitare (jos)
    QPushButton* btnAfiseazaToate;
    QPushButton* btnUndo;
    QPushButton* btnRaport;
    QPushButton* btnLista;          // deschide fereastra de lista de spalare (vechi)

    // Iteratia 4: butoane noi pentru ferestrele cu Observer Pattern
    QPushButton* btnCosCRUD;        // deschide CosCrud (tabel + butoane)
    QPushButton* btnCosReadOnly;    // deschide CosForme (cercuri desenate)

    // Eticheta status (jos de tot) - afiseaza mesaje de info/eroare
    QLabel* statusLabel;

    /* Construieste interfata grafica - layout cu butoane si campuri
       Apelata din constructor
       @param: - ; @return: - */
    void initUI();

    /* Conecteaza signals-urile butoanelor la slot-urile corespunzatoare
       Apelata din constructor dupa initUI()
       @param: - ; @return: - */
    void connectSignals();

    /* Reincarca lista de masini din service si o afiseaza in QListWidget
       Apelata dupa fiecare operatie care modifica datele
       @param: - ; @return: - */
    void reloadList();

    /* Reincarca lista cu un vector specific (pentru afisarea filtrarilor/sortarilor)
       @param masini: vectorul de masini de afisat ; @return: - */
    void displayList(const std::vector<Masina>& masini);

    
    QGridLayout* tipLayout; 
    void updateDynamicButtons(); 

public:
    /* Constructor - primeste service-ul si construieste UI-ul
       @param service: referinta la service ; @param parent: parintele Qt (default null)
       @return: - */
    explicit MainWindow(Service& service, QWidget* parent = nullptr);

private slots:
    // Slot-urile sunt metode private speciale conectate la butoane (signals)

    /* Slot pentru butonul Add - adauga o masina noua */
    void onAdd();

    /* Slot pentru butonul Update - modifica masina selectata */
    void onUpdate();

    /* Slot pentru butonul Remove - sterge masina selectata */
    void onRemove();

    /* Slot pentru butonul Inchiriere - marcheaza masina selectata ca inchiriata */
    void onInchiriere();

    /* Slot pentru butonul Returnare - marcheaza masina selectata ca disponibila */
    void onReturnare();

    /* Slot pentru filtrare dupa producator - foloseste textul din inputProducator */
    void onFilterProducator();

    /* Slot pentru filtrare dupa tip - foloseste textul din inputTip */
    void onFilterTip();

    /* Slot pentru sortare dupa nr inmatriculare (crescator) */
    void onSortNr();

    /* Slot pentru sortare dupa tip (crescator) */
    void onSortTip();

    /* Slot pentru sortare dupa producator + model (crescator) */
    void onSortProdModel();

    /* Slot pentru afisarea tuturor masinilor (resetare filtru/sortare) */
    void onAfiseazaToate();

    /* Slot pentru Undo - apeleaza service.undo() si actualizeaza lista */
    void onUndo();

    /* Slot pentru afisarea raportului dupa tip (intr-un dialog separat) */
    void onRaport();

    /* Slot pentru deschiderea ferestrei de lista de spalare */
    void onDeschideLista();

    /* Iteratia 4: deschide o noua instanta CosCrud (cu tabel + butoane)
       La fiecare apasare se deschide o fereastra NOUA - se pot avea multiple
       deschise simultan, toate sincronizate prin Observer Pattern */
    void onDeschideCosCRUD();

    /* Iteratia 4: deschide o noua instanta CosForme (cu desene)
       Acelasi principiu - multiple ferestre posibile, toate sincronizate */
    void onDeschideCosReadOnly();

    /* Slot apelat cand utilizatorul selecteaza o masina din lista
       Populeaza automat campurile de input cu datele masinii selectate
       Util pentru update si remove (nu mai trebuie sa scrie nrInm) */
    void onItemSelected();
};
