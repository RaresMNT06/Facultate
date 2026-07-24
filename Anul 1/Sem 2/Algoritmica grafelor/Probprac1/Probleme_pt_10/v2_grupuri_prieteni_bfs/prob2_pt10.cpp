#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v2_grupuri_prieteni_bfs/input.txt");

    int n, m;
    fin >> n >> m;  // n = numarul de copii, m = numarul de relatii

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare relatie de prietenie
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);  // x il are pe y ca prieten
        adj[y].push_back(x);  // y il are pe x ca prieten (relatia e simetrica)
    }
    fin.close();

    vector<bool> vizitat(n + 1, false);  // tinem minte ce copii am vizitat deja
    vector<vector<int>> grupuri;         // lista tuturor grupurilor gasite

    for (int start = 1; start <= n; start++) {  // pentru fiecare copil
        if (!vizitat[start]) {  // daca nu e deja intr-un grup, facem unul nou
            vector<int> grup;
            queue<int> Q;
            vizitat[start] = true;  // marcam copilul ca vizitat
            Q.push(start);          // il adaugam in coada BFS

            while (!Q.empty()) {        // cat timp mai avem copii de procesat
                int u = Q.front();      // luam primul copil din coada
                Q.pop();
                grup.push_back(u);      // il adaugam in grupul curent

                for (int v : adj[u]) {      // pentru fiecare prieten al lui u
                    if (!vizitat[v]) {      // daca prietenul nu e deja vizitat
                        vizitat[v] = true;  // il marcam ca vizitat
                        Q.push(v);          // il adaugam in coada
                    }
                }
            }
            grupuri.push_back(grup);  // grupul e complet, il adaugam la lista
        }
    }

    cout << "Numarul de grupuri: " << grupuri.size() << endl << endl;
    for (int i = 0; i < (int)grupuri.size(); i++) {  // afisam fiecare grup
        cout << "Grupul " << i + 1 << ": { ";
        for (int j = 0; j < (int)grupuri[i].size(); j++) {
            if (j > 0) cout << ", ";
            cout << grupuri[i][j];
        }
        cout << " }" << endl;
    }

    return 0;
}