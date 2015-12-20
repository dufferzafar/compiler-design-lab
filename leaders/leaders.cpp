/* Program to find Leaders and Basic Blocks for a given TAC
   input file : TAC.txt
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
	ifstream inp;
	inp.open("TAC.txt", ios::in);

	vector< string > tac;
	set<int> leaders;
	string line;

	leaders.insert(1);

	int line_number = 0;
	while(getline(inp, line)){
		// Save line
		tac.push_back(line);

		// Break the line into tokens
		// and find target of goto
		line_number++;
		istringstream line_stream(line);
		do {
			string token;
			line_stream >> token;
			if(token == "goto"){
				line_stream >> token;

				// Target of a goto label is a leader
				leaders.insert(atoi(token.c_str()));

				// Next line will also be a leader
				leaders.insert(line_number + 1);
			}
		} while (line_stream);
	}

	// Print Leaders
	set<int>::iterator it;
	cout << "Leaders are: \n";
	for(it = leaders.begin(); it!=leaders.end(); ++it){
		cout << *it << ", ";
	}
	cout << endl;

	// Print Basic Blocks
	cout << "\nBasic Blocks are:\n\n";

	int block_number = 1;
	for(int i=0; i<tac.size(); i++)
	{
		if(leaders.find(i+1) != leaders.end())
		{
			cout<<"\nBLOCK "<<block_number<<endl;
			block_number++;
		}

		cout << tac[i]<< " " << endl;
	}

	return 0;
}
