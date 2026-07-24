#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v1_drumuri_case_dijkstra/case.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare drum
        int ci, cj, L;
        fin >> ci >> cj >> L;
        adj[ci].push_back({cj, L});  // adaugam drumul in graf
    }

    int cx, cy;
    fin >> cx >> cy;  // casa de plecare si casa destinatie
    fin.close();

    vector<int> dist(n + 1, INT_MAX);  // toate distantele = infinit la inceput
    vector<int> parinte(n + 1, -1);   // nu stim inca drumul
    priority_queue<pii, vector<pii>, greater<pii>> pq;  // coada care scoate mereu minimul

    dist[cx] = 0;      // distanta de la sursa la ea insasi e 0
    pq.push({0, cx});  // pornim din casa cx

    while (!pq.empty()) {  // cat timp mai avem noduri de procesat
        auto [d, u] = pq.top();  // luam casa cu costul cel mai mic
        pq.pop();
        if (d > dist[u]) continue;  // daca am gasit deja un drum mai bun, sarim

        for (auto [v, w] : adj[u]) {      // pentru fiecare casa vecina
            if (dist[u] + w < dist[v]) {  // daca drumul prin u e mai scurt
                dist[v] = dist[u] + w;    // actualizam distanta
                parinte[v] = u;           // retinem ca am venit prin u
                pq.push({dist[v], v});    // adaugam in coada
            }
        }
    }

    if (dist[cy] == INT_MAX) {  // daca distanta e inca infinit => nu exista drum
        cout << "Nu exista drum de la casa " << cx << " la casa " << cy << endl;
    } else {
        cout << "Costul minim: " << dist[cy] << endl;

        // reconstructia drumului: mergem inapoi de la destinatie la sursa
        vector<int> drum;
        int cur = cy;
        while (cur != -1) {       // cat timp nu am ajuns la inceput
            drum.push_back(cur);  // adaugam casa curenta
            cur = parinte[cur];   // mergem la casa anterioara
        }
        reverse(drum.begin(), drum.end());  // inversam ca sa fie in ordine corecta

        cout << "Drumul optim: ";
        for (int i = 0; i < (int)drum.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << drum[i];
        }
        cout << endl;
    }

    return 0;
}