#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
using namespace std;

bool BFS(int G[1000][1000], int V, int s, int d, int parinte[]) {
    bool* viz = new bool[V];
    for(int i = 0; i < V; i++)
        viz[i] = false;

    queue<int> Q;
    Q.push(s);
    parinte[s] = -1;
    viz[s] = true;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int v = 0; v < V; v++) {
            if(viz[v] == false && G[u][v] > 0) {
                Q.push(v);
                parinte[v] = u;
                viz[v] = true;
            }
        }
    }

    bool gasit = viz[d];
    delete[] viz;
    return gasit;
}

int Ford_Fulkerson(int G[1000][1000], int V, int s, int d) {
    int u, v;

    // graf rezidual - copie a matricii originale
    static int rG[1000][1000];
    for(u = 0; u < V; u++)
        for(v = 0; v < V; v++)
            rG[u][v] = G[u][v];

    int* parinte = new int[V];
    int flux_maxim = 0;

    while(BFS(rG, V, s, d, parinte)) {
        // bottleneck-ul pe drumul gasit
        int flux_cale = INT_MAX;
        for(v = d; v != s; v = parinte[v]) {
            u = parinte[v];
            flux_cale = min(flux_cale, rG[u][v]);
        }

        // actualizam graful rezidual
        for(v = d; v != s; v = parinte[v]) {
            u = parinte[v];
            rG[u][v] -= flux_cale;
            rG[v][u] += flux_cale;
        }

        flux_maxim += flux_cale;
    }

    delete[] parinte;
    return flux_maxim;
}


int G[1000][1000];

int main(int argc, char* argv[]) {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Lab5_prob1/in.txt");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Lab5_prob1/out.txt");


    if(!fin.is_open()) {
        cerr << "Nu pot deschide fisierul de intrare!" << endl;
        return 1;
    }

    int V, E, c, x, y;
    fin >> V >> E;

    // initializare cu 0 - CRITIC!
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            G[i][j] = 0;

    for(int i = 0; i < E; i++) {
        fin >> x >> y >> c;
        G[x][y] += c;  // += pentru a permite muchii multiple intre aceleasi noduri
    }

    // sursa este 0, destinatia este V-1 (conform enuntului)
    int fluxM = Ford_Fulkerson(G, V, 0, V - 1);
    fout << fluxM;

    fin.close();
    fout.close();
    return 0;
}