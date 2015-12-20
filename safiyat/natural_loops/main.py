/*
 * Refer page number 625 for algorithm.
 * Kill and Gen sets are required for it to work.
 */

#include <iostream>
#include "parent.h"

using namespace std;

int main()
{
	string fileName;
	cout << "Enter the source file name: ";
	cin >> fileName;
	parent program(fileName);
	cout << "Code: \n" << program.printCode() << endl;
	cout << "\nLeaders: " << program.leaderList() << endl;
	cout << "\nBlocks:\n" << program.blocks() << endl;
	cout << "\nLoops:" << program.printLoops() << endl;
	return 0;
}

