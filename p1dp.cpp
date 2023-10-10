#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){

    string inFile = argv[1];
    
    int n,e,k1,k2;
    ifstream file(inFile, ios::in);
    file>>n;
    file>>e;
    file>>k1;
    file>>k2;
    vector<vector<int>> adj(n, vector<int>(n,0));
    for(int i=0;i<e;i++){
        int x,y;
        file>>x>>y;
        adj[x-1][y-1] = 1;
        adj[y-1][x-1] = 1;
    }

    vector<bool> cliquek1(n,false);     //represented by 1, n
    vector<bool> cliquek2(n,false);     //represented by n+1, 2n

    vector<vector<int>> formula;
    for(int i=1;i<=n;i++){
        vector<int> clause{-i,-(i+n)};
        formula.push_back(clause);
    }

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(adj[i][j]==1){
                vector<int> clause1{-i,-j};
                vector<int> clause2{-(i+n),-(j+n)};
                formula.push_back(clause1);
                formula.push_back(clause2);
            }
        }
    }

    


    return 0;
}