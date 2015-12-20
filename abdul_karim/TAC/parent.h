#ifndef PARENT_H
#define PARENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include "block.h"

using namespace std;

class parent
{
	public:
		parent();
		parent(string fileName);
		void populate(string fileName);
		string printCode();
		string leaderList();
		string blocks();
		string printLoops();
	private:
		vector<block> graph;
		vector<LOC> code;
		list<int> leaders;

		bool myFunction(int i, int j);
};

#endif // PARENT_H
