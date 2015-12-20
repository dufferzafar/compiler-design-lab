#include "block.h"

block::block(vector<LOC> code, unsigned int block)
{
	tac = code;
	vector<LOC>::iterator it;
	blockNo = block;
	it = tac.begin();
	start = it->n;
	it = tac.end();
	it--;
	end = it->n;
}

unsigned int block::startLine()
{
	return start;
}

unsigned int block::endLine()
{
	return end;
}

string block::getCode(int beg, int end)
{
	vector<LOC>::iterator it;
	if(beg == -1)
	{
		it = tac.begin();
		beg = it->n;
	}
	if(end == -1)
	{
		it = tac.end();
		it--;
		end = it->n;
	}
	string temp="";
	for(it = tac.begin(); it < tac.end(); it++)
	{
		if((it->n >= beg) && (it->n <=end))
			temp += "\t" + it->lineOfCode + "\n";
	}
	return temp;
}

void block::setCode(vector<LOC> code)
{
	vector<LOC>::iterator it;
	tac.clear();
	tac = code;
	it = tac.begin();
	start = it->n;
	it = tac.end();
	it--;
	end = it->n;
}



int block::countSubstring(const string& str, const string& sub)
{
	if(!sub.length())
		return 0;
	int count = 0;
	for(size_t offset = str.find(sub); offset != string::npos; offset = str.find(sub, offset+sub.length()))
		count++;
	return count;
}

void block::addToFromList(unsigned int n)
{
	from.insert(n);
}

void block::addToToList(unsigned int n)
{
	to.insert(n);
}

bool block::hasPathFrom(unsigned int block)
{
	if(from.find(block) != from.end())
		return true;
	return false;
}

bool block::hasPathTo(unsigned int block)
{
	if(to.find(block) != to.end())
		return true;
	return false;
}

bool block::hasLine(string code)
{
	string tac_text = getCode();
	if(tac_text.find(code) != string::npos)
		return true;
	return false;
}

bool block::hasLine(unsigned int n)
{
	if(n>=start && n<=end)
		return true;
	return false;
}

void block::setBlockNo(unsigned int block)
{
	blockNo = block;
}

unsigned int block::getBlockNo()
{
	return blockNo;
}

string block::printBlock()
{
	string text = "Block No. " + to_string(blockNo) + "\n";
	text += "From blocks:";
	for(set<unsigned int>::iterator it = from.begin(); it != from.end(); ++it)
		text += " " + to_string(*it);
	text += "\n";
	text += "Code:\n" + getCode();
	text += "To blocks: ";
	for(set<unsigned int>::iterator it = to.begin(); it != to.end(); ++it)
		text += " " + to_string(*it);
	text += "\n";
	text += "Dominators: ";
	for(set<unsigned int>::iterator it = dominator.begin(); it != dominator.end(); ++it)
		text += " " + to_string(*it);
	return text;
}

set<unsigned int> block::getDom()
{
	return dominator;
}

void block::setDom(unsigned int n)
{
	dominator.insert(n);
}

void block::setDom(set<unsigned int> n)
{
	dominator.insert(n.begin(), n.end());
}

set<unsigned int> block::getFromList()
{
	return from;
}

set<unsigned int> block::getToList()
{
	return to;
}
