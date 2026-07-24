#pragma once

#include "service.h"
#include "observer.h"
#include <QAbstractTableModel>

/* Modelul Qt pentru lista de spalare (cosul)
   Cerinta iteratia 4 - punctul 2: folosim QTableView cu un model propriu

   Are 2 roluri:
   1. Model Qt (extinde QAbstractTableModel) - furnizeaza datele catre QTableView
   2. Observer - e notificat de Service cand cosul se modifica

   Cand Service apeleaza notifyAll(), CosModel primeste update() si emite
   semnalul layoutChanged() care face QTableView sa se redeseneze automat. */
class CosModel : public QAbstractTableModel, public Observer {
    Q_OBJECT  // macro pentru clase Qt cu signals/slots

private:
    Service& service;  // referinta la service - sursa de date

public:
    /* Constructor - primeste service-ul si se inregistreaza ca observer
       @param service: referinta la service ; @param parent: parintele Qt
       @return: - */
    explicit CosModel(Service& service, QObject* parent = nullptr);

    /* Destructor - se de-inregistreaza din lista de observatori
       Important: fara asta, Service ar pastra un pointer la obiect distrus
       @param: - ; @return: - */
    ~CosModel() override;

    /* Numarul de randuri in tabel = numarul de masini din cos
       Apelata automat de Qt cand redeseneaza tabelul
       @param parent: parametrul Qt (neutilizat - tabel plat)
       @return: numarul de masini din cos */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /* Numarul de coloane in tabel (fix 4: NrInm, Producator, Model, Tip)
       @param parent: parametrul Qt (neutilizat)
       @return: 4 */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /* Furnizeaza datele pentru o celula specifica (rand, coloana)
       Apelata de Qt pentru fiecare celula vizibila
       @param index: pozitia celulei (rand+coloana)
       @param role: rolul (Display, Edit, etc. - folosim doar DisplayRole)
       @return: QVariant cu valoarea afisata */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /* Furnizeaza datele pentru header (numele coloanelor)
       @param section: indexul coloanei/randului
       @param orientation: orizontala (header sus) sau verticala (header stanga)
       @param role: rolul ; @return: QVariant cu textul header-ului */
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;

    /* Override pentru Observer::update() - apelata de Service la modificarea cosului
       Emite semnalele Qt care fac view-urile asociate sa se redeseneze automat
       @param: - ; @return: - */
    void update() override;
};
