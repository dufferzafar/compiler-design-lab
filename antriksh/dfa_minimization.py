#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define EMPTY -99

#define STATE 8
#define ALPHA 2

#define INPUT_FILE ("input_dfa.txt")

int dfa[STATE][ALPHA];
int initial;
int final[STATE];
int is_same[STATE][STATE], is_final[STATE];
int present[STATE][STATE];


int check_same(int a, int b){
	vector<int> is;
	if(is_same[a][b]!=0)
		return is_same[a][b];
	if(present[a][b]!=EMPTY || present[b][a]!=EMPTY)
		return 1;
	present[a][b]=present[b][a]=1;
	for(int i=0;i<ALPHA;i++){
		int x= dfa[a][i];
		int y = dfa[b][i];
		int za=check_same(x, y);
        if(za==-1){
            is_same[a][b]=-1;
            is_same[b][a] = -1;
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
	    if(!flag) 
	    	is_same[b][a]=is_same[a][b]=1;
	    else
	    	is_same[b][a]=is_same[a][b]=-1;
    }
    return  is_same[a][b];
}

int main(){
	int i,j,k;
	ifstream in(INPUT_FILE);

	for(i=0;i<STATE;i++){
		final[i]=EMPTY;
	}

	for(i=0;i<STATE;i++)
		for(j=0;j<STATE;j++){
			dfa[i][j] = EMPTY;
			present[i][j] = EMPTY;
		}

	string line;

	getline(in,line);
	initial = atoi(line.c_str());

	getline(in,line);
	istringstream line_stream(line);
	string cell;
	i=0;
	while(getline(line_stream,cell,' ')){
		final[i] = atoi(cell.c_str());
		is_final[atoi(cell.c_str())] = 1;
		i++;
	}

	i=0;
	while(getline(in,line)){

		istringstream line_stream(line);
		string cell;

		j=0;
		while(getline(line_stream,cell,' ')){
			dfa[i][j] = atoi(cell.c_str());
			j++;
		}
		i++;
	}

	for(i=0;i<STATE;i++)			// Initialise table with 0s
		for(j=0;j<=i;j++)
			is_same[i][j] = 0;

	for(i=0;i<STATE;i++){			// All non-final and final combinations initialised -1
        if(is_final[i]){
            for(j=0;j<STATE;j++){
                if(!is_final[j])
                {
                    is_same[i][j]=-1;
                    is_same[j][i]=-1;
                }
            }
        }
        is_same[i][i]=1;
    }

    for(i=0;i<STATE;i++){			// Solving for each combination left
    	for(j=0;j<STATE;j++){
    		if(is_same[i][j]==0)
    			check_same(i,j);
    	}
    }

    cout<<"AUTOMATA : \n\ta\tb";
    for(i=0;i<STATE;i++){
    	cout<< endl << i << "\t" ;
		for(j=0;j<ALPHA;j++)
			cout << dfa[i][j] << "\t";
    }

    cout<<"\n\nMinimisation Table :\n";					// Minimisation Table
    for(i=0;i<STATE;i++){
    	cout<<endl<<i<<"\t";
    	for(j=0;j<=i;j++)
    		cout<<is_same[i][j]<<"\t";
    }
    cout << endl;
    for(i=0;i<STATE;i++)
    	cout<<"\t"<<i;

    cout<< "\n\nAll the same states : \n";				// Same States
    for(i=0;i<STATE;i++){
    	for(j=0;j<i;j++)
    		if(is_same[i][j]==1)
    			cout << i << " " << j << endl;
    }

    cout<<"\n\n";
}