#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_5/lista muchiilor - matricea de incidenta (neorientat)/graf.txt");

    int n, m;
    fin >> n >> m;  // citim n=numarul de varfuri, m=numarul de muchii


    int u[101], v[101];
    for (int j = 1; j <= m; j++) {
        fin >> u[j] >> v[j];
    }
    fin.close();

    // Matricea de incidenta: M[i][j] = 1 daca varful i e incident cu muchia j
    int M[11][101] = {};

    for (int j = 1; j <= m; j++) {
        M[u[j]][j] = 1;
        M[v[j]][j] = 1;
    }

    // Afisam antetul matricei
    cout << "Matricea de incidenta (" << n << " varfuri x " << m << " muchii):" << endl;
    cout << endl;
    cout << "     ";
    for (int j = 1; j <= m; j++) cout << "M" << j << " ";  // numerele muchiilor
    cout << endl;

    // Afisam matricea rand cu rand (cate un rand per varf)
    for (int i = 1; i <= n; i++) {
        cout << "V" << i << " : ";
        for (int j = 1; j <= m; j++) cout << " " << M[i][j] << " ";
        cout << endl;
    }

    return 0;
}