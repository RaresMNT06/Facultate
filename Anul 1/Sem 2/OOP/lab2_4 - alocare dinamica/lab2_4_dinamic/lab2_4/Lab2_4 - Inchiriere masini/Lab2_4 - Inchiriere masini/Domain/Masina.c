#define _CRT_SECURE_NO_WARNINGS
#include "Masina.h"
#include <string.h>
#include <stdlib.h>

int FORTEAZA_EROARE_MALLOC1 = 0;

Masina* creeazaMasina(const char* nrInmatriculare, const char* model, const char* categorie) {

	if (FORTEAZA_EROARE_MALLOC1 == 1)
		return NULL;
	Masina* m = (Masina*)malloc(sizeof(Masina));
	if (m == NULL || FORTEAZA_EROARE_MALLOC1 == 2) {
		if (m != NULL)
			free(m);
		return NULL; //verificam daca alocarea a reusit 
	}

	m->nrInmatriculare = (char*)malloc(strlen(nrInmatriculare) + 1); //+1 ca sa includem spatiu si pentru terminatorul de sir \0
	if (m->nrInmatriculare != NULL)
		strcpy(m->nrInmatriculare, nrInmatriculare);

	m->model = (char*)malloc(strlen(model) + 1); //+1 ca sa includem spatiu si pentru terminatorul de sir \0
	if (m->model != NULL)
		strcpy(m->model, model);

	m->categorie = (char*)malloc(strlen(categorie) + 1); //+1 ca sa includem spatiu si pentru terminatorul de sir \0 
	if (m->categorie != NULL)
		strcpy(m->categorie, categorie);

	m->esteInchiriata = 0;

	return m;

}

void distrugeMasina(Masina* m) {
	if (m == NULL)
		return;

	if (m->nrInmatriculare != NULL) {
		free(m->nrInmatriculare);
		m->nrInmatriculare = NULL;
	}
	if (m->model != NULL) {
		free(m->model);
		m->model = NULL;
	}
	if (m->categorie != NULL) {
		free(m->categorie);
		m->categorie = NULL;
	}

	free(m);
}

Masina* copiazaMasina(Masina* m) {
	if (m == NULL)
		return NULL;

	return creeazaMasina(m->nrInmatriculare, m->model, m->categorie);
}