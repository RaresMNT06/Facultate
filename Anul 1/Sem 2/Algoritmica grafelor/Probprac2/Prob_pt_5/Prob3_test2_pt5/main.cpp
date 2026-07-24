#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int NMAX = 1005;
int cap[NMAX][NMAX];  // matricea de capacitati reziduale c_f(u,v)
int tata[NMAX];       // pentru reconstructia caii in BFS
int n;                // numarul de noduri
int m;                // numarul de arce

// BFS care cauta o cale de la sursa s la destinatia t in graful rezidual
bool bfs(int s, int t) {
    // Resetam vectorul de parinti (-1 = nevizitat)
    memset(tata, -1, sizeof(tata));
    tata[s] = s;  // marcam sursa ca vizitata (e propriul ei parinte)

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Parcurgem toti vecinii lui u
        for (int v = 0; v < n; v++) {
            // Verificam doua conditii:
            // 1. v nu a fost vizitat inca
            // 2. exista capacitate reziduala pe arcul u->v
            if (tata[v] == -1 && cap[u][v] > 0) {
                tata[v] = u;  // retinem din ce nod am ajuns in v

                // Daca am ajuns la destinatie, gata
                if (v == t) {
                    return true;
                }

                q.push(v);
            }
        }
    }

    // Nu mai exista nicio cale de la s la t
    return false;
}

// Algoritmul Edmonds-Karp = Ford-Fulkerson cu BFS
int edmonds_karp(int s, int t) {
    int flux_total = 0;

    // Cat timp gasim o cale de augmentare
    while (bfs(s, t)) {
        // Pas 1: determinam capacitatea minima de pe cale (bottleneck)
        // Parcurgem calea inapoi, de la t la s
        int minim = INT_MAX;
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            minim = min(minim, cap[u][v]);
        }

        // Pas 2: actualizam capacitatile reziduale pe cale
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            cap[u][v] -= minim;  // scade pe arcul direct
            cap[v][u] += minim;  // creste pe arcul invers (rezidual)
        }

        // Adunam fluxul la totalul fluxului
        flux_total += minim;
    }

    return flux_total;
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob3_test2_pt5/input.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob3_test2_pt5/output.out");

    fin >> n >> m;

    // Initializam matricea de capacitati cu 0
    memset(cap, 0, sizeof(cap));

    // Citim arcele si construim matricea de capacitati
    for (int i = 0; i < m; i++) {
        int x;
        int y;
        int c;
        fin >> x >> y >> c;
        cap[x][y] += c;  // += pentru a permite arce multiple intre aceleasi noduri
    }

    // Conform cerintei: sursa = 0, destinatie = n-1
    int s = 0;
    int t = n - 1;

    fout << edmonds_karp(s, t) << "\n";

    fin.close();
    fout.close();
    return 0;
}