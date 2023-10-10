#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){

    string inFileName = argv[1];
    string outFileName = argv[2];
    
    int n,e,k1,k2;
    ifstream inFile(inFileName, ios::in);
    inFile>>n;
    inFile>>e;
    inFile>>k1;
    inFile>>k2;
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

    int variables = 2*n + (n+1)*(k1+k2+2);
    int clauses = n + 2*(n*(n-1)/2-e) + (k1+1) + n*2 + n + n*k1*4 + 1 + (k2+1) + n*2 + n + n*(k2)*4 + 1;

    ofstream outFile(outFileName, ios::out);
    outFile<<"p cnf "<<variables<<" "<<clauses<<endl;

    int count = 0;

    
    int position = 0;       //Index of current dp grid base address


    //No node can be in both DAs
    for(int i=1;i<=n;i++){
        outFile<<-i<<" "<<-(i+n)<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;


    //No two nodes which don't share an edge can't be in same DA.
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            if(adj[i-1][j-1]==0){
                outFile<<-i<<" "<<-j<<" 0"<<endl;
                outFile<<-(i+n)<<" "<<-(j+n)<<" 0"<<endl;
                count+=2;
            }
        }
    }

    cout<<count<<endl;

    position = 2*n;

    //Adding dp grid base to formula as TRUE
    outFile<<position+1<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    //Adding first row of dp to formula as FALSE
    for(int i=position+2;i<=position+k1+1;i++){
        outFile<<-i<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values based on predecessor in same column when X[i] = False
    for(int i=1;i<=n;i++){
        outFile<<i<<" "<<-(position+(k1+1)*(i-1)+1)<<" "<<position+(k1+1)*i+1<<" 0"<<endl;
        outFile<<i<<" "<<position+(k1+1)*(i-1)+1<<" "<<-(position+(k1+1)*i+1)<<" 0"<<endl;
        count+=2;
    }

    cout<<count<<endl;

    //Initialising values of first column when X[i] = True
    for(int i=1;i<=n;i++){
        outFile<<-i<<" "<<-(position+(k1+1)*i+1)<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values of other columns when X[i] = True
    for(int i=1;i<=n;i++){
        for(int j=2;j<=k1+1;j++){
            outFile<<-i<<" "<<-(position+(k1+1)*(i-1)+j-1)<<" "<<position+(k1+1)*i+j<<" 0"<<endl;
            outFile<<-i<<" "<<position+(k1+1)*(i-1)+j-1<<" "<<-(position+(k1+1)*i+j)<<" 0"<<endl;
            outFile<<i<<" "<<-(position+(k1+1)*(i-1)+j)<<" "<<position+(k1+1)*i+j<<" 0"<<endl;
            outFile<<i<<" "<<position+(k1+1)*(i-1)+j<<" "<<-(position+(k1+1)*i+j)<<" 0"<<endl;
            count+=4;
        }
    }

    cout<<count<<endl;

    //Adding dp grid end to formula as TRUE
    outFile<<position+(n+1)*(k1+1)<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    position = 2*n + (n+1)*(k1+1);

    //Adding dp grid base to formula as TRUE
    outFile<<position+1<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    //Adding first row of dp to formula as FALSE
    for(int i=position+2;i<=position+k2+1;i++){
        outFile<<-i<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values based on predecessor in same column when X[i] = False
    for(int i=1;i<=n;i++){
        outFile<<i+n<<" "<<-(position+(k2+1)*(i-1)+1)<<" "<<position+(k2+1)*i+1<<" 0"<<endl;
        outFile<<i+n<<" "<<position+(k2+1)*(i-1)+1<<" "<<-(position+(k2+1)*i+1)<<" 0"<<endl;
        count+=2;
    }

    cout<<count<<endl;

    //Initialising values of first column when X[i] = True
    for(int i=1;i<=n;i++){
        outFile<<-(i+n)<<" "<<-(position+(k2+1)*i+1)<<" 0"<<endl;
        count++;
    }

    cout<<count<<endl;

    //Initialising values of other columns when X[i] = True
    for(int i=1;i<=n;i++){
        for(int j=2;j<=k2+1;j++){
            outFile<<-(i+n)<<" "<<-(position+(k2+1)*(i-1)+j-1)<<" "<<position+(k2+1)*i+j<<" 0"<<endl;
            outFile<<-(i+n)<<" "<<position+(k2+1)*(i-1)+j-1<<" "<<-(position+(k2+1)*i+j)<<" 0"<<endl;
            outFile<<i+n<<" "<<-(position+(k2+1)*(i-1)+j)<<" "<<position+(k2+1)*i+j<<" 0"<<endl;
            outFile<<i+n<<" "<<position+(k2+1)*(i-1)+j<<" "<<-(position+(k2+1)*i+j)<<" 0"<<endl;
            count+=4;
        }
    }

    cout<<count<<endl;

    //Adding dp grid end to formula as TRUE
    outFile<<position+(n+1)*(k2+1)<<" 0"<<endl;
    count++;
    cout<<count<<endl;

    return 0;
}