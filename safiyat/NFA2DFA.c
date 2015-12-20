#include<stdio.h>
#include<string.h>

int i, j, k, l, m, n = 0, o, p, ch, iv = 0, ns = 0, nss = 0;
char tab[20][10], st[20][5], temp[5], tr[20][5];

void search() {
    for (i = 1; i < n; i++) {
        j = 0;
        while (tab[i][j] != '\0') {
            k = 0;
            while (tab[i][j] != ':' && tab[i][j] != '\0') {
                temp[k] = tab[i][j];
                k++;
                j++;
            }
            temp[k] = '\0';
            strcpy(tr[nss], temp);
            nss++;
            temp[0] = '\0';
            if (tab[i][j] == ':') {
                j++;
            }
        }
        tab[i][0] = nss - 2 + 48;
        tab[i][1] = nss - 1 + 48;
        tab[i][2] = '\0';
    }
}

void newstate() {
    for (i = 0; i < nss; i++) {
        for (j = 0; j < ns; j++)
            if (strcmp(st[j], tr[i]) == 0 || tr[i][0] == 'x') {
                break;
            }
        if (j == ns) {
            strcpy(st[ns], tr[i]);
            ns++;
        }
    }
}

void main() {
    FILE *f;
    f = fopen("tab2.txt", "r");
    while (!feof(f)) {
        fscanf(f, "%s", tab[n]);
        n++;
    }
    n--;
    ns = n - 1;
    for (i = 0; i < ns; i++) {
        st[i][0] = i + 48;
    }
    printf("\n\nTHE NFA TABLE IS AS FOLLOWS\n\n");
    for (i = 0; tab[0][i] != '\0'; i++) {
        printf("\t%c", tab[0][i]);
        iv++;
    }
    for (i = 1; i < n; i++) {
        printf("\n%c\t", st[i - 1][0]);
        for (j = 0; tab[i][j] != '\0'; j++) {
            if (tab[i][j] == ':') {
                printf("\t");
            } else {
                printf("%c", tab[i][j]);
            }
        }
    }
    search();
    newstate();
    while (ns != (n - 1)) {
        for (k = 0; k < strlen(st[n - 1]); k++) {
            if (st[n - 1][k] == ',') {
                //st[n-1][k]=' ';
                k++;
            }
            for (i = 1; i < n; i++) {
                if (st[n - 1][k] == st[i - 1][0]) {
                    break;
                }
            }
            for (j = 0; j < iv; j++) {
                tab[n][j] = nss + 48;
                if (k == 0) {
                    strcpy(tr[nss], tr[tab[i][j] - 48]);
                } else {
                    if (tr[nss][0] == 'x') {
                        strcpy(tr[nss], tr[tab[i][j] - 48]);
                    } else {
                        for (o = 0; o < strlen(tr[tab[i][j] - 48]); o++) {
                            for (p = 0; p < strlen(tr[nss]); p++)
                                if ( tr[nss][p] == tr[tab[i][j] - 48][o] || tr[tab[i][j] - 48][o] == 'x') {
                                    break;
                                }
                            if (p == strlen(tr[nss])) {
                                tr[nss][strlen(tr[nss])] = tr[tab[i][j] - 48][o];
                            }
                        }
                    }
                }
                nss++;
            }
            nss = nss - 2;
        }
        nss = nss + 2;
        n++;
        newstate();
    }
    printf("\n\n\n\nTHE DFA TABLE IS AS FOLLOWS\n\n");
    for (i = 0; tab[0][i] != '\0'; i++) {
        printf("\t%c", tab[0][i]);
    }
    for (i = 1; i < n; i++) {
        printf("\n%s\t", st[i - 1]);
        for (j = 0; j < iv; j++) {
            printf("%s\t", tr[tab[i][j] - 48]);
        }
    }
    f = fopen("tab2res.txt", "w");
    fprintf(f, "\t%s", tab[0]);
    for (i = 1; i < n; i++) {
        fprintf(f, "\n%s\t", st[i - 1]);
        for (j = 0; j < iv; j++) {
            fprintf(f, "%s", tr[tab[i][j] - 48]);
            if (j == 0) {
                fprintf(f, ":");
            }
        }
    }
    printf("\n\n");
    getchar();
}
