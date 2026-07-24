#pragma once

/* Clasa abstracta pentru pattern-ul Observer
   Orice fereastra care vrea sa fie notificata cand se schimba cosul
   trebuie sa mosteneasca din aceasta clasa si sa implementeze update().

   Cum functioneaza:
   - Service-ul detine o lista de Observer*
   - Cand cosul se modifica, Service apeleaza notifyAll() care apeleaza
     update() pe fiecare observer
   - Fiecare fereastra in update() decide cum reactioneaza:
     - CosCrud: reincarca modelul/tabelul
     - CosForme: redeseneaza (apeleaza repaint) */
class Observer {
public:
    /* Destructor virtual obligatoriu pentru clasa abstracta cu mostenire
       @param: - ; @return: - */
    virtual ~Observer() = default;

    /* Metoda pur virtuala apelata cand Service notifica modificarea
       Fiecare clasa derivata isi implementeaza propria logica de actualizare
       @param: - ; @return: - */
    virtual void update() = 0;
};
