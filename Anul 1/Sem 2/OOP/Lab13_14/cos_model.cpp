#include "cos_model.h"
#include "masini.h"

/* Constructor - inregistreaza modelul ca observer la service
   @param service: referinta la service ; @param parent: parintele Qt
   @return: - */
CosModel::CosModel(Service& service, QObject* parent)
    : QAbstractTableModel(parent), service{ service } {
    // Ne inregistram ca observer - service ne va notifica la fiecare modificare
    service.addObserver(this);
}

/* Destructor - de-inregistreaza modelul din lista de observatori
   @param: - ; @return: - */
CosModel::~CosModel() {
    service.removeObserver(this);
}

/* Numarul de randuri = numarul de masini din cos
   @param parent: neutilizat ; @return: nr masini */
int CosModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(service.lungimeListaSpalate());
}

/* Numarul de coloane = 4 (NrInm, Producator, Model, Tip)
   @param parent: neutilizat ; @return: 4 */
int CosModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 4;
}

/* Furnizeaza datele pentru o celula
   @param index: pozitia (rand, coloana) ; @param role: rolul
   @return: QVariant cu textul afisat */
QVariant CosModel::data(const QModelIndex& index, int role) const {
    // Verificam ca indexul e valid
    if (!index.isValid())
        return QVariant();

    // Folosim doar DisplayRole (pentru text afisat in celula)
    if (role != Qt::DisplayRole)
        return QVariant();

    // Verificam ca randul e in limite
    auto masini = service.getListaSpalate();
    if (index.row() >= static_cast<int>(masini.size()))
        return QVariant();

    const Masina& m = masini.at(index.row());

    // Returnam valoarea coloanei corespunzatoare
    switch (index.column()) {
    case 0: return QString::fromStdString(m.getNrInmatriculare());
    case 1: return QString::fromStdString(m.getProducator());
    case 2: return QString::fromStdString(m.getModel());
    case 3: return QString::fromStdString(m.getTip());
    default: return QVariant();
    }
}

/* Furnizeaza header-ele (numele coloanelor)
   @param section: indexul ; @param orientation: orizontal/vertical
   @param role: rolul ; @return: textul header-ului */
QVariant CosModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    // Header orizontal (sus) - numele coloanelor
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Nr. inmatriculare";
        case 1: return "Producator";
        case 2: return "Model";
        case 3: return "Tip";
        default: return QVariant();
        }
    }

    // Header vertical (stanga) - numarul randului
    return section + 1;
}

/* Observer::update() - apelata de Service la modificarea cosului
   Emitem semnale Qt care fac view-urile sa se redeseneze automat
   beginResetModel/endResetModel = anunta toate view-urile asociate ca
   intreaga structura s-a schimbat si trebuie refacuta complet
   @param: - ; @return: - */
void CosModel::update() {
    beginResetModel();
    endResetModel();
}
