#include<iostream>
#include<fstream>

using namespace std;

int line[30], llen = 0, len, leaders[20], blocks[20][2], gen[20][50],
              kill[20][50], cfg[20][20], in[20][50], out[20][50];
char tac[50][50];

void read() {
    ifstream fin;
    fin.open("inouttxt.txt", ios::in);
    char ch;
    int num = 0;
    llen = 0;
    fin.get(ch);
    int i = 0, j = 0, flag = 0;
    while (ch != '\n') {
        if (ch == ' ') {
            leaders[llen++] = num;
            num = 0;
        } else {
            num = num * 10 + (ch - '0');
        }
        fin.get(ch);
    }
    leaders[llen++] = num;
    i = 0;
    j = 0;
    fin.get(ch);
    while (1) {
        if (ch == '\n') {
            i++;
            j = 0;
        } else if (ch != ' ') {
            cfg[i][j++] = ch - '0';
        }
        if (i == llen) {
            break;
        }
        fin.get(ch);
    }
    cout << llen;
    i = j = 0;
    num = 0;
    cout << ch;
    fflush(stdin);
    flag = 0;
    while (fin.get(ch)) {
        cout << ch;
        if (ch == '\n') {
            flag = 0;
            tac[i][j] = '\0';
            j = 0;
            i++;
        } else if (ch == ':') {
            flag = 1;
            j = 0;
            line[i] = num;
            num = 0;
        } else if (!flag) {
            num = num * 10 + (ch - '0');
        } else {
            tac[i][j++] = ch;
        }
    }
    cout << line[0];
    tac[i][j] = '\0';
    len = i + 1;
}

int findindex(int num) {
    for (int i = 0; i < len; i++) {
        if (num == line[i]) {
            return i;
        }
    }
    return -1;
}

void mkblocks() {
    int i, j;
    cout << line[0] << "\t1";
    for (i = 0; i < llen; i++) {
        blocks[i][0] = findindex(leaders[i]);
        if ((i + 1) != llen) {
            blocks[i][1] = findindex(leaders[i + 1] - 1);
        } else {
            blocks[i][1] = len - 1;
        }
    }
    for (i = 0; i < llen; i++) {
        cout << "\nBlock: " << blocks[i][0] << "- " << blocks[i][1];
    }
}

int find(char *str) {
    int i = 0;
    while (*(str + i) != '\0') {
        if (*(str + i) == '=') {
            return 1;
        }
        i++;
    }
    return 0;
}


void gen_gen() {
    int i, j;
    for (i = 0; i < llen; i++) {
        for (j = 0; j < 50; j++) {
            gen[i][j] = 0;
        }
    }
    for (i = 0; i < llen; i++) {
        for (j = 0; j <= len; j++) {
            if (j >= blocks[i][0] && j <= blocks[i][1]) {
                int flag = find(tac[j]);
                if (flag) {
                    gen[i][j] = 1;
                }
            }
        }
    }
    cout << "\nGen Matrix is: \n";
    for (i = 0; i < llen; i++) {
        cout << "\n";
        for (j = 0; j < len; j++) {
            cout << gen[i][j] << "\t";
        }
    }
}

void gen_kill() {
    int i, j, k, m, flag = 0;
    for (i = 0; i < llen; i++) {
        for (j = 0; j < 50; j++) {
            kill[i][j] = 0;
        }
    }
    for (i = 0; i < llen; i++) {
        for (k = blocks[i][0]; k <= blocks[i][1]; k++) {
            for (j = 0; j < len; j++) {
                if (j < blocks[i][0] || j > blocks[i][1]) {
                    int flag1 = find(tac[j]);
                    int flag2 = find(tac[k]);
                    if (flag1 && flag2) {
                        flag = 1;
                        for (m = 0; tac[j][m] != '=' && tac[k][m] != '='; m++) {
                            if (tac[j][m] != tac[k][m]) {
                                flag = 0;
                                break;
                            }
                        }
                        if (tac[j][m] == '=' && tac[k][m] == '=' && flag) {
                            kill[i][j] = 1;
                        }
                    }
                }
            }
        }
    }
    cout << "\nKill: \n";
    for (i = 0; i < llen; i++) {
        cout << "\n";
        for (j = 0; j < len; j++) {
            cout << kill[i][j] << "\t";
        }
    }
}

void dounion(int i, int j) {
    int m, n;
    for (m = 0; m < len; m++) {
        in[i][m] = in[i][m] | out[j][m];
    }
}

void calcout(int index) {
    int i, j;
    int temp[50];
    for (j = 0; j < len; j++) {
        if (in[index][j]) {
            temp[j] = in[index][j] - kill[index][j];
        } else {
            temp[j] = 0;
        }
    }
    for (j = 0; j < len; j++) {
        out[index][j] = gen[index][j] | temp[j];
    }
}

void inout() {
    int i, j, k;
    for (i = 0; i < llen; i++) {
        for (j = 0; j < len; j++) {
            in[i][j] = 0;
            out[i][j] = gen[i][j];
        }
    }
    int flag = 1;
    while (flag) {
        flag = 0;
        for (i = 0; i < llen; i++) {
            for (j = 0; j < llen; j++) {
                if (cfg[j][i] == 1) {
                    //cout<<i<<" "<<j<<"\t";
                    dounion(i, j);
                }
            }
            int oldout[50];
            for (j = 0; j < len; j++) {
                oldout[j] = out[i][j];
            }
            calcout(i);
            for (j = 0; j < len; j++) {
                if (oldout[j] != out[i][j]) {
                    flag = 1;
                }
            }
        }
    }
    cout << "\nINOUT\n\n";
    for (i = 0; i < llen; i++) {
        cout << "\n";
        for (j = 0; j < len; j++) {
            cout << in[i][j] << "\t";
        }
    }
    cout << "\nOut\n";
    for (i = 0; i < llen; i++) {
        cout << "\n";
        for (j = 0; j < len; j++) {
            cout << out[i][j] << "\t";
        }
    }
    cout << "\n\n";
    for (i = 0; i < llen; i++) {
        cout << "\n";
        for (j = 0; j < llen; j++) {
            cout << cfg[i][j] << "\t";
        }
    }
}

int main() {
    read();
    mkblocks();
    gen_gen();
    gen_kill();
    inout();
}

