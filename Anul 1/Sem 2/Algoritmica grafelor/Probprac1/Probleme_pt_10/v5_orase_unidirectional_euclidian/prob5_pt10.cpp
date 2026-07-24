#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>      // pentru sqrt si pow (distanta euclidiana)
#include <algorithm>  // pentru reverse
using namespace std;
typedef pair<double,int> pdi;  // pereche (cost, nod) pentru coada

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v5_orase_unidirectional_euclidian/input.txt");

    int n, m;
    fin >> n >> m;  // n = numarul de orase, m = numarul de drumuri

    vector<double> cx(n + 1), cy(n + 1);
    for (int i = 1; i <= n; i++)
        fin >> cx[i] >> cy[i];  // citim coordonatele fiecarui oras

    vector<vector<pair<int,double>>> adj(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare drum
        int x, y;
        fin >> x >> y;
        double cost = sqrt(pow(cx[x]-cx[y],2) + pow(cy[x]-cy[y],2));  // distanta euclidiana intre x si y
        adj[x].push_back({y, cost});  // drum doar de la x la y (unidirectional)
    }
    fin.close();

    int S, F;
    cout << "Introdu orasul sursa: ";
    cin >> S;  // orasul de plecare
    cout << "Introdu orasul destinatie: ";
    cin >> F;  // orasul de destinatie

    vector<double> dist(n + 1, 1e18);  // toate distantele = infinit la inceput
    vector<int> parinte(n + 1, -1);    // nu stim inca drumul
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;  // coada care scoate mereu minimul

    dist[S] = 0;      // distanta de la sursa la ea insasi e 0
    pq.push({0, S});  // pornim din orasul S

    while (!pq.empty()) {  // cat timp mai avem orase de procesat
        auto [d, u] = pq.top();  // luam orasul cu costul cel mai mic
        pq.pop();
        if (d > dist[u]) continue;  // daca am gasit deja un drum mai bun, sarim

        for (auto [v, w] : adj[u]) {      // pentru fiecare oras vecin
            if (dist[u] + w < dist[v]) {  // daca drumul prin u e mai scurt
                dist[v] = dist[u] + w;    // actualizam distanta
                parinte[v] = u;           // retinem ca am venit prin u
                pq.push({dist[v], v});    // adaugam in coada
            }
        }
    }

    if (dist[F] >= 1e18) {  // daca distanta e inca infinit => nu exista drum
        cout << "Nu exista drum!" << endl;
    } else {
        cout << "Costul minim: " << dist[F] << endl;

        // reconstructia drumului: mergem inapoi de la destinatie la sursa
        vector<int> drum;
        int cur = F;
        while (cur != -1) {       // cat timp nu am ajuns la inceput
            drum.push_back(cur);  // adaugam orasul curent
            cur = parinte[cur];   // mergem la orasul anterior
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