#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;
class IteratorValori;

class MD
{
    friend class IteratorMD;
    friend class IteratorValori;

private:
    /* aici e reprezentarea */
    //LSI exterioara - chei distincte (inlantuiri pe tablou dinamic)
    TCheie* cheie;
    int* primVal;
    int* urmC;
    int prim;
    int primLiberC;
    int cpC;

    //LSI interioara - valorile (inlantuiri pe tablou dinamic)
    TValoare* val;
    int* urmV;
    int primLiberV;
    int cpV;

    int nr;

public:
    // constructorul implicit al MultiDictionarului
    MD();

    // adauga o pereche (cheie, valoare) in MD
    void adauga(TCheie c, TValoare v);

    //cauta o cheie si returneaza vectorul de valori asociate
    vector<TValoare> cauta(TCheie c) const;

    //sterge o cheie si o valoare
    //returneaza adevarat daca s-a gasit cheia si valoarea de sters
    bool sterge(TCheie c, TValoare v);

    //returneaza numarul de perechi (cheie, valoare) din MD
    int dim() const;

    //verifica daca MultiDictionarul e vid
    bool vid() const;

    // se returneaza iterator pe MD
    IteratorMD iterator() const;

    // creeaza un iterator peste valorile asociate cheii k. In cazul in care k nu este in multidictionar,
    // iteratorul va fi nevalid imediat dupa creare. In caz contrar, elementul curent este prima valoare asociata cheii
    IteratorValori iterator(TCheie k) const;

    // destructorul MultiDictionarului
    ~MD();



};