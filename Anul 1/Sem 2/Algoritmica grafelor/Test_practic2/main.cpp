#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int NMAX = 1005;
const int INF = 1000000000;
int cap[NMAX][NMAX];
int tata[NMAX];
int n_total;

bool bfs(int s, int t) {
    memset(tata, -1, sizeof(tata));
    tata[s] = s;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n_total; v++) {
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

int calculeaza_flux_maxim(int s, int t) {
    int flux_total = 0;

    while (bfs(s, t)) {
        int minim = INF;
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
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Test_practic2/input.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Test_practic2/output.out");

    int N;
    int M;
    int E;
    fin >> N >> M >> E;

    int SURSA = 0;
    int DEST = N + M + 1;
    n_total = N + M + 2;

    memset(cap, 0, sizeof(cap));

    for (int i = 1; i <= N; i++) {
        cap[SURSA][i] = 1;
    }

    for (int i = 1; i <= M; i++) {
        cap[N + i][DEST] = 1;
    }

    for (int i = 0; i < E; i++) {
        int x;
        int y;
        fin >> x >> y;
        cap[x][y + N] = 1;
    }

    fout << calculeaza_flux_maxim(SURSA, DEST) << "\n";

    fin.close();
    fout.close();
    return 0;
}