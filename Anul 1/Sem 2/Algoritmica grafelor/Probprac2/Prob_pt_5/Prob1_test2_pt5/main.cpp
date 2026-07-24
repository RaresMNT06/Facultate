
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Muchie {
    int x;
    int y;
    int cost;
};

int tata[100005];
int rang[100005];

int gaseste(int u) {
    // Find cu compresia drumului
    if (tata[u] != u) {
        tata[u] = gaseste(tata[u]);
    }
    return tata[u];
}

void uneste(int u, int v) {
    // Union by rank
    int ru = gaseste(u);
    int rv = gaseste(v);

    if (ru == rv) {
        return;
    }

    if (rang[ru] < rang[rv]) {
        tata[ru] = rv;
    }
    else if (rang[ru] > rang[rv]) {
        tata[rv] = ru;
    }
    else {
        tata[rv] = ru;
        rang[ru]++;
    }
}

bool cmp(const Muchie& a, const Muchie& b) {
    return a.cost < b.cost;
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob1_test2_pt5/apm.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_5/Prob1_test2_pt5/apm.out");

    int n;
    int m;
    fin >> n >> m;

    vector<Muchie> muchii(m);
    for (int i = 0; i < m; i++) {
        fin >> muchii[i].x >> muchii[i].y >> muchii[i].cost;
    }

    // Initializare: fiecare nod este propria componenta
    for (int i = 1; i <= n; i++) {
        tata[i] = i;
        rang[i] = 0;
    }

    // Sortam muchiile crescator dupa cost
    sort(muchii.begin(), muchii.end(), cmp);

    long long cost_total = 0;
    vector<Muchie> apm;

    // Algoritmul lui Kruskal
    for (int i = 0; i < m && (int)apm.size() < n - 1; i++) {
        int x = muchii[i].x;
        int y = muchii[i].y;

        // Daca cele doua capete sunt in componente diferite, adaugam muchia
        if (gaseste(x) != gaseste(y)) {
            uneste(x, y);
            apm.push_back(muchii[i]);
            cost_total += muchii[i].cost;
        }
    }

    // Scriem rezultatul
    fout << cost_total << "\n";
    fout << apm.size() << "\n";
    for (auto& e : apm) {
        fout << e.x << " " << e.y << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
