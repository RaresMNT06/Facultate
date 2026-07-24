#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int NMAX = 1005;

struct Muchie {
    int x;
    int y;
    double cost;
};

int tata[NMAX];

int find(int x) {
    if (tata[x] == x) return x;
    return tata[x] = find(tata[x]);
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) tata[rx] = ry;
}

int main() {
    ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob2_test2_pt10/input.in");
    ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Probprac2/Prob_pt_10/Prob2_test2_pt10/output.out");

    int n;
    fin >> n;

    vector<double> X(n + 1);
    vector<double> Y(n + 1);

    for (int i = 1; i <= n; i++) {
        fin >> X[i] >> Y[i];
    }

    vector<Muchie> muchii;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double dx = X[i] - X[j];
            double dy = Y[i] - Y[j];
            double d = sqrt(dx * dx + dy * dy);

            Muchie m;
            m.x = i;
            m.y = j;
            m.cost = d;
            muchii.push_back(m);
        }
    }

    sort(muchii.begin(), muchii.end(), [](Muchie a, Muchie b) {
        return a.cost < b.cost;
    });

    for (int i = 1; i <= n; i++) tata[i] = i;

    double cost_total = 0;
    int nr_muchii = 0;

    for (int i = 0; i < (int)muchii.size() && nr_muchii < n - 1; i++) {
        if (find(muchii[i].x) != find(muchii[i].y)) {
            unite(muchii[i].x, muchii[i].y);
            cost_total += muchii[i].cost;
            nr_muchii++;
        }
    }

    long long val = (long long)(cost_total * 1000 + 0.5);
    long long parte_intreaga = val / 1000;
    long long parte_zecimala = val % 1000;

    fout << parte_intreaga << ".";

    if (parte_zecimala < 100) fout << "0";
    if (parte_zecimala < 10) fout << "0";
    fout << parte_zecimala << "\n";

    fin.close();
    fout.close();
    return 0;
}