#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define EMPTY -99

#define STATE 4
#define ALPHA 3

#define INPUT_FILE ("lex_input.txt")
#define AUTOMATA ("automata_input.txt")

int automata[STATE][ALPHA];
int initial;
int final[STATE];
int state;

int main() {
    int i, j;
    const char *inval;
    int flag = 0;
    ifstream in(AUTOMATA);
    for (i = 0; i < STATE; i++) {
        final[i] = EMPTY;
    }
    string line;
    getline(in, line);
    initial = atoi(line.c_str());
    getline(in, line);
    istringstream line_stream(line);
    string cell;
    i = 0;
    while (getline(line_stream, cell, ' ')) {
        final[i] = atoi(cell.c_str());
        i++;
    }
    i = 0;
    while (getline(in, line)) {
        istringstream line_stream(line);
        string cell;
        j = 0;
        while (getline(line_stream, cell, ' ')) {
            automata[i][j] = atoi(cell.c_str());
            j++;
        }
        i++;
    }
    cout << "Automata : \n\n";
    cout << "\t[A-Z],[a-z],_\t[0-9]\t\tSpl\n";
    for (i = 0; i < STATE; i++) {
        cout << "q" << i << "\t";
        for (j = 0; j < ALPHA; j++) {
            cout << automata[i][j] << "\t\t";
        }
        cout << endl;
    }
    cout << "\n\n";
    ifstream input(INPUT_FILE);
    while (getline(input, line)) {
        inval = line.c_str();
        cout << inval;
        state = initial;
        flag = 0;
        for (i = 0; inval[i] != '\0'; i++) {
            if ((inval[i] >= 'a' && inval[i] <= 'z') || (inval[i] >= 'A' &&
                    inval[i] <= 'Z') || inval[i] == '_') {
                state = automata[state][0];
            } else if (inval[i] >= '0' && inval[i] <= '9') {
                state = automata[state][1];
            } else {
                cout << "\t\tInvalid Input";
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            cout << "\t\tRejected --\n";
        } else {
            if (state == 1) {
                cout << "\t\tId\t\tAccepted ++\n";
            } else if (state == 2) {
                cout << "\t\tNum\t\tAccepted ++\n";
            } else {
                cout << "\t\tInvalid Input\t\tRejected --\n";
            }
        }
    }
}
