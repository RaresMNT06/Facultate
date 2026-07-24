#include "IteratorValori.h"
#include "MD.h"
#include <exception>

using namespace std;

IteratorValori::IteratorValori(const MD& _md, TCheie k): md(_md), cheia(k) {
    //Complexitate: O(n_chei) - cauta cheia k in LSI exterioara
    //caut cheia k in LSI exterioara
    int p = _md.prim;
    while (p != -1 && _md.cheie[p] != k)
        p = _md.urmC[p];

    //daca cheia exista, iteratorul porneste pe prima valoare asociata
    //altfel, iteratorul e nevalid (curentVal = -1)
    if (p != -1)
        curentVal = _md.primVal[p];
    else
        curentVal = -1;
}

TValoare IteratorValori::element() const {
    //Complexitate: Theta(1)
    if (curentVal == -1)
        throw std::exception();
    return md.val[curentVal];
}

bool IteratorValori::valid() const {
    //Complexitate: Theta(1)
    return curentVal != -1;
}

void IteratorValori::urmator() {
    //Complexitate: Theta(1)
    if (curentVal == -1)
        throw std::exception();
    curentVal = md.urmV[curentVal];
}

void IteratorValori::prim() {
    //Complexitate: O(n_chei) - re-cauta cheia in LSI exterioara
    //re-caut cheia in LSI exterioara
    int p = md.prim;
    while (p != -1 && md.cheie[p] != cheia)
        p = md.urmC[p];

    if (p != -1)
        curentVal = md.primVal[p];
    else
        curentVal = -1;
}