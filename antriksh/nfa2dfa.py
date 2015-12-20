#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define EMPTY -99

#define STATE 3
#define ALPHA 2

#define INPUT_FILE ("innfa.txt")

int nfa[STATE][ALPHA][STATE];
int dfa[20][20];
int initial;
int final[STATE];
int state, NEWSTATE = STATE;

int *OR(int *a, int *b){
	int *c;
	c = (int*)malloc(sizeof(int)*STATE);
	for (int i = 0; i < STATE; i++){
		c[i] = EMPTY;
	}
	for(int i=0;i<NEWSTATE;i++){
		c[i] = a[i] | b[i] ;
	}
	return c;
}

int value(int *a){
	int opval=0;
	for (int i = 0; i < STATE; i++){
		if(a[i]!=EMPTY)
			opval += a[i]*pow(2,i);
	}
	return opval;
}

int convert_back(int a){
	int b[STATE];
	for(int i=0;i<STATE;i++)
		b[i]=EMPTY;
	int i=0;
	while(a>=1){
		if(a%2==1){
			cout<<i<<",";
		}
		a = a/2;
		i++;
	}
}

int convert(int a){
	int b[STATE];
	for(int i=0;i<STATE;i++)
		b[i]=EMPTY;
	b[a] = 1;
	return value(b);
}

int check_new(int i, int j){
	int k;
	for(k=0;k<STATE;k++){
		if(dfa[i][j]==k){
			return 0;
		}
	}
	return 1;
}

int main(){
	int i,j,k;
	const char *inval;
	int *prev;
	int flag=0;

	prev = (int*)malloc(sizeof(int)*20);

	ifstream in(INPUT_FILE);

	for(i=0;i<STATE;i++){
		final[i]=EMPTY;
	}

	for(i=0;i<STATE;i++)
		for(j=0;j<ALPHA;j++)
			for(k=0;k<STATE;k++)
				nfa[i][j][k] = EMPTY;

	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			dfa[i][j] = EMPTY;

	string line;

	getline(in,line);
	initial = atoi(line.c_str());

	getline(in,line);
	istringstream line_stream(line);
	string cell;
	i=0;
	while(getline(line_stream,cell,' ')){
		final[i] = atoi(cell.c_str());
		i++;
	}

	i=0;
	while(getline(in,line)){

		istringstream line_stream(line);
		string cell;

		j=0;
		while(getline(line_stream,cell,' ')){

			istringstream cell_stream(cell);
			string val;

			while(getline(cell_stream,val,',')){
				nfa[i][j][atoi(val.c_str())] = 1;
			}
			j++;
		}
		i++;
	}

	cout<<"\nIndefinite Automata :\n\ta\tb\n";
	for(i=0;i<STATE;i++){
		cout<<i;
		for(j=0;j<ALPHA;j++){
			cout<<"\t";
			for(k=0;k<STATE;k++)
				if(nfa[i][j][k]==1){
					cout<<k<<",";
				}
		}
		cout<<endl;
	}

	for(i=0;i<STATE;i++){
		for(j=0;j<ALPHA;j++){
			dfa[i][j] = value(nfa[i][j]);
		}
	}

	for(i=0;i<NEWSTATE;i++){
		for(j=0;j<ALPHA;j++){
			if(check_new(i,j)){
				NEWSTATE++;
				prev = '\0';
				for(k=0;k<STATE;k++){
					prev = OR(prev, nfa[k][j]);
				}
				dfa[NEWSTATE][j] = value(prev);
			}
			else
				dfa[i][j] = nfa[i][j][0];
		}
	}

	cout<<"\ta\tb\n";
	for(i=0;i<NEWSTATE;i++){
		cout<<i<<"\t";
		for(j=0;j<ALPHA;j++)
			cout<<dfa[i][j]<<"\t";
		cout<<endl;
	}
}