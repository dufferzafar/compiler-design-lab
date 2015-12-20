/* Program to find Leaders and Basic Blocks for a given TAC
   input file : TAC.txt
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<string>
#include<sstream>
#include<cstdlib>
#include<algorithm>
using namespace std;

int main(){
	ifstream inp;
	inp.open("TAC.txt", ios::in);
	string stat;
	vector< vector<string> > tac;
	set<int> leaders;
	int i=0;
	leaders.insert(1);
	while(getline(inp, stat)){
		i++;
		istringstream str(stat);
		vector<string> temp;
		do {
			string token;
			str>>token;
			temp.push_back(token);
			if(token == "goto"){
				leaders.insert(i+1);
				str>>token;
				temp.push_back(token);
				leaders.insert(atoi(token.c_str()));
			}
		}	while (str);
		tac.push_back(temp);
	}
	
	set<int>::iterator it;
	cout<<"Leaders are: \n";
	for(it = leaders.begin(); it!=leaders.end(); ++it){
		cout<<*it<<endl;
	}
	
	
	cout<<"\nBasic Blocks are:\n\n";
	int k=1; 
	for(i=0 ; i<tac.size(); i++){
		if(leaders.find(i+1)!=leaders.end())
			{cout<<"\nBLOCK "<<k<<endl; k++;}
			
		for(int j=0; j<tac[i].size(); j++){
			cout<<tac[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}
