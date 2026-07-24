#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/* de adaugat */
	//Complexitate: Theta(m) - alocare vectori si initializare pozitii libere
	m = 11;  //capacitate initiala (numar prim - mai bun pentru hash)
	nr = 0;
	elem = new TElem[m];
	urm = new int[m];
	//initial toate pozitiile sunt libere
	for (int i = 0; i < m; i++) {
		urm[i] = -2;
	}
}


bool Multime::adauga(TElem e) {
	/* de adaugat */
	//Complexitate: O(1) amortizat in caz mediu (cu hash bun si load factor < 0.7)
	//Caz defavorabil: O(n) - daca toate elementele cad in acelasi lant
	//functia hash: |e| % m
	int h = e % m;
	if (h < 0) h += m;

	//verific daca elementul exista deja parcurgand lantul de coliziuni
	int p = h;
	if (urm[p] != -2) {
		while (true) {
			if (elem[p] == e) return false;
			if (urm[p] == -1) break;          //ultimul din lant
			p = urm[p];
		}
		//p e acum ultimul element din lant - voi lega noul nod aici
	}

	//verific daca trebuie sa redimensionez tabela (load factor > 0.7)
	if ((nr + 1) * 10 > m * 7) {
		//redimensionez: dublez capacitatea si re-inserez toate elementele
		int mVechi = m;
		TElem* elemVechi = elem;
		int* urmVechi = urm;

		m = mVechi * 2 + 1;  //cresc capacitatea
		elem = new TElem[m];
		urm = new int[m];
		for (int i = 0; i < m; i++) urm[i] = -2;
		nr = 0;

		//re-inserez toate elementele din vechea tabela
		for (int i = 0; i < mVechi; i++) {
			if (urmVechi[i] != -2) {
				TElem el = elemVechi[i];
				//re-calculez hash si inserez in tabela noua
				int h2 = el % m;
				if (h2 < 0) h2 += m;
				if (urm[h2] == -2) {
					//pozitia de hash libera -> pun aici
					elem[h2] = el;
					urm[h2] = -1;
				} else {
					//coliziune -> parcurg lantul pana la final
					int q = h2;
					while (urm[q] != -1) q = urm[q];
					//caut o pozitie libera in tabela
					int liber = -1;
					for (int k = 0; k < m; k++) {
						if (urm[k] == -2) { liber = k; break; }
					}
					elem[liber] = el;
					urm[liber] = -1;
					urm[q] = liber;
				}
				nr++;
			}
		}
		delete[] elemVechi;
		delete[] urmVechi;

		//re-calculez pozitia de inserare pentru elementul nou e
		h = e % m;
		if (h < 0) h += m;
		p = h;
		if (urm[p] != -2) {
			while (urm[p] != -1) p = urm[p];
		}
	}

	if (urm[h] == -2) {
		//pozitia de hash e libera -> pun elementul direct aici
		elem[h] = e;
		urm[h] = -1;
	} else {
		int liber = -1;
		for (int k = 0; k < m; k++) {
			if (urm[k] == -2) { liber = k; break; }
		}
		elem[liber] = e;
		urm[liber] = -1;
		urm[p] = liber;  //leg noul nod la finalul lantului
	}
	nr++;
	return true;
}


bool Multime::sterge(TElem e) {
	/* de adaugat */
	//Complexitate: O(1) amortizat in caz mediu (cu hash bun si load factor < 0.7)
	//Caz defavorabil: O(n) - daca toate elementele cad in acelasi lant
	int h = e % m;
	if (h < 0) h += m;

	if (urm[h] == -2) return false;  //pozitia de hash e libera -> elementul nu exista

	//caut elementul in lantul de coliziuni, retinand si predecesorul
	int p = h;
	int pred = -1;
	while (p != -1 && elem[p] != e) {
		pred = p;
		p = urm[p];
	}
	if (p == -1) return false;  //elementul nu exista

	//am gasit elementul la pozitia p
	if (pred == -1) {
		//p e capul lantului (pozitia de hash h)
		if (urm[p] == -1) {
			//e singurul element din lant -> marchez pozitia ca libera
			urm[p] = -2;
		} else {
			//mai sunt elemente in lant -> mut primul element urmator pe pozitia h
			int q = urm[p];
			elem[p] = elem[q];
			urm[p] = urm[q];
			urm[q] = -2;  //elibereaza pozitia q
		}
	} else {
		//p e in mijlocul/finalul lantului -> doar releg si elibereaza
		urm[pred] = urm[p];
		urm[p] = -2;
	}
	nr--;
	return true;
}


bool Multime::cauta(TElem e) const {
	/* de adaugat */
	//Complexitate: O(1) amortizat in caz mediu (cu hash bun si load factor < 0.7)
	//Caz defavorabil: O(n) - daca toate elementele cad in acelasi lant
	int h = e % m;
	if (h < 0) h += m;

	if (urm[h] == -2) return false;

	int p = h;
	while (p != -1) {
		if (elem[p] == e) return true;
		p = urm[p];
	}
	return false;
}


int Multime::dim() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return nr;
}

bool Multime::vida() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return nr == 0;
}


Multime::~Multime() {
	/* de adaugat */
	//Complexitate: Theta(m) - 2 apeluri delete[]
	delete[] elem;
	delete[] urm;
}



IteratorMultime Multime::iterator()  {
	//Complexitate: O(m) - constructorul iteratorului cauta prima pozitie ocupata
	return IteratorMultime(*this);
}