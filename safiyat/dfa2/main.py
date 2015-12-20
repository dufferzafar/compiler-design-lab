/*
 * Input File Format:
 *	1 1 3 ~ 2 F
 *	0 ~ 2 1 0
 *	5 ~ ~ 3 1
 *	3 1 0 2 ~ F
 *
 * The Nth line denotes the output at the (N-1)th state and the transitions
 * from the (N-1)th state.
 * The first column is the state specific output.
 * Each following columns denote the state to transit to, upon respective input
 *
 * ~ denotes an absent transition.
 *
 * The input symbols start from 'a', beginning with the second column. The
 * third column denotes transitions on the input symbol 'b'.
 *
 * The first tuple will always give transitions from the initial state.
 * Each final state is denoted by an 'F' at the end of the tuple.
 *
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "state.h"

using namespace std;

extern struct globalRef *refTable;
extern state *next;

int main()
{
	string str;
	cout << "Enter the input file name: ";
	cin >> str;
	ifstream file(str.c_str());
	if(!file)
	{
		cout << "Error opening file!!!" << endl;
		return -1;
	}

//	state q0;
	int index = 0;
//	refTable = (struct globalRef *) malloc(sizeof(globalRef));
//	refTable[0].addr = &q0;
	while(file)
	{
		refTable = (struct globalRef *) realloc(refTable, sizeof(globalRef) * (index+1));
//		if(refTable[index].addr == NULL)
//			refTable[index].addr = new state;
		refTable[index].stateName = index + 48;
		refTable[index].addr = new state;
		refTable[index].addr->populate(file);
		index++;
	}

	cout << "Enter the test string: ";
	cin >> str;

	unsigned int i = 0;
	next = refTable[0].addr;
	cout << "Output: ";
	while(i < str.length())
	{
		cout << next->output();
		next = next->transit(str.substr(i));
		if(next == NULL)
		{
			cout << endl << "Invalid input!" << endl;
			return -1;
		}
		i++;
	}
	if(!next->isFinalState())
		cout << endl << "Test input is processed but final state not reached." << endl;
	else
		cout << endl << "Test input is processed and the final state reached." << endl;
	return 0;
}

