#include <iostream>  // pentru cout (afisare pe ecran)
#include <fstream>   // pentru ifstream (citire din fisier)
#include <vector>    // pentru vector (liste dinamice)

using namespace std;

ifstream f("in.txt");  // deschidem fisierul de intrare

int main()
{
    int x, y, n, m;
    if (!(f >> n >> m)) return 0;  // citim n=noduri, m=muchii; daca fisierul e gol, iesim

    // Matricea de adiacenta: m_a[i][j] = 1 daca exista muchie intre i si j
    vector<vector<int>> m_a(n + 1, vector<int>(n + 1, 0));

    // Lista de adiacenta: l_a[i] = lista vecinilor nodului i
    vector<vector<int>> l_a(n + 1);

    // Matricea de incidenta: m_i[i][j] = 1 daca nodul i e incident cu muchia j
    vector<vector<int>> m_i(n + 1, vector<int>(m, 0));

    for (int i = 0; i < m; i++)
    {
        f >> x >> y;  // citim muchia i: intre nodurile x si y

        // Completam matricea de adiacenta (neorientat => ambele directii)
        m_a[x][y] = 1;
        m_a[y][x] = 1;

        // Completam matricea de incidenta (ambele noduri sunt incidente cu muchia i)
        m_i[x][i] = 1;
        m_i[y][i] = 1;

        // Completam lista de adiacenta (fiecare nod il are pe celalalt ca vecin)
        l_a[x].push_back(y);
        l_a[y].push_back(x);
    }

    // Afisam matricea de adiacenta
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << m_a[i][j] << " ";
        cout << "\n";
    }
    cout << "____________________\n";

    // Afisam lista de adiacenta
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)l_a[i].size(); j++)
            cout << l_a[i][j] << " ";
        cout << "\n";
    }
    cout << "____________________\n";

    // Afisam matricea de incidenta
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++)
            cout << m_i[i][j] << " ";
        cout << "\n";
    }

    return 0;
}