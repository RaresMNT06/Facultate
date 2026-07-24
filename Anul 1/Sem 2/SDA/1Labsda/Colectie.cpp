#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
	/* de adaugat */
	// Initializam capacitatile initiale si dimensiunile la 0
	// Alocam memorie pentru vectorul D (elemente distincte) si P (pozitii in D)
	capD = 10;
	capP = 10;
	dimD = 0;
	dimP = 0;
	D = new TElem[capD];
	P = new int[capP];
}

void Colectie::resizeD() {
	// Dublam capacitatea lui D si copiem elementele existente in noul vector
	capD *= 2;
	TElem* newD = new TElem[capD];
	for (int i = 0; i < dimD; i++)
		newD[i] = D[i];
	delete[] D;
	D = newD;
}

void Colectie::resizeP() {
	// Dublam capacitatea lui P si copiem elementele existente in noul vector
	capP *= 2;
	int* newP = new int[capP];
	for (int i = 0; i < dimP; i++)
		newP[i] = P[i];
	delete[] P;
	P = newP;
}

void Colectie::adauga(TElem elem) {
	/* de adaugat */
	// Cautam daca elem exista deja in D
	// Daca nu exista, il adaugam in D si retinem indexul sau
	// In ambele cazuri, adaugam indexul elementului din D la sfarsitul lui P
	int posInD = -1;
	for (int i = 0; i < dimD; i++) {
		if (D[i] == elem) {
			posInD = i;
			break;
		}
	}

	if (posInD == -1) {
		if (dimD == capD)
			resizeD();
		D[dimD] = elem;
		posInD = dimD;
		dimD++;
	}

	if (dimP == capP)
		resizeP();
	P[dimP] = posInD;
	dimP++;
}


bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	// Cautam elem in D; daca nu exista, returnam false
	// Gasim prima aparitie a indexului sau in P si o stergem (shift stanga)
	// Daca indexul nu mai apare deloc in P, stergem si elem din D
	// si decrementam toti indicii din P mai mari decat cel sters
	int posInD = -1;
	for (int i = 0; i < dimD; i++) {
		if (D[i] == elem) {
			posInD = i;
			break;
		}
	}

	if (posInD == -1)
		return false;

	int posInP = -1;
	for (int i = 0; i < dimP; i++) {
		if (P[i] == posInD) {
			posInP = i;
			break;
		}
	}

	if (posInP == -1)
		return false;

	for (int i = posInP; i < dimP - 1; i++)
		P[i] = P[i + 1];
	dimP--;

	bool stillExists = false;
	for (int i = 0; i < dimP; i++) {
		if (P[i] == posInD) {
			stillExists = true;
			break;
		}
	}

	if (!stillExists) {
		for (int i = posInD; i < dimD - 1; i++)
			D[i] = D[i + 1];
		dimD--;

		for (int i = 0; i < dimP; i++) {
			if (P[i] > posInD)
				P[i]--;
		}
	}

	return true;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	// Parcurgem D si returnam true daca gasim elementul
	for (int i = 0; i < dimD; i++) {
		if (D[i] == elem)
			return true;
	}
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	// Cautam indexul lui elem in D
	// Daca nu exista, returnam 0
	// Altfel numaram de cate ori apare acel index in P
	int posInD = -1;
	for (int i = 0; i < dimD; i++) {
		if (D[i] == elem) {
			posInD = i;
			break;
		}
	}

	if (posInD == -1)
		return 0;

	int count = 0;
	for (int i = 0; i < dimP; i++) {
		if (P[i] == posInD)
			count++;
	}
	return count;
}


int Colectie::dim() const {
	/* de adaugat */
	// Numarul total de elemente este dimensiunea lui P
	return dimP;
}


bool Colectie::vida() const {
	/* de adaugat */
	// Colectia e vida daca nu exista niciun element in P
	return dimP == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	// Eliberam memoria alocata pentru D si P
	delete[] D;
	delete[] P;
}