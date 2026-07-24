#include <iostream>  // pentru cout (afisare pe ecran)
#include <fstream>   // pentru ifstream (citire din fisier)
using namespace std;

int main() {
    // deschidem fisierul cu matricea de adiacenta (graf orientat)
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_5/matricea de adiacenta - matricea de incidenta (orientat)/graf.txt");

    int n;
    fin >> n;  // citim n = numarul de varfuri

    // Matricea de adiacenta: A[i][j] = 1 daca exista arc de la i la j
    int A[11][11] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> A[i][j];  // citim rand cu rand
    fin.close();  // inchidem fisierul

    // Extragem arcele din matricea de adiacenta
    // Parcurgem TOATA matricea (nu doar jumatatea superioara)
    // pentru ca graful e ORIENTAT => arcul (i,j) e diferit de (j,i)
    int u[101], v[101];
    int m = 0;  // numarul de arce gasit
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (A[i][j] == 1) {
                m++;       // am gasit un arc nou
                u[m] = i;  // arcul m PLEACA din i
                v[m] = j;  // arcul m SOSESTE in j
            }

    // Matricea de incidenta pentru graf ORIENTAT:
    // M[i][j] =  1 daca arcul j pleaca din varful i
    // M[i][j] = -1 daca arcul j soseste in varful i
    // M[i][j] =  0 daca varful i nu e incident cu arcul j
    int M[11][101] = {};  // initializata cu 0
    for (int j = 1; j <= m; j++) {
        M[u[j]][j] =  1;  // varful sursa al arcului j primeste +1
        M[v[j]][j] = -1;  // varful destinatie al arcului j primeste -1
    }

    // Afisam antetul matricei
    cout << "Matricea de incidenta (" << n << " varfuri x " << m << " arce):" << endl;
    cout << "(+1 = arc pleaca, -1 = arc soseste, 0 = neincident)" << endl << endl;
    cout << "      ";
    for (int j = 1; j <= m; j++) cout << "A" << j << "  ";  // numerele arcelor
    cout << endl;

    // Afisam matricea rand cu rand (cate un rand per varf)
    for (int i = 1; i <= n; i++) {
        cout << "V" << i << " :  ";
        for (int j = 1; j <= m; j++) {
            if (M[i][j] == -1) cout << "-1 ";  // arc soseste
            else cout << " " << M[i][j] << " "; // arc pleaca (1) sau neincident (0)
        }
        cout << endl;
    }

    return 0;
}