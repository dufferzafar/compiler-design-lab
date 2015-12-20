#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

char nfa[10][10][10], sname[10][10], final[10];
int n = 0, m = 0, fc, q, nt;

int read() {
    ifstream fin;
    fin.open("kcd4.txt", ios::in);
    int i, j, k;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
            sname[i][j] = '\0';
            for (k = 0; k < 10; k++) {
                nfa[i][j][k] = '\0';
            }
        }
    i = j = k = 0;
    char ch;
    fin.get(ch);
    do {
        m++;
        fin.get(ch);
    } while (ch != '\n');
    while (fin.get(ch)) {
        if (ch == '\n') {
            sname[i][0] = char(i + 48);
            i++;
            j = k = 0;
        } else if (ch == '#') {
            n = i;
            nt = n;
            i = 0;
            fin.get(ch);
            q = ch - '0';
            fin.get(ch);
            while (fin.get(ch)) {
                final[i++] = ch;
            }
            fc = i;
            return 1;
        } else if (ch == ',') {
            k++;
            nfa[i][j][k] = ch;
        } else if (ch == ' ') {
            j++;
            k = 0;
        } else {
            nfa[i][j][k] = ch;
        }
    }
    return 0;
}
int sort() {
    int i, j, k, l;
    char ch;
    for (j = 0; j < m; j++) {
        for (k = 0; nfa[nt][j][k] != '\0'; k++) {
            for (l = k + 1; nfa[nt][j][l] != '\0'; l++) {
                if (nfa[nt][j][l] == nfa[nt][j][k] || nfa[nt][j][l] == '-') {
                    for (i = l; nfa[nt][j][i] != '\0'; i++) {
                        nfa[nt][j][i] = nfa[nt][j][i + 1];
                    }
                } else if (nfa[nt][j][l] < nfa[nt][j][k]) {
                    ch = nfa[nt][j][l];
                    nfa[nt][j][l] = nfa[nt][j][k];
                    nfa[nt][j][k] = ch;
                }
            }
        }
    }
}
int add_state(int i, int j) {
    int j1, k, k1;
    for (j1 = 0; j1 < m; j1++) {
        nfa[nt][j1][0] = '\0';
        for (k = 0; nfa[i][j][k] != '\0'; k++) {
            k1 = nfa[i][j][k] - '0';
            strcat(nfa[nt][j1], nfa[k1][j1]);
        }
        if (nfa[nt][j][0] == '\0') {
            nfa[nt][j][0] = '-';
        }
    }
    sort();
    int flag = 0;
    for (i = 0; i < nt; i++) {
        if (strcmp(sname[i], sname[nt]) == 0) {
            flag = 1;
        }
    }
    if (flag == 0) {
        nt++;
    }
}
int nfa2dfa() {
    int i, j, k, t1, t2, flag;
    for (i = 0; i < nt; i++) {
        for (j = 0; j < m; j++) {
            if (nfa[i][j][1] != '\0') {
                strcpy(sname[nt], nfa[i][j]);
                add_state(i, j);
            }
        }
    }
}

void print() {
    int i, j, k;
    for (i = 0; i < nt; i++) {
        cout << endl;
        cout << sname[i];
        for (j = 0; j < m; j++) {
            for (k = 0; nfa[i][j][k] != '\0'; k++) {
                if (k == 0) {
                    cout << "\t" << nfa[i][j][k];
                } else {
                    cout << "," << nfa[i][j][k];
                }
            }
        }
    }
}

int main() {
    read();
    cout << "NFA read is:\n";
    print();
    cout << "\n\nDFA formed is:\n";
    nfa2dfa();
    print();
}
