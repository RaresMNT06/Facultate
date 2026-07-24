#include "MD.h"
#include "IteratorMD.h"
#include "IteratorValori.h"
#include <exception>
#include <iostream>

using namespace std;


MD::MD() {
	/* de adaugat */
	//Complexitate: Theta(cp) - alocare vectori si initializare lista spatiului liber
	cpC = 10;
	cpV = 10;
	cheie = new TCheie[cpC];
	primVal = new int[cpC];
	urmC = new int[cpC];
	val = new TValoare[cpV];
	urmV = new int[cpV];
	//initializez lista spatiului liber pentru LSI exterioara
	for (int i = 0; i < cpC - 1; i++)
		urmC[i] = i + 1;
	urmC[cpC - 1] = -1;
	primLiberC = 0;
	//initializez lista spatiului liber pentru LSI interioara
	for (int j = 0; j < cpV - 1; j++)
		urmV[j] = j + 1;
	urmV[cpV - 1] = -1;
	primLiberV = 0;
	prim = -1;
	nr = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	//Complexitate: O(n_chei) in caz mediu si defavorabil, unde n_chei = numarul de chei distincte
	//Redimensionarea e Theta(cp) dar amortizat Theta(1) (se face doar la dublarea capacitatii)
	//caut cheia c in LSI exterioara
	int p = prim;
	while (p != -1 && cheie[p] != c)
		p = urmC[p];

	//aloc o pozitie pentru noul nod-valoare (in LSI interioara)
	//daca nu mai e spatiu liber, redimensionez vectorii val si urmV
	if (primLiberV == -1) {
		int cpNou = cpV * 2;
		TValoare* valNou = new TValoare[cpNou];
		int* urmVNou = new int[cpNou];
		for (int k = 0; k < cpV; k++) {
			valNou[k] = val[k];
			urmVNou[k] = urmV[k];
		}
		for (int k = cpV; k < cpNou - 1; k++)
			urmVNou[k] = k + 1;
		urmVNou[cpNou - 1] = -1;
		primLiberV = cpV;
		delete[] val;
		delete[] urmV;
		val = valNou;
		urmV = urmVNou;
		cpV = cpNou;
	}
	int j = primLiberV;
	primLiberV = urmV[primLiberV];
	val[j] = v;

	if (p != -1) {
		//cheia exista -> adaug valoarea la inceputul LSI-ului intern
		urmV[j] = primVal[p];
		primVal[p] = j;
	} else {
		//cheia nu exista -> creez un nod-cheie nou (in LSI exterioara)
		urmV[j] = -1;
		//aloc o pozitie pentru noul nod-cheie
		//daca nu mai e spatiu liber, redimensionez vectorii cheie, primVal, urmC
		if (primLiberC == -1) {
			int cpNou = cpC * 2;
			TCheie* cheieNou = new TCheie[cpNou];
			int* primValNou = new int[cpNou];
			int* urmCNou = new int[cpNou];
			for (int k = 0; k < cpC; k++) {
				cheieNou[k] = cheie[k];
				primValNou[k] = primVal[k];
				urmCNou[k] = urmC[k];
			}
			for (int k = cpC; k < cpNou - 1; k++)
				urmCNou[k] = k + 1;
			urmCNou[cpNou - 1] = -1;
			primLiberC = cpC;
			delete[] cheie;
			delete[] primVal;
			delete[] urmC;
			cheie = cheieNou;
			primVal = primValNou;
			urmC = urmCNou;
			cpC = cpNou;
		}
		int i = primLiberC;
		primLiberC = urmC[primLiberC];
		cheie[i] = c;
		primVal[i] = j;
		urmC[i] = prim;
		prim = i;
	}
	nr++;
}


bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	//Complexitate: O(n_chei + k_v), unde n_chei = numarul de chei distincte,
	//k_v = numarul de valori asociate cheii c
	//caut cheia c retinand si predecesorul
	int p = prim;
	int predCheie = -1;
	while (p != -1 && cheie[p] != c) {
		predCheie = p;
		p = urmC[p];
	}
	if (p == -1) return false;

	//caut valoarea v in LSI interioara, retinand si predecesorul
	int nodVal = primVal[p];
	int predVal = -1;
	while (nodVal != -1 && val[nodVal] != v) {
		predVal = nodVal;
		nodVal = urmV[nodVal];
	}
	if (nodVal == -1) return false;

	//scot nodul-valoare din LSI interna
	if (predVal == -1)
		primVal[p] = urmV[nodVal];
	else
		urmV[predVal] = urmV[nodVal];
	//dealocare: trec pozitia nodVal in lista spatiului liber
	urmV[nodVal] = primLiberV;
	primLiberV = nodVal;

	//daca lista de valori a devenit vida, scot si nodul-cheie
	if (primVal[p] == -1) {
		if (predCheie == -1)
			prim = urmC[p];
		else
			urmC[predCheie] = urmC[p];
		//dealocare: trec pozitia p in lista spatiului liber
		urmC[p] = primLiberC;
		primLiberC = p;
	}

	nr--;
	return true;
}


vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */
	//Complexitate: O(n_chei + k_v), unde n_chei = numarul de chei distincte,
	//k_v = numarul de valori asociate cheii c
	vector<TValoare> rezultat;
	int p = prim;
	while (p != -1 && cheie[p] != c)
		p = urmC[p];

	if (p != -1) {
		int nodVal = primVal[p];
		while (nodVal != -1) {
			rezultat.push_back(val[nodVal]);
			nodVal = urmV[nodVal];
		}
	}
	return rezultat;
}


int MD::dim() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return nr;
}


bool MD::vid() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return nr == 0;
}

IteratorMD MD::iterator() const {
	//Complexitate: Theta(1)
	return IteratorMD(*this);
}


IteratorValori MD::iterator(TCheie k) const {
	//Complexitate: O(n_chei) - constructorul IteratorValori cauta cheia
	return IteratorValori(*this, k);
}


MD::~MD() {
	/* de adaugat */
	//Complexitate: Theta(cp) - 5 apeluri delete[]
	delete[] cheie;
	delete[] primVal;
	delete[] urmC;
	delete[] val;
	delete[] urmV;
}