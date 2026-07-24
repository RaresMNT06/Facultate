#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

const int NMAX = 1005;
int cap[NMAX][NMAX];  // capacitatea reziduala c_f(u,v)
int tata[NMAX];
int n;
int m;

bool bfs(int s, int t) {
    // Cautam o cale reziduala de la s la t
    memset(tata, -1, sizeof(tata));
    tata[s] = s; // marcam sursa ca vizitata

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            // Arc rezidual disponibil si v nevizitat
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

int edmonds_karp(int s, int t) {
    int flux_total = 0;

    while (bfs(s, t)) {
        // Determinam capacitatea minima de pe cale (gat de strangulare)
        int minim = INT_MAX;
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            minim = min(minim, cap[u][v]);
        }

        // Actualizam capacitatile reziduale de-a lungul caii
        for (int v = t; v != s; v = tata[v]) {
            int u = tata[v];
            cap[u][v] -= minim;  // scade pe arcul direct
            cap[v][u] += minim;  // creste pe arcul invers
        }

        flux_total += minim;
    }

    return flux_total;
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob1_test2_pt10/flux.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob1_test2_pt10/flux.out");

    fin >> n >> m;

    memset(cap, 0, sizeof(cap));

    // Citim arcele si construim matricea de capacitati
    for (int i = 0; i < m; i++) {
        int x;
        int y;
        int c;
        fin >> x >> y >> c;
        cap[x][y] += c;
    }

    int s = 0;          // sursa
    int t = n - 1;      // destinatie

    fout << edmonds_karp(s, t) << "\n";

    fin.close();
    fout.close();
    return 0;
}