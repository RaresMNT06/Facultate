#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Test_practic1/input.txt");

    int n;
    fin >> n;

    // Matricea de adiacenta: A[i][j] = 1 daca exista muchie intre i si j
    int A[11][11] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> A[i][j];
    fin.close();

    int u[51], v[51];
    int m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j] == 1) {
                m++;
                u[m] = i;
                v[m] = j;
            }

    // Matricea de incidenta: M[i][j] = 1 daca varful i e incident cu muchia j
    int M[11][51] = {};
    for (int j = 1; j <= m; j++) {
        M[u[j]][j] = 1;
        M[v[j]][j] = 1;
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