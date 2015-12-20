#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
using namespace std;
vector<pair<int,int> >pp;
int is_same[100][100],matrix[100][100];
int transitions;
int initial_state,is_final[100],x,present[100][100];
vector<int>v;
int alpha;
int solve(int A,int B){
    int x,y;
    //cout<<A<<" "<<B<<endl;
    vector<int>is;
    if(is_same[A][B]!=0) {
        //cout<<A<<"=="<<B<<endl;    
    return is_same[A][B];} 
    if(present[A][B] || present[B][A]) return 1;
    present[A][B]=present[B][A]=1;
    for(int i=0;i<alpha;i++){
        x=matrix[A][i],y=matrix[B][i];
        int za=solve(x, y);
        //cout<<A<<" "<<B<<"="<<za<<endl;
        if(za==-1){
            is_same[A][B]=-1;
            is_same[B][A]=-1;
            return -1;
        }
        is.push_back(za);
    }
    int flag=0;
    for(int i=0;i<is.size();i++){
        if(is[i]!=1){
            flag=1;
            break;
        }
    }
    if(is.size()>0){
    if(!flag) is_same[B][A]=is_same[A][B]=1;
    else is_same[B][A]=is_same[A][B]=-1;
    }
        //cout<<A<<" "<<B<<"="<<is_same[A][B]<<endl;
    return  is_same[A][B];
}

int main (int argc, const char * argv[])
{
    ifstream fin("inputsahil.txt");
    fin>>initial_state;
    fin>>transitions;
    fin>>x;
    for (int i=0; i<x; i++) {
        int y;
        fin>>y;
        is_final[y]=1;
    }
    
    for(int i=0;i<100;i++) for(int j=0;j<100;j++) matrix[i][j]=-1;
    cout<<"Tabular Matrix\n";
    printf("-----------\n");
    cout<<transitions<<endl;
    for (int i=0;i<transitions; i++) {
        fin>>x;
        alpha=max(alpha,x);
        for (int j=0; j<x; j++) {
            int y;
            fin>>y;
            matrix[i][j]=y;
            cout<<matrix[i][j]<<" ";
        }
        printf("\n");
    }
    
    for(int i=0;i<100;i++){
        if(is_final[i]){
            for(int j=0;j<transitions;j++){
                if(!is_final[j])
                {
                    is_same[i][j]=-1;
                    is_same[j][i]=-1;
                }
            }
        }
        is_same[i][i]=1;
    }
    for(int j=0;j<transitions;j++){
        for(int k=0;k<j;k++){
            if(is_same[j][k]==0)
                solve(j,k);
        }
    }
    printf("\n");
    bool check[100]={0};
    cout<<"Same States are\n";
    for(int i=0;i<transitions;i++){
        if(!check[i]){
            cout<<i<<" ";
        for(int j=0;j<transitions;j++){
            if( i!=j && is_same[i][j]==1){
                cout<<j<<" ";
                check[j]=1;
            }
        }
            printf("\n");

        }
    }

    cout<<"\n";                 // Minimisation Table
    for(int i=0;i<transitions;i++){
        cout<<endl<<i<<"\t";
        for(int j=0;j<=i;j++)
            cout<<is_same[i][j]<<"\t";
    }
    cout << endl;
    for(int i=0;i<transitions;i++)
        cout<<"\t"<<i;

    cout<<"\n\n";
    
    return 0;
}