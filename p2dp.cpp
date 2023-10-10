#include<bits/stdc++.h>

using namespace std;

pair<int,vector<int>> runSAT( int n, int e, int k, vector<vector<int>> adj ){

    int variables = n + (n+1)*(k+1);
    int clauses = (n*(n-1)/2-e) + (k+1) + n*2 + n + n*k*4 + 1;

    ofstream outFile("temp.satinput", ios::out);
    outFile<<"p cnf "<<variables<<" "<<clauses<<endl;

    int count = 0;
    
    int position = 0;       //Index of current dp grid base address


    //No node can be in both DAs
    // for(int i=1;i<=n;i++){
    //     outFile<<-i<<" "<<-(i+n)<<" 0"<<endl;
    //     count++;
    // }

    // cout<<count<<endl;


    //No two nodes which don't share an edge can't be in same DA.
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            if(adj[i-1][j-1]==0){
                outFile<<-i<<" "<<-j<<" 0"<<endl;
                count++;
            }
        }
    }

    cout<<count<<endl;

    position = n;

    //Adding dp grid base to formula as TRUE
    outFile<<position+1<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    //Adding first row of dp to formula as FALSE
    for(int i=position+2;i<=position+k+1;i++){
        outFile<<-i<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values based on predecessor in same column when X[i] = False
    for(int i=1;i<=n;i++){
        outFile<<i<<" "<<-(position+(k+1)*(i-1)+1)<<" "<<position+(k+1)*i+1<<" 0"<<endl;
        outFile<<i<<" "<<position+(k+1)*(i-1)+1<<" "<<-(position+(k+1)*i+1)<<" 0"<<endl;
        count+=2;
    }

    cout<<count<<endl;

    //Initialising values of first column when X[i] = True
    for(int i=1;i<=n;i++){
        outFile<<-i<<" "<<-(position+(k+1)*i+1)<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values of other columns when X[i] = True
    for(int i=1;i<=n;i++){
        for(int j=2;j<=k+1;j++){
            outFile<<-i<<" "<<-(position+(k+1)*(i-1)+j-1)<<" "<<position+(k+1)*i+j<<" 0"<<endl;
            outFile<<-i<<" "<<position+(k+1)*(i-1)+j-1<<" "<<-(position+(k+1)*i+j)<<" 0"<<endl;
            outFile<<i<<" "<<-(position+(k+1)*(i-1)+j)<<" "<<position+(k+1)*i+j<<" 0"<<endl;
            outFile<<i<<" "<<position+(k+1)*(i-1)+j<<" "<<-(position+(k+1)*i+j)<<" 0"<<endl;
            count+=4;
        }
    }

    cout<<count<<endl;

    //Adding dp grid end to formula as TRUE
    outFile<<position+(n+1)*(k+1)<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    outFile.close();

    int err = system("minisat temp.satinput temp.satoutput");

    ifstream satFile("temp.satoutput", ios::in);

    string line;
    satFile>>line;

    vector<int> result;

    if(line=="UNSAT"){
        system("rm temp.satinput");
        system("rm temp.satoutput");
        return make_pair(0,result);
    }
    else{
        int val = 0;
        for(int i=0;i<n;i++){
            satFile>>val;
            if(val>0)
                result.push_back(val);
        }
        system("rm temp.satinput");
        system("rm temp.satoutput");
        return make_pair(1,result);
    }

}

int main(int argc, char** argv){

    string inFileName = argv[1];
    string outFileName = argv[2];
    ifstream inFile(inFileName, ios::in);
    ofstream outFile(outFileName, ios::out);

    int n,e;
    inFile>>n>>e;

    vector<vector<int>> adj(n, vector<int>(n,0));
    for(int i=0;i<e;i++){
        int x,y;
        inFile>>x>>y;
        adj[x-1][y-1] = 1;
        adj[y-1][x-1] = 1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }


    vector<int> result;
    for(int i=2;i<=n;i++){
        pair<int,vector<int>> res = runSAT(n, e, i, adj);
        if(res.first==0){
            if(i==2){
                outFile<<"#1"<<endl;
                outFile<<1<<endl;
            }
            else{
                outFile<<"#1"<<endl;
                for(int j=0;j<result.size();j++){
                    if(j<result.size()-1)
                        outFile<<result[j]<<" ";
                    else
                        outFile<<result[j]<<endl;
                }
                outFile<<endl;
            }
            break;
        }
        else{
            result = res.second;
            if(i==n){
                outFile<<"#1"<<endl;
                for(int j=0;j<result.size();j++){
                    if(j<result.size()-1)
                        outFile<<result[j]<<" ";
                    else
                        outFile<<result[j]<<endl;
                }
                outFile<<endl;
            }
        }
    }

    return 0;
}