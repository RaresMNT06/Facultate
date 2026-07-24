#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	/* de adaugat */
	//O(1)
	curent = m.cap;
}


void IteratorMultime::prim() {
	/* de adaugat */
	//O(1)
	curent = multime.cap;
}


void IteratorMultime::urmator() {
	/* de adaugat */
	//O(1)
	if (curent == nullptr)
		throw std::exception();
	curent = curent->urm;
}


TElem IteratorMultime::element() const {
	/* de adaugat */
	//O(1)
	if (curent == nullptr)
		throw std::exception();
	return curent->elem_c;
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	//O(1)
	return curent != nullptr;
}
