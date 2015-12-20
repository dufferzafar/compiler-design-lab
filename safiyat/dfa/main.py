/*
 * Input File Format:
 *		1,1 0,2 ~ F
 *		~ 1,1 1,0
 *		~ 1,0 0,1 F
 *
 * The Nth line denotes transitions from the (N-1)th state.
 * Each transition is a comma separated pair of value.
 * The first one is the output from that transition-path, the second is the
 * state to transit to, from the current state.
 *
 * ~ denotes an absent transition.
 *
 * The input symbols start from 'a', beginning with the first column. The
 * second column denotes transitions on the input symbol 'b'.
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

	state q0;
	int index = 0;
	refTable = (struct globalRef *) malloc(sizeof(globalRef));
	refTable[0].addr = &q0;
	while(file)
	{
		refTable[index].addr->populate(file);
		index++;
	}

	cout << "Enter the test string: ";
	cin >> str;

	unsigned int i = 0;
	char ch;
	next = refTable[0].addr;
	cout << "Output: ";
	while(i < str.length())
	{
		ch = next->transit(str.substr(i));
		if(ch == '~')
		{
			cout << endl << "Invalid input!" << endl;
			return -1;
		}
		cout << ch;
		i++;
	}
	if(!next->isFinalState())
		cout << endl << "Test input is processed but final state not reached." << endl;
	else
		cout << endl << "Test input is processed and the final state reached." << endl;
	return 0;
}

