#include "state.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

struct globalRef *refTable = NULL;

state *current = NULL, *next = NULL;

int state::sCount = 0;

state::state() {
    sCount++;
    finalState = false;
    tCount = 0;
    transitionTable = NULL;
}

char state::transit(std::string p) {
    int i;
    for (i = 0; i < tCount; i++) {
        if (transitionTable[i].ip == p[0]) {
            next = transitionTable[i].t;
            return transitionTable[i].op;
        }
    }
    return '~';
}

void state::populate(std::ifstream &file) {
    char row[50], *p, temp[5];
    char ipSymbol = 'a', ip, op;
    int s;
    file.getline(row, 50);
    p = row;
    while (*p != '\0') {
        std::sscanf(p, "%s", temp);
        if (temp[0] == '~') {
        } else if (temp[0] == 'F') {
            finalState = true;
        } else {
            tCount++;
            ip = ipSymbol;
            op = temp[0];
            s = temp[2] - 48;
            transitionTable = (struct transition *) std::realloc(transitionTable,
                              sizeof(transition) * tCount);
            transitionTable[tCount - 1].ip = ip;
            transitionTable[tCount - 1].op = op;
            if (s < sCount) {	//Transiting to a preceding state
                transitionTable[tCount - 1].t = refTable[s].addr;
            } else {
                refTable = (struct globalRef *) std::realloc(refTable,
                           sizeof(globalRef) * (s + 1));
                transitionTable[tCount - 1].t = refTable[s].addr = new state;
            }
        }
        while (*p != ' ') {
            if (*p == '\0') {
                p--;
                break;
            }
            p++;
        }
        p++;
        ipSymbol++;
    }
}

bool state::isFinalState() {
    return finalState;
}
