#ifndef STATE_H
#define STATE_H

#include <iostream>

struct transition;

class state
{
		static int sCount;
		bool finalState;
		int tCount;
		struct transition *transitionTable;
	public:
		state();
		char transit(std::string);
		void populate(std::ifstream &);
		bool isFinalState();
};

struct globalRef
{
	char stateName;
	state *addr;
};

struct transition
{
	char ip, op;
	state *t;
};

#endif // STATE_H
