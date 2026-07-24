#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int NMAX = 1005;
int cap[NMAX][NMAX];  // matricea de capacitati reziduale
int tata[NMAX];       // pentru reconstructia caii in BFS
int n_total;          // numarul total de noduri din reteaua de flux

// BFS standard pentru cautarea unei cai reziduale
bool bfs(int s, int t) {
    memset(tata, -1, sizeof(tata));
    tata[s] = s;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n_total; v++) {
            // Cautam arce reziduale nevizitate
            if (tata[v] == -1 && cap[u][v] > 0) {
                tata[v] = u;

                if (v == t) {
                    return true;
                }

                q.push(v);
            }
        }
    }

    return false;
}

// Edmonds-Karp - identic cu problema anterioara
int edmonds_karp(int s, int t) {
    int flux_total = 0;

    while (bfs(s, t)) {
        int minim = INT_MAX;
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            minim = min(minim, cap[u][v]);
        }

        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            cap[u][v] -= minim;
            cap[v][u] += minim;
        }

        flux_total += minim;
    }

    return flux_total;
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob3_test2_pt10/input.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob3_test2_pt10/output.out");

    int N;  // |L| - cardinalul multimii din stanga
    int M;  // |R| - cardinalul multimii din dreapta
    int E;  // numarul de muchii bipartite
    fin >> N >> M >> E;

    // Conform hint-ului: introducem 2 noduri virtuale
    // SURSA = 0, DESTINATIA = N+M+1
    // Nodurile din L sunt 1..N, nodurile din R sunt N+1..N+M
    int SURSA = 0;
    int DEST = N + M + 1;
    n_total = N + M + 2;

    memset(cap, 0, sizeof(cap));

    // Muchii de capacitate 1 de la SURSA la fiecare nod din L
    for (int i = 1; i <= N; i++) {
        cap[SURSA][i] = 1;
    }

    // Muchii de capacitate 1 de la fiecare nod din R la DESTINATIE
    for (int i = 1; i <= M; i++) {
        cap[N + i][DEST] = 1;
    }

    // Citim muchiile bipartite si le adaugam cu capacitate 1
    // Conform hint-ului: muchia (x, y) devine (x, y + N) in reteaua noastra
    for (int i = 0; i < E; i++) {
        int x;
        int y;
        fin >> x >> y;
        cap[x][y + N] = 1;
    }

    // Fluxul maxim in aceasta retea = cardinalitatea cuplajului maxim
    // (teorema: cuplaj maxim in graf bipartit = flux maxim in reteaua construita)
    fout << edmonds_karp(SURSA, DEST) << "\n";

    fin.close();
    fout.close();
    return 0;
}