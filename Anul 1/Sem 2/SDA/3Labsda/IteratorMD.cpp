#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	/* de adaugat */
	//Complexitate: Theta(1)
	curentCheie = _md.prim;
	if (curentCheie != -1)
		curentVal = _md.primVal[curentCheie];
	else
		curentVal = -1;
}

TElem IteratorMD::element() const{
	/* de adaugat */
	//Complexitate: Theta(1)
	return pair <TCheie, TValoare>  (md.cheie[curentCheie], md.val[curentVal]);
}

bool IteratorMD::valid() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return curentCheie != -1;
}

void IteratorMD::urmator() {
	/* de adaugat */
	//Complexitate: Theta(1)
	curentVal = md.urmV[curentVal];
	if (curentVal == -1) {
		curentCheie = md.urmC[curentCheie];
		if (curentCheie != -1)
			curentVal = md.primVal[curentCheie];
	}
}

void IteratorMD::prim() {
	/* de adaugat */
	//Complexitate: Theta(1)
	curentCheie = md.prim;
	if (curentCheie != -1)
		curentVal = md.primVal[curentCheie];
	else
		curentVal = -1;
}