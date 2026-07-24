#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> adj;   // lista de adiacenta a grafului
vector<bool> vizitat;      // tinem minte ce noduri am vizitat
bool are_ciclu = false;    // devine true daca gasim un ciclu

// DFS care detecteaza cicluri
void dfs(int u, int parinte) {
    vizitat[u] = true;
    for (int v : adj[u]) {       // pentru fiecare vecin al lui u
        if (!vizitat[v]) {       // daca vecinul nu e vizitat, mergem mai departe
            dfs(v, u);
        } else if (v != parinte) {  // daca e vizitat si nu e parintele lui u => ciclu
            are_ciclu = true;
        }
    }
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v6_graf_aciclic/input.txt");

    int n, m;
    fin >> n >> m;  // n = numarul de noduri, m = numarul de muchii

    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare muchie
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);  // muchie de la x la y
        adj[y].push_back(x);  // muchie de la y la x (neorientat)
    }
    fin.close();

    vizitat.assign(n + 1, false);
    for (int i = 1; i <= n; i++)  // pornim DFS din fiecare nod nevizitat
        if (!vizitat[i])          // (graful poate sa nu fie conex)
            dfs(i, -1);           // -1 = nodul 1 nu are parinte

    // DA = graful e aciclic (fara cicluri)
    // NU = graful are cel putin un ciclu
    cout << (are_ciclu ? "NU" : "DA") << endl;

    return 0;
}