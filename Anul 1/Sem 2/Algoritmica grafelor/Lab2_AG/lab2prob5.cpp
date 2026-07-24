#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("lab2.txt");

void dfs(vector<bool>& vizitare, vector<vector<int>>& matrice, int start, int n){

    vizitare[start] = true;
    cout << start << " ";

    for(int i = 1; i <= n; i++){
        if(matrice[start][i] == 1 && !vizitare[i]){
            dfs(vizitare, matrice, i, n);
        }
    }
}


int main(){
    int n, m;
    fin>>n>>m;

    vector<vector<int>> matrice(n+1, vector<int>(n+1, 0));
    vector<bool> vizitare(n+1, false);
    int x, y;
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            fin>>x>>y;
            matrice[x][y] = 1;
            matrice[y][x] = 1;
        }
    }

    for(int i = 1; i<=n; i++){
        if (vizitare[i] == false){
            dfs(vizitare, matrice, i, n);
            cout<<'\n';
        }

    }

    return 0;
}