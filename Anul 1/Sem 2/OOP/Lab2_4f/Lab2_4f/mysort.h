#ifndef MYSORT_H
#define MYSORT_H

#include "participant.h"

// Definim tipul pentru pointer la funcție
// Returnează > 0 dacă p1 > p2, 0 dacă sunt egali, < 0 dacă p1 < p2
typedef int (*FunctieComparare)(Participant* p1, Participant* p2);

/*
 * Sortează un vector de pointeri la participanți folosind un criteriu generic.
 * @param lista: vectorul de pointeri
 * @param n: numărul de elemente
 * @param cmpF: funcția de comparare (criteriul)
 */
void sortare_generica(Participant** lista, int n, FunctieComparare cmpF);

#endif
