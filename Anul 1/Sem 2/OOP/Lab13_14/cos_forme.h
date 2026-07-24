#pragma once

#include "service.h"
#include "observer.h"
#include <QWidget>

/* Fereastra ReadOnly pentru cos - cerinta iteratia 4
   Spre deosebire de CosCrud, aceasta fereastra NU afiseaza text,
   ci DESENEAZA figuri geometrice (cercuri colorate) la pozitii random.
   Numarul de cercuri desenate = numarul de masini din cos.

   Cum functioneaza:
   1. Suprascriem paintEvent(QPaintEvent*) - apelat automat de Qt cand
      fereastra trebuie redesenata
   2. In paintEvent folosim QPainter pentru a desena
   3. Implementam Observer::update() - cand cosul se schimba, apelam
      update() (metoda Qt) care forteaza paintEvent sa fie reapelat

   Atentie la conflict de nume: Observer are update() iar QWidget are update()
   QWidget::update() = forteaza redesenarea
   Observer::update() = metoda apelata cand cosul se modifica
   Le rezolvam prin redenumirea uneia - facem update() din Observer sa
   apeleze repaint() pe fereastra */
class CosForme : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;

protected:
    /* Suprascris din QWidget - apelat automat de Qt cand fereastra
       trebuie redesenata (la creare, la resize, dupa repaint, etc.)
       @param event: evenimentul de paint (neutilizat aici)
       @return: - */
    void paintEvent(QPaintEvent* event) override;

public:
    /* Constructor - se inregistreaza ca observer la service
       @param service: referinta la service ; @param parent: parintele Qt
       @return: - */
    explicit CosForme(Service& service, QWidget* parent = nullptr);

    /* Destructor - se de-inregistreaza din lista de observatori
       @param: - ; @return: - */
    ~CosForme() override;

    /* Override Observer::update() - apelata de Service la modificarea cosului
       Cere Qt sa redeseneze fereastra (apeleaza paintEvent)
       @param: - ; @return: - */
    void update() override;
};
