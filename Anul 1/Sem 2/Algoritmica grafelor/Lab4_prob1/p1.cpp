#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Lab4_prob1/input.txt");
ofstream fout("C:/Users/rares/Desktop/Sem2/Algoritmica grafelor/Lab4_prob1/output.txt");

int fii[100005], t[100005], k[100005], nr = 0;

void codarePrufer(int k[], int fii[], int t[], int n, int& nr) {
    bool gasit = false;
    while (!gasit)
    {
        for (int i = 0; i < n; i++) {
            gasit = true;
            if (fii[i] == 0)
            {
                gasit = false;
                fii[i]--;
                if (t[i] != -1)
                    fii[t[i]]--;
                k[nr++] = t[i];
                break;
            }
        }
    }
}

int main() {
    int n, x;
    fin >> n;

    for (int i = 0; i < n; i++)
        fii[i] = 0;

    for (int i = 0; i < n; i++) {
        fin >> x;
        t[i] = x;
        if (t[i] != -1)
            fii[t[i]]++;
    }

    codarePrufer(k, fii, t, n, nr);

    fout << nr-1 << "\n";
    for (int i = 0; i < nr-1; i++)
        fout << k[i] << " ";
    fout << "\n";

    fin.close();
    fout.close();
    return 0;
}