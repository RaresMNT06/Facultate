#pragma once
#include "MD.h"

class MD;

class IteratorValori
{
    friend class MD;

private:

    //constructorul primeste o referinta catre Container si o cheie
    //iteratorul va referi prima valoare asociata cheii k
    //daca cheia k nu exista, iteratorul va fi nevalid imediat dupa creare
    IteratorValori(const MD& c, TCheie k);

    //contine o referinta catre containerul pe care il itereaza
    const MD& md;

    TCheie cheia;
    int curentVal;

public:

    //reseteaza pozitia iteratorului la prima valoare a cheii
    void prim();

    //muta iteratorul pe valoarea urmatoare
    // arunca exceptie daca iteratorul nu e valid
    void urmator();

    //verifica daca iteratorul e valid
    bool valid() const;

    //returneaza valoarea curenta
    //arunca exceptie daca iteratorul nu e valid
    TValoare element() const;
};