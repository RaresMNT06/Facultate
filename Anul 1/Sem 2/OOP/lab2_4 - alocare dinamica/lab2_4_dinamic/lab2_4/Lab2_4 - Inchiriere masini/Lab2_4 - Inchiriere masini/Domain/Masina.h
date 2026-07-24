#ifndef MASINA_H
#define MASINA_H

typedef struct {
	char* nrInmatriculare;
	char* model;
	char* categorie;
	int esteInchiriata;
} Masina;


/*
 * Creeaza o noua masina
 * nrInmatriculare: sir de caractere (ex: "CJ 01 ABC")
 * model: sir de caractere (ex: "Dacia Duster")
 * categorie: sir de caractere (ex: "SUV")
 * return: o structura de tip Masina initializata
 */
Masina* creeazaMasina(const char* nrInmatriculare, const char* model, const char* categorie);

void distrugeMasina(Masina* m);

Masina* copiazaMasina(Masina* m);
#endif