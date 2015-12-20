#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct LOC
{
	unsigned int n;
	string lineOfCode;
};

class block
{
	public:
		block(vector<LOC> code, unsigned int block = 0);
		unsigned int startLine();
		unsigned int endLine();
		string getCode(int beg = -1, int end = -1);
		string printBlock();
		void setCode(vector<LOC> code);
		void addToFromList(unsigned int n);
		set<unsigned int> getFromList();
		void addToToList(unsigned int n);
		set<unsigned int> getToList();
		void setBlockNo(unsigned int block);
		unsigned int getBlockNo();
		bool hasPathFrom(unsigned int block);
		bool hasPathTo(unsigned int block);
		bool hasLine(string code);
		bool hasLine(unsigned int n);
		set<unsigned int> getDom();
		void setDom(unsigned int n);
		void setDom(set<unsigned int> n);
	private:
		vector<LOC> tac;
		unsigned int start, end, blockNo;
		set<unsigned int> from;
		set<unsigned int> to;
		set<unsigned int> dominator;

		int countSubstring(const string &str, const string &sub);
};

#endif // BLOCK_H
