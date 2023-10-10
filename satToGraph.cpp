#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){
    string inFileName = argv[1];
    string graphFileName = argv[2];
    string outFileName = argv[3];
    ifstream graphFile(graphFileName, ios::in);
    ifstream inFile(inFileName, ios::in);
    ofstream outFile(outFileName, ios::out);

    int n,e,k1,k2;
    graphFile>>n>>e>>k1>>k2;

    string line;
    inFile>>line;
    cout<<line<<endl;
    int printed = 0;
    if(line=="UNSAT"){
        outFile<<0<<endl;
    }
    else{
        outFile<<"#1"<<endl;
        int val = 0;
        for(int i=0;i<n;i++){
            inFile>>val;
            cout<<val<<endl;
            if(val>0){
                printed++;
                if(printed<k1)
                    outFile<<i+1<<" ";
                else
                    outFile<<i+1<<endl;
            }
        }
        outFile<<"#2"<<endl;
        for(int i=0;i<n;i++){
            inFile>>val;
            cout<<val<<endl;
            if(val>0){
                printed++;
                if(printed<k1+k2)
                    outFile<<i+1<<" ";
                else
                    outFile<<i+1<<endl;
            }
        }
    }
    
    return 0;
}