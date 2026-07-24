#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;


bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

Multime::Multime() {
	/* de adaugat */
	//Complexitate: Theta(1)
	rad = nullptr;
	nr = 0;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	//Complexitate: O(h), unde h = inaltimea arborelui
	//in caz mediu O(log n), in caz defavorabil O(n) (arbore degenerat in lista)
	//caut locul de inserare iterativ (fara recursie, evit stack overflow)
	if (rad == nullptr) {
		rad = new Nod{elem, nullptr, nullptr};
		nr++;
		return true;
	}
	Nod* p = rad;
	while (true) {
		//verific daca elementul exista deja: rel(elem, p->info) && rel(p->info, elem) <=> elem == p->info
		if (rel(elem, p->info) && rel(p->info, elem)) {
			return false;  //elementul exista deja, nu se adauga
		}
		if (rel(elem, p->info)) {
			//elem <= p->info, dar nu sunt egale => merg in subarborele stang
			if (p->st == nullptr) {
				p->st = new Nod{elem, nullptr, nullptr};
				nr++;
				return true;
			}
			p = p->st;
		} else {
			//elem > p->info => merg in subarborele drept
			if (p->dr == nullptr) {
				p->dr = new Nod{elem, nullptr, nullptr};
				nr++;
				return true;
			}
			p = p->dr;
		}
	}
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	//Complexitate: O(h), unde h = inaltimea arborelui
	//caut nodul de sters retinand si parintele si o indicatie daca e copil stang/drept
	Nod* parinte = nullptr;
	Nod* p = rad;
	bool estStang = false;  //true daca p e copilul stang al parintelui
	while (p != nullptr) {
		if (rel(elem, p->info) && rel(p->info, elem)) break;  //am gasit nodul de sters
		parinte = p;
		if (rel(elem, p->info)) {
			p = p->st;
			estStang = true;
		} else {
			p = p->dr;
			estStang = false;
		}
	}
	if (p == nullptr) return false;  //elementul nu exista

	//3 cazuri la stergere in ABC:
	if (p->st == nullptr && p->dr == nullptr) {
		//CAZ 1: nodul de sters e frunza
		if (parinte == nullptr) {
			rad = nullptr;
		} else if (estStang) {
			parinte->st = nullptr;
		} else {
			parinte->dr = nullptr;
		}
		delete p;
	} else if (p->st == nullptr || p->dr == nullptr) {
		//CAZ 2: nodul are un singur copil
		Nod* copil = (p->st != nullptr) ? p->st : p->dr;
		if (parinte == nullptr) {
			rad = copil;
		} else if (estStang) {
			parinte->st = copil;
		} else {
			parinte->dr = copil;
		}
		delete p;
	} else {
		//CAZ 3: nodul are doi copii
		//caut succesorul in-ordine (cel mai mic element din subarborele drept)
		Nod* parinteSucc = p;
		Nod* succ = p->dr;
		while (succ->st != nullptr) {
			parinteSucc = succ;
			succ = succ->st;
		}
		//copiez valoarea succesorului in p si sterg fizic succesorul (care are cel mult un copil drept)
		p->info = succ->info;
		if (parinteSucc == p) {
			//succ era chiar p->dr (nu avea copil stang)
			parinteSucc->dr = succ->dr;
		} else {
			parinteSucc->st = succ->dr;
		}
		delete succ;
	}
	nr--;
	return true;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	//Complexitate: O(h), unde h = inaltimea arborelui
	Nod* p = rad;
	while (p != nullptr) {
		if (rel(elem, p->info) && rel(p->info, elem)) return true;  //gasit
		if (rel(elem, p->info)) {
			p = p->st;
		} else {
			p = p->dr;
		}
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

IteratorMultime Multime::iterator() const {
	//Complexitate: O(h) - iteratorul coboara pe ramura stanga pana la cel mai mic element
	return IteratorMultime(*this);
}


Multime::~Multime() {
	/* de adaugat */
	//Complexitate: Theta(n) - sterg toate nodurile arborelui
	//folosesc parcurgere iterativa cu stiva ca sa evit stack overflow
	if (rad == nullptr) return;
	Nod** stiva = new Nod*[nr];
	int varf = 0;
	stiva[varf++] = rad;
	while (varf > 0) {
		Nod* p = stiva[--varf];
		if (p->st != nullptr) stiva[varf++] = p->st;
		if (p->dr != nullptr) stiva[varf++] = p->dr;
		delete p;
	}
	delete[] stiva;
}