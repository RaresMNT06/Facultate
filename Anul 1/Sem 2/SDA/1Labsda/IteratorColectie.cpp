#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

using namespace std;


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	/* de adaugat */
	// Initializam iteratorul pe primul element (pozitia 0 in P)
	current = 0;
}

void IteratorColectie::prim() {
	/* de adaugat */
	// Resetam iteratorul la inceputul colectiei (pozitia 0 in P)
	current = 0;
}


void IteratorColectie::urmator() {
	/* de adaugat */
	// Daca iteratorul nu e valid aruncam exceptie
	// Altfel avansam la urmatoarea pozitie din P
	if (!valid())
		throw exception();
	current++;
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	// Iteratorul e valid cat timp current e in interiorul lui P
	return current < col.dimP;
}


TElem IteratorColectie::element() const {
	/* de adaugat */
	// Daca iteratorul nu e valid aruncam exceptie
	// Returnam elementul din D indicat de P[current]
	if (!valid())
		throw exception();
	return col.D[col.P[current]];
}