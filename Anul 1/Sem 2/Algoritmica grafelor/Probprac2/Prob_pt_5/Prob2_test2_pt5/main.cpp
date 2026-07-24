#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <iomanip>

using namespace std;

const int NMAX = 1005;
int cap[NMAX][NMAX];  // matricea de capacitati reziduale
int tata[NMAX];       // pentru reconstructia caii in BFS
int n;                // numarul de noduri
int m;                // numarul de arce

// BFS pentru gasirea unei cai reziduale de la s la t
bool bfs(int s, int t) {
    memset(tata, -1, sizeof(tata));
    tata[s] = s;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Atentie: indexare de la 1, deci v merge de la 1 la n
        for (int v = 1; v <= n; v++) {
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

// Algoritmul Edmonds-Karp pentru flux maxim
int edmonds_karp(int s, int t) {
    int flux_total = 0;

    while (bfs(s, t)) {
        // Determinam capacitatea minima de pe cale
        int minim = INT_MAX;
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            minim = min(minim, cap[u][v]);
        }

        // Actualizam capacitatile reziduale
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
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob2_test2_pt5/input.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob2_test2_pt5/output.out");

    fin >> n >> m;

    memset(cap, 0, sizeof(cap));

    // Citim cele m muchii
    for (int i = 0; i < m; i++) {
        int x;
        int y;
        int c;
        fin >> x >> y >> c;
        cap[x][y] += c;
    }

    // Indexare de la 1: sursa = 1, destinatie = n
    int s = 1;
    int t = n;

    int flux = edmonds_karp(s, t);

    // Output cu 3 zecimale conform cerintei (8.000)
    fout << fixed << setprecision(3) << (double)flux << "\n";

    fin.close();
    fout.close();
    return 0;
}