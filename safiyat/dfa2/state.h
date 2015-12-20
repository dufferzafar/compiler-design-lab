#ifndef STATE_H
#define STATE_H

#include <iostream>

struct transition;

class state
{
		static int sCount;
		char op;
		bool finalState;
		int tCount;
		struct transition *transitionTable;
	public:
		state();
		state *transit(std::string);
		void populate(std::ifstream &);
		bool isFinalState();
		char output();
};

struct globalRef
{
	char stateName;
	state *addr;
};

struct transition
{
	char ip;
	char t;
};

#endif // STATE_H
