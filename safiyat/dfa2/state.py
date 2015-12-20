#include "state.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

struct globalRef *refTable = NULL;

state *current = NULL, *next = NULL;

int state::sCount = 0;

state::state()
{
	sCount++;
	finalState = false;
	tCount = 0;
	transitionTable = NULL;
}

state *state::transit(std::string p)
{
	int i;
	for(i = 0; i < tCount; i++)
	{
		if(transitionTable[i].ip == p[0])
		{
			break;
		}
	}
	if(i == tCount)
		return NULL;
	for(int j = 0; j < sCount; j++)
	{
		if(transitionTable[i].t == refTable[j].stateName)
			return refTable[j].addr;
	}
	return NULL;
}

void state::populate(std::ifstream &file)
{
	char row[50], *p, temp[5];
	char ipSymbol = 'a', ip;
	int s;
	file.get(op);
	file.get();
	file.getline(row, 50);
	p = row;
	while(*p!='\0')
	{
		std::sscanf(p, "%s", temp);
		if(temp[0] == '~')
		{
		}
		else if(temp[0] == 'F')
		{
			finalState = true;
		}
		else
		{
			tCount++;
			ip = ipSymbol;
			s = temp[0] - 48;
			transitionTable = (struct transition *) std::realloc(transitionTable, sizeof(transition) * tCount);
			transitionTable[tCount - 1].ip = ip;
			transitionTable[tCount - 1].t = s + 48;
			/*
			if(s < sCount)		//Transiting to a preceding state
			{
				transitionTable[tCount - 1].t = s + 48;
			}
			else
			{
				refTable = (struct globalRef *) std::realloc(refTable, sizeof(globalRef) * (s+1));
//				refTable[s].addr = new state;
				transitionTable[tCount - 1].t = refTable[s].stateName = s + 48;
			}
			*/
		}

		while(*p != ' ')
		{
			if(*p == '\0')
			{
				p--;
				break;
			}
			p++;
		}
		p++;

		ipSymbol++;
	}
}

bool state::isFinalState()
{
	return finalState;
}

char state::output()
{
	return op;
}
