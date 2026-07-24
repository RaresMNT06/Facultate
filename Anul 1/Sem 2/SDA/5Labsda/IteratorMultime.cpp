#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	/* de adaugat */
	//Complexitate: O(h) - coboara pe ramura stanga pana la cel mai mic element
	//pornesc de la radacina si cobor pe stanga pana cel mai stang nod
	Multime::Nod* p = m.rad;
	if (p == nullptr) {
		curent = nullptr;
	} else {
		while (p->st != nullptr) p = p->st;
		curent = p;
	}
}

TElem IteratorMultime::element() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	if (curent == nullptr) throw std::exception();
	return curent->info;
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return curent != nullptr;
}

void IteratorMultime::urmator() {
	/* de adaugat */
	//Complexitate: O(h), amortizat O(1) pe ansamblul parcurgerii complete
	//caut succesorul in-ordine al nodului curent in ABC
	if (curent == nullptr) throw std::exception();
	if (curent->dr != nullptr) {
		//caz 1: are subarbore drept => succesorul e cel mai stang nod din subarborele drept
		Multime::Nod* p = curent->dr;
		while (p->st != nullptr) p = p->st;
		curent = p;
	} else {
		//caz 2: nu are subarbore drept => caut primul stramos pentru care curent e in subarborele stang
		//pornesc cautarea de la radacina
		Multime::Nod* succ = nullptr;
		Multime::Nod* p = mult.rad;
		while (p != curent) {
			if (rel(curent->info, p->info)) {
				succ = p;
				p = p->st;
			} else {
				p = p->dr;
			}
		}
		curent = succ;
	}
}

void IteratorMultime::prim() {
	/* de adaugat */
	//Complexitate: O(h)
	Multime::Nod* p = mult.rad;
	if (p == nullptr) {
		curent = nullptr;
	} else {
		while (p->st != nullptr) p = p->st;
		curent = p;
	}
}