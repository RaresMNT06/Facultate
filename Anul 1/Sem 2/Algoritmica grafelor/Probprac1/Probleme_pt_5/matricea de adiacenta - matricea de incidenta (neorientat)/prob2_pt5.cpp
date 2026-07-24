#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_5/matricea de adiacenta - matricea de incidenta (neorientat)/graf.txt");

    int n;
    fin >> n;  // citim n = numarul de varfuri

    // Matricea de adiacenta: A[i][j] = 1 daca exista muchie intre i si j
    int A[11][11] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> A[i][j];  // citim rand cu rand
    fin.close();  // inchidem fisierul

    // Extragem muchiile din matricea de adiacenta
    // Parcurgem doar jumatatea superioara (i < j) pentru ca graful e neorientat
    // => evitam sa numaram muchia (i,j) si (j,i) de doua ori
    int u[51], v[51];
    int m = 0;  // numarul de muchii gasit
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j] == 1) {
                m++;        // am gasit o muchie noua
                u[m] = i;   // varful de start al muchiei m
                v[m] = j;   // varful de sfarsit al muchiei m
            }

    // Matricea de incidenta: M[i][j] = 1 daca varful i e incident cu muchia j
    int M[11][51] = {};  // initializata cu 0
    for (int j = 1; j <= m; j++) {
        M[u[j]][j] = 1;  // varful u[j] e incident cu muchia j
        M[v[j]][j] = 1;  // varful v[j] e incident cu muchia j
    }

    cout << "Matricea de incidenta (" << n << " varfuri x " << m << " muchii):" << endl;
    cout << endl;
    cout << "     ";
    for (int j = 1; j <= m; j++) cout << "M" << j << " ";  
    cout << endl;

    // Afisam matricea rand cu rand (cate un rand per varf)
    for (int i = 1; i <= n; i++) {
        cout << "V" << i << " : ";
        for (int j = 1; j <= m; j++) cout << " " << M[i][j] << " ";
        cout << endl;
    }

    return 0;
}