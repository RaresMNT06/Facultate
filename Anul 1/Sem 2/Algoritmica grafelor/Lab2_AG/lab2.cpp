#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ifstream fin("lab2.txt");

    int n, m;
    fin >> n >> m;


    vector<vector<int>> graf(n + 1);

    int x, y;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y;
        graf[x].push_back(y);
    }

    int s;
    fin >> s;

    vector<int> dist(n + 1, -1);
    vector<int> parinte(n + 1, 0);

    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int vecin : graf[v])
        {
            if (dist[vecin] == -1)
            {
                dist[vecin] = dist[v] + 1;
                parinte[vecin] = v;
                q.push(vecin);
            }
        }
    }

    cout << "V  D  P\n";

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] != -1)
            cout << i << " " << dist[i] << " " << parinte[i] << endl;
    }

    return 0;
}