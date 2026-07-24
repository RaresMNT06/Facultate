#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>    // pentru INT_MAX (valoare infinita)
#include <algorithm>  // pentru reverse
using namespace std;
typedef pair<int,int> pii;  // pereche (cost, nod) pentru coada

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v7_atractii_dijkstra/input.txt");

    int n, m;
    fin >> n >> m;  // n = numarul de atractii, m = numarul de drumuri

    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare drum
        int u, v, k;
        fin >> u >> v >> k;         // drum de la u la v cu costul k
        adj[u].push_back({v, k});   // drum unidirectional de la u la v
    }
    fin.close();

    int X, Y;
    cout << "Introdu punctul de start X: ";
    cin >> X;  // atractia de plecare
    cout << "Introdu punctul de destinatie Y: ";
    cin >> Y;  // atractia de destinatie

    vector<int> dist(n + 1, INT_MAX);  // toate distantele = infinit la inceput
    vector<int> parinte(n + 1, -1);    // nu stim inca drumul
    priority_queue<pii, vector<pii>, greater<pii>> pq;  // coada care scoate mereu minimul

    dist[X] = 0;      // distanta de la sursa la ea insasi e 0
    pq.push({0, X});  // pornim din atractia X

    while (!pq.empty()) {  // cat timp mai avem atractii de procesat
        auto [d, u] = pq.top();  // luam atractia cu costul cel mai mic
        pq.pop();
        if (d > dist[u]) continue;  // daca am gasit deja un drum mai bun, sarim

        for (auto [v, w] : adj[u]) {      // pentru fiecare atractie vecina
            if (dist[u] + w < dist[v]) {  // daca drumul prin u e mai scurt
                dist[v] = dist[u] + w;    // actualizam distanta
                parinte[v] = u;           // retinem ca am venit prin u
                pq.push({dist[v], v});    // adaugam in coada
            }
        }
    }

    if (dist[Y] == INT_MAX) {  // daca distanta e inca infinit => nu exista drum
        cout << "Nu exista drum!" << endl;
    } else {
        cout << "Costul minim: " << dist[Y] << endl;

        // reconstructia drumului: mergem inapoi de la destinatie la sursa
        vector<int> drum;
        int cur = Y;
        while (cur != -1) {       // cat timp nu am ajuns la inceput
            drum.push_back(cur);  // adaugam atractia curenta
            cur = parinte[cur];   // mergem la atractia anterioara
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