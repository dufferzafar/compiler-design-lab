#include "parent.h"

parent::parent()
{

}

parent::parent(string fileName)
{
	populate(fileName);
}

void parent::populate(string fileName)
{
	char temp[32];
	LOC t1;
	int index = 0;
	ifstream file(fileName);
	if(!file)
	{
		cerr << "Error opening the input file: " << fileName << endl;
		return;
	}
	while (file)
	{
		file.getline(temp, 32);
		t1.n = ++index;
		t1.lineOfCode = temp;
		code.push_back(t1);
	}

	/*Find leaders*/
	set<int> tempLeaders;
	tempLeaders.insert(1);
	size_t locationOfGoto, locationOfAddress1, locationOfAddress2;
	string loc;
	int addr;
	for(int i = 0; i < code.size(); i++)
	{
		loc = code[i].lineOfCode;
		if((locationOfGoto = loc.find("goto")) != string::npos)
		{
			locationOfAddress1 = loc.find("(", locationOfGoto) + 1;
			locationOfAddress2 = loc.find(")", locationOfAddress1);
			addr = stoi(loc.substr(locationOfAddress1, locationOfAddress2 - locationOfAddress1));
			tempLeaders.insert(addr);
			tempLeaders.insert(i+2);
		}
	}
	for(set<int>::iterator it = tempLeaders.begin(); it != tempLeaders.end(); ++it)
		leaders.push_back(*it);
	leaders.sort();

	/*Create Blocks*/
	unsigned int start, end;
	string tempString;
	int blockNo = 1;
	for(list<int>::iterator it = leaders.begin(); it != leaders.end(); blockNo++)
	{
		start = *it;
		it++;
		if(it == leaders.end())
			end = code.size();
		else
			end = *it;
		vector<LOC> tempTAC;
		for(unsigned int i = start; i < end; i++)
		{
			tempTAC.push_back(code[i-1]);
		}
		graph.push_back(block(tempTAC, blockNo));
	}

	/*Link Blocks*/
	for(int i = 0; i < graph.size(); i++)
	{
		string text = graph[i].getCode(-1);
		if(text.find("if") != string::npos)
		{
			if(i+1 != graph.size())
			{
				graph[i].addToToList(i+2);
				graph[i+1].addToFromList(i+1);
			}
		}
		if(text.find("goto") != string::npos)
		{
			size_t locationOfGoto, locationOfAddress1, locationOfAddress2;
			locationOfGoto = text.find("goto");
			locationOfAddress1 = text.find("(", locationOfGoto) + 1;
			locationOfAddress2 = text.find(")", locationOfAddress1);
			int addr = stoi(text.substr(locationOfAddress1, locationOfAddress2 - locationOfAddress1));
			int j;
			for(j = 0; j < graph.size(); j++)
				if(graph[j].hasLine(addr))
					break;
			graph[i].addToToList(j+1);
			graph[j].addToFromList(i+1);
		}
		else
		{
			if(i+1 != graph.size())
			{
				graph[i].addToToList(i+2);
				graph[i+1].addToFromList(i+1);
			}
		}
	}

	/*Dominators*/
	graph[0].setDom(1);
	for(unsigned int k = 1; k < graph.size(); k++)
	{
		set<unsigned int> tempFromList = graph[k].getFromList();
		set<unsigned int> resultant, temp1, temp2;
		for(unsigned int i = 1; i < 100; i++)
			resultant.insert(i);
		for(set<unsigned int>::iterator its = tempFromList.begin(); its != tempFromList.end(); ++its)	//************
		{
			if(*its > k)
				continue;
			temp1.clear();
			temp1 = resultant;
			temp2 = graph[*its - 1].getDom();
			resultant.clear();
			set_intersection(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), inserter(resultant, resultant.begin()));
		}
		resultant.insert(k+1);
		graph[k].setDom(resultant);
	}
}

string parent::printCode()
{
	string text="", temp;

	for(int i = 0; i < code.size(); i++)
	{
		temp = to_string(code[i].n) + ":\t" + code[i].lineOfCode + "\n";
		text.append(temp);
	}
	return text;
}

bool parent::myFunction(int i, int j)
{
	return (i==j);
}

string parent::leaderList()
{
	string text="", temp;
	for(list<int>::iterator it = leaders.begin(); it != leaders.end(); ++it)
	{
		temp = to_string(*it) + " ";
		text.append(temp);
	}
	return text;
}

string parent::blocks()
{
	string text="";
	for(int i = 0; i < graph.size(); i++)
	{
		text.append(graph[i].printBlock());
		text.append("\n\n");
	}
	return text;
}

string parent::printLoops()
{
	string text = "";
	for(int i = 0; i < graph.size(); i++)
	{
		set<unsigned int> dom, to, resultant;
		to = graph[i].getToList();
		dom = graph[i].getDom();
		resultant.clear();
		set_intersection(to.begin(), to.end(), dom.begin(), dom.end(), inserter(resultant, resultant.begin()));
		if(resultant.size())
		{
			text += "\nLoops from " + to_string(i+1) + ": ";
			for(set<unsigned int>::iterator it = resultant.begin(); it != resultant.end(); ++it)
				text += " " + to_string(*it);
		}
	}
	text += "\n";
	return text;
}
