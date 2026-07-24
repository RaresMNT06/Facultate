#include <iostream>  // pentru cout (afisare pe ecran)
#include <fstream>   // pentru ifstream (citire din fisier)
using namespace std;

int main() {
    // deschidem fisierul cu matricea de adiacenta
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_5/matricea de adiacenta - lista muchiilor (neorientat)/graf.txt");

    int n;
    fin >> n;  // citim n = numarul de varfuri

    // Matricea de adiacenta: A[i][j] = 1 daca exista muchie intre i si j
    int A[11][11] = {};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fin >> A[i][j];  // citim rand cu rand
    fin.close();  // inchidem fisierul

    // Parcurgem jumatatea superioara a matricei (i < j)
    // pentru ca graful e neorientat => muchia (i,j) e aceeasi cu (j,i)
    cout << "Lista muchiilor:" << endl;
    int m = 0;  // numarul de muchii gasit
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (A[i][j] == 1) {
                m++;  // am gasit o muchie noua
                cout << "Muchia " << m << ": (" << i << ", " << j << ")" << endl;
            }

    cout << endl << "Total: " << m << " muchii." << endl;

    return 0;
}