#include "mysort.h"

void sortare_generica(Participant** lista, int n, FunctieComparare cmpF) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            // Dacă funcția de comparare zice că ordinea e greșită (> 0)
            if (cmpF(lista[i], lista[j]) > 0) {
                // Interschimbăm doar pointerii (adresele)
                Participant* aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}