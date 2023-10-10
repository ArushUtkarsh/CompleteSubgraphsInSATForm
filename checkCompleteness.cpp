#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){

    string graphName = argv[1];
    string subgraphName = argv[2];
    ifstream graph(graphName, ios::in);
    ifstream subgraph(subgraphName, ios::in);

    int n,e;
    graph>>n>>e;
    vector<vector<int>> adj(n,vector<int>(n,0));
    for(int i=0;i<e;i++){
        int x,y;
        graph>>x>>y;
        adj[x-1][y-1] = 1;
        adj[y-1][x-1] = 1;
    }

    string line;
    subgraph>>line;
    vector<int> nodes;
    int val;
    while(subgraph>>val){
        nodes.push_back(val);
    }

    bool flag = true;

    for(int i=0;i<nodes.size();i++){
        for(int j=i+1;j<nodes.size();j++){
            if(adj[nodes[i]-1][nodes[j]-1] == 0){
                flag = false;
                break;
            }
        }
        if(flag == false)
            break;
    }

    if(flag == false)
        cout<<"NOT COMPLETE"<<endl;
    else
        cout<<"COMPLETE"<<endl;

    return 0;
}