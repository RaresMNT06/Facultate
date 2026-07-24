#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> adj;   // lista de adiacenta a grafului
vector<bool> vizitat;      // tinem minte ce noduri am vizitat
int n;                     // numarul de noduri (global ca sa il vada si dfs)

// DFS care ignora muchia (u_skip, v_skip) = muchia pe care o testam
void dfs(int u, int u_skip, int v_skip) {
    vizitat[u] = true;
    for (int v : adj[u]) {          // pentru fiecare vecin al lui u
        if (!vizitat[v]) {          // daca vecinul nu e vizitat
            if ((u == u_skip && v == v_skip) || (u == v_skip && v == u_skip))
                continue;           // sarim peste muchia testata (o ignoram)
            dfs(v, u_skip, v_skip); // continuam DFS din vecinul v
        }
    }
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac1/Probleme_pt_10/v4_muchie_punte/input.txt");

    int m;
    fin >> n >> m;  // n = numarul de orase, m = numarul de drumuri

    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {  // citim fiecare drum
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);  // drum de la x la y
        adj[y].push_back(x);  // drum de la y la x (bidirectional)
    }
    fin.close();

    int mx, my;
    cout << "Introdu muchia de testat (x y): ";
    cin >> mx >> my;  // muchia pe care vrem sa o testam

    vizitat.assign(n + 1, false);
    dfs(1, mx, my);  // facem DFS din nodul 1 fara muchia (mx, my)

    // verificam daca toate nodurile au fost vizitate
    bool conex = true;
    for (int i = 1; i <= n; i++)
        if (!vizitat[i]) { conex = false; break; }  // am gasit un nod nevizitat => graful s-a deconectat

    // DA = graful ramane conex fara muchia testata
    // NU = muchia e punte, fara ea graful se rupe in doua
    cout << (conex ? "DA" : "NU") << endl;

    return 0;
}