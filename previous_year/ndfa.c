#include <stdio.h>
#include <string.h>

int n, n1, cur, state[10][10][10], dfa[10][10], ind[10][10];

char input[20];

void read() {
    int i, j, k, f = 0;
    char c;
    FILE *fp;
    fp = fopen("nfadfainput.txt", "r+");
    c = fgetc(fp);

    // Clear the state matrix
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++) {
                state[i][j][k] = -1;
            }

    i = j = k = 0;

    while (c != EOF) {
        if (c == ',') {
            k++;
        } else if (c == ' ') {
            j++;
            k = 0;
        } else if (c == '\n') {
            if (j == 0 && f == 0) {
                f = 1;
                n1 = i;
            }
            i++;
            j = k = 0;
        } else if (c == '-') {
            state[i][j][k] = c;
        } else {
            state[i][j][k] = c - '0';
        }
        c = fgetc(fp);
    }
    n = ++i;
}

void ntodfa() {
    int i, j, k, l = 0, m, f = 0, f1, temp[10][10], p;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
            dfa[i][j] = ind[i][j] = -1;
        }
    for (i = 0; i < n1; i++) {
        f1 = 0;
        for (k = 0; k < l; k++)
            if (ind[k][0] == i && ind[k][1] == -1) {
                f1 = 1;
            }
        if (f1 == 0) {
            ind[l++][0] = i;
        }
        for (j = 0; j < 10; j++)
            if (state[i][j][1] != -1 && state[i][j][0] != '-') {
                f1 = 0;
                for (k = 0; k < l; k++)
                    if (ind[k][0] == state[i][j][0])
                        for (m = 0; m < 10; m++)
                            if (ind[k][m] != state[i][j][m]) {
                                f1 = 1;
                                break;
                            }
                if (f1 == 1) {
                    for (k = 0; k < 10; k++) {
                        ind[l][k] = state[i][j][k];
                    }
                    l++;
                }
            } else if (state[i][j][0] != '-' && state[i][j][0] != -1) {
                f1 = 0;
                for (k = 0; k < l; k++)
                    if (ind[k][0] == state[i][j][0] && ind[k][1] == -1) {
                        f1 = 1;
                    }
                if (f1 == 0) {
                    ind[l++][0] = state[i][j][0];
                }
            }
    }
    /* DFA creation */
    for (i = 0; i < l; i++) {
        if (ind[i][1] == -1) {
            for (j = 0; j < 10; j++) {
                f1 = f = 0;
                if (state[ind[i][0]][j][0] != '-' && state[ind[i][0]][j][0] != -1) {
                    for (m = 0; m < l; m++) {
                        for (k = 0; k < 10; k++)
                            if (ind[m][k] == state[ind[i][0]][j][k]) {
                                f1 = 1;
                            } else {
                                f1 = 0;
                                break;
                            }
                        if (f1 == 1) {
                            break;
                        }
                    }
                    dfa[i][j] = m;
                } else if (state[ind[i][0]][j][0] == '-') {
                    dfa[i][j] = '-';
                }
            }
        } else {
            for (j = 0; j < 10; j++)
                for (k = 0; k < 10; k++) {
                    temp[j][k] = -1;
                }
            for (j = 0; j < 10; j++) {
                if (ind[i][j] != -1)
                    for (p = 0; p < 10; p++) {
                        k = 0;
                        while (temp[p][k] != -1) {
                            k++;
                        }
                        for (m = 0; m < 10; m++)
                            if (state[ind[i][j]][p][m] != -1 && state[ind[i][j]][p][m] != '-') {
                                temp[p][k++] = state[ind[i][j]][p][m];
                            }
                    }
            }
            for (j = 0; j < 10; j++)
                for (k = 0; k < 10; k++)
                    for (m = k + 1; m < 10; m++) {
                        if (temp[j][m] == -1) {
                            break;
                        }
                        if (temp[j][k] == temp[j][m]) {
                            temp[j][m] = -1;
                        }
                        if (temp[j][k] >= temp[j][m] && temp[j][m] != -1) {
                            int sav;
                            sav = temp[j][m];
                            temp[j][m] = temp[j][k];
                            temp[j][k] = sav;
                        }
                    }
            for (j = 0; j < 10; j++) {
                if (temp[j][0] != -1) {
                    for (m = 0; m < l; m++) {
                        f1 = 0;
                        if (temp[j][0] == ind[m][0] && temp[j][0] != -1)
                            for (p = k = 0; p < 10 && temp[j][k] != -1; p++, k++)
                                if (temp[j][k] == ind[m][p]) {
                                    f1 = 1;
                                } else {
                                    f1 = 0;
                                    break;
                                }
                        if (f1 == 1) {
                            break;
                        }
                    }
                    if (f1 == 1) {
                        dfa[i][j] = m;
                    } else {
                        for (k = 0; k < 10; k++) {
                            ind[l][k] = temp[j][k];
                        }
                        dfa[i][j] = l++;
                    }
                }
            }
        }
    }
}
void check() {
    int i = 0, f = 0, j, k;
    while (input[i] != '\0') {
        if (dfa[cur][input[i] - 'a'] == -1 || dfa[cur][input[i] - 'a'] == '-') {
            f = 1;
            printf("String Not Accepted\n");
            break;
        } else {
            cur = dfa[cur][input[i] - 'a'];
        }
        i++;
    }
    if (f == 0) {
        for (j = n1 + 1; j < n; j++)
            for (k = 0; k < 10 && ind[cur][k] != -1; k++)
                if (ind[cur][k] == state[j][0][0]) {
                    f = 1;
                }
        if (f == 1) {
            printf("String accepted\n");
        } else {
            printf("String Not Accepted\n");
        }
    }
}
void main() {
    read();
    ntodfa();
    printf("\nEnter string\n");
    scanf("%s", input);
    cur = state[n1][0][0];
    check();
}
