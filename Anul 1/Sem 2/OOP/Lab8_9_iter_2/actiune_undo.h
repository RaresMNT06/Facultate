#pragma once
#include "repo_abstract.h"
#include "masini.h"

/* Clasa abstracta ActiuneUndo - interfata pentru toate actiunile reversibile
   Foloseste polimorfism: Service-ul tine o lista de pointeri la ActiuneUndo
   si apeleaza doUndo() polimorfic, fara sa stie ce tip concret e (UndoAdauga/Sterge/Modifica)
   Cerinta iteratia 2: clasa abstracta pentru undo, mostenire, polimorfism */
class ActiuneUndo {
public:
    /* Anuleaza efectul actiunii - reface situatia de dinainte
       Implementare specifica in clasele derivate
       @param: - ; @return: - */
    virtual void doUndo() = 0;

    /* Destructor virtual - obligatoriu pentru clase abstracte cu mostenire
       Asigura ca delete pe pointer la baza apeleaza destructorul corect
       (eviteaza memory leak la stergerea obiectelor derivate) */
    virtual ~ActiuneUndo() = default;
};

/* UndoAdauga - inverseaza o operatie de adaugare prin stergerea masinii
   Tine doar nrInmatriculare-ul (e de ajuns ca sa stergem masina) */
class UndoAdauga : public ActiuneUndo {
private:
    RepoAbstract& repo;             // referinta la repo (nu o detinem - alta clasa o gestioneaza)
    std::string nrInmatriculare;    // cheia masinii care a fost adaugata

public:
    /* Constructor
       @param repo: referinta la repository
       @param nrInmatriculare: cheia masinii adaugate ; @return: - */
    UndoAdauga(RepoAbstract& repo, const std::string& nrInmatriculare)
        : repo{ repo }, nrInmatriculare{ nrInmatriculare } {}

    /* Refacere: stergem masina pe care am adaugat-o
       @param: - ; @return: - */
    void doUndo() override {
        repo.sterge(nrInmatriculare);
    }
};

/* UndoSterge - inverseaza o operatie de stergere prin re-adaugarea masinii
   Tine TOATA masina (avem nevoie de toate datele ca s-o reconstruim) */
class UndoSterge : public ActiuneUndo {
private:
    RepoAbstract& repo;
    Masina masinaSteasa;            // copia masinii care a fost stearsa

public:
    /* Constructor
       @param repo: referinta la repository
       @param masinaSteasa: copia masinii inainte de stergere ; @return: - */
    UndoSterge(RepoAbstract& repo, const Masina& masinaSteasa)
        : repo{ repo }, masinaSteasa{ masinaSteasa } {}

    /* Refacere: adaugam la loc masina stearsa
       @param: - ; @return: - */
    void doUndo() override {
        repo.adauga(masinaSteasa);
    }
};

/* UndoModifica - inverseaza o modificare prin reaplicarea datelor vechi
   Tine masina ASA CUM ERA inainte de modificare (cu vechiul producator/model/tip/inchiriata) */
class UndoModifica : public ActiuneUndo {
private:
    RepoAbstract& repo;
    Masina masinaVeche;             // copia masinii inainte de modificare

public:
    /* Constructor
       @param repo: referinta la repository
       @param masinaVeche: copia masinii inainte de modificare ; @return: - */
    UndoModifica(RepoAbstract& repo, const Masina& masinaVeche)
        : repo{ repo }, masinaVeche{ masinaVeche } {}

    /* Refacere: aplicam datele vechi peste masina actuala
       Refacem si producator/model/tip si statusul de inchiriere
       @param: - ; @return: - */
    void doUndo() override {
        repo.modifica(masinaVeche.getNrInmatriculare(),
            masinaVeche.getProducator(),
            masinaVeche.getModel(),
            masinaVeche.getTip());
        repo.setStatusInchiriere(masinaVeche.getNrInmatriculare(),
            masinaVeche.getInchiriata());
    }
};
