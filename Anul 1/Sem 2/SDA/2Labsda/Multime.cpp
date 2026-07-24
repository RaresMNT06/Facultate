#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/* de adaugat */
	//O(1)
	cap = nullptr;
	coada = nullptr;
	nr = 0;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	//O(n)
	if (cauta(elem))
		return false;

	Nod* nou = new Nod;
	nou->elem_c = elem;
	nou->urm = nullptr;
	nou->prec = coada;

	if (coada == nullptr) {
		cap = nou;
	}else {
		coada->urm = nou;
	}
	coada = nou;
	nr++;

	return true;
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	//O(n)
	Nod* p = cap;
	while (p != nullptr && p->elem_c != elem)
		p = p->urm;

	if (p == nullptr)
		return false;

	if (p->prec != nullptr)
		p->prec->urm = p->urm;
	else
		cap = p->urm;

	if (p->urm != nullptr)
		p->urm->prec = p->prec;
	else
		coada = p->prec;

	delete p;
	nr--;
	return true;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	//O(n)
	Nod* p = cap;
	while (p != nullptr) {
		if (p->elem_c == elem)
			return true;
		p = p->urm;
	}
	return false;
}


int Multime::dim() const {
	/* de adaugat */
	//O(1)
	return nr;
}

bool Multime::vida() const {
	/* de adaugat */
	//O(1)
	if (nr != 0)
		return false;
	return true;
}


Multime::~Multime() {
	/* de adaugat */
	//O(n)
	Nod* p = cap;
	while (p != nullptr) {
		Nod* urmator = p->urm;
		delete p;
		p = urmator;
	}
}

int Multime::diferentaMaxMin() const {
	//O(n)
	if (nr==0)
		return -1;

	Nod* p = cap;
	TElem maxim = p->elem_c;
	TElem minim = p->elem_c;

	p = p-> urm;
	while (p != nullptr) {
		if (p->elem_c > maxim)
			maxim = p->elem_c;
		if (p->elem_c < minim)
			minim = p->elem_c;
		p = p-> urm;
	}
	return maxim - minim;

}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

