#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime( Multime& m) : multime(m){
	/* de adaugat */
	//Complexitate: O(m) - caut prima pozitie ocupata in tabela
	curent = -1;
	for (int i = 0; i < multime.m; i++) {
		if (multime.urm[i] != -2) {
			curent = i;
			break;
		}
	}
}


void IteratorMultime::prim() {
	/* de adaugat */
	//Complexitate: O(m) - caut prima pozitie ocupata in tabela
	curent = -1;
	for (int i = 0; i < multime.m; i++) {
		if (multime.urm[i] != -2) {
			curent = i;
			break;
		}
	}
}


void IteratorMultime::urmator() {
	/* de adaugat */
	//Complexitate: O(m) in caz defavorabil
	//O(m/n) amortizat pe ansamblul iterarii complete (parcurgere totala = Theta(m))
	if (curent == -1) throw std::exception();
	//caut urmatoarea pozitie ocupata
	int nou = -1;
	for (int i = curent + 1; i < multime.m; i++) {
		if (multime.urm[i] != -2) {
			nou = i;
			break;
		}
	}
	curent = nou;
}


TElem IteratorMultime::element() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	if (curent == -1) throw std::exception();
	return multime.elem[curent];
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return curent != -1;
}

// Complexitate: O(n) în caz defavorabil (din cauza stergerii), O(1) amortizat pe caz mediu
TElem IteratorMultime::elimina() {

	if (!valid()) {
		throw std::exception();
	}

	// Salvăm elementul curent pentru a-l putea returna la final
	TElem elementEliminat = multime.elem[curent];

	multime.sterge(elementEliminat);

	if (multime.urm[curent] == -2) {
		int nou = -1;
		for (int i = curent + 1; i < multime.m; i++) {
			if (multime.urm[i] != -2) {
				nou = i;
				break;
			}
		}
		curent = nou;
	}

	return elementEliminat;
}