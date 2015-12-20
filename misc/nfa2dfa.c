#include <stdio.h>
#include <string.h>
#include <ctype.h>

char NFAtab[30][30][30];
char DFAtab[30][30], fin[30];
int NFA_states, DFA_states, NFA_symbols = -1, outputs, dfa_finals[40], s;

void read() {
    FILE *fp;
    char ch;
    int i, j, k, z, flag;
    i = 0;
    j = 0;
    k = 0;
    z = 0;
    flag = 0;
    fp = fopen("nfa2dfa_data.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (flag == 0) {
            if (ch == ' ') {
                NFAtab[i][j][k] = '\0';
                k = 0;
                j++;
            } else if (ch == ',') {
                continue;
            } else if (ch == '\n') {
                NFAtab[i][j][k] = '\0';
                k = 0;
                j++;
                if (NFA_symbols < j) {
                    NFA_symbols = j;
                }
                NFAtab[i][j][0] = '\0';
                j = 0;
                i++;
            } else if (isdigit(ch)) {
                NFAtab[i][j][k++] = ch;
            } else if (ch == '#') {
                NFAtab[i][j][0] = '\0';
            } else if (ch == '@') {
                flag = 1;
            }
        } else {
            if (ch == ' ' || ch == ',') {
                continue;
            } else if (isdigit(ch)) {
                fin[z++] = ch;
            }
        }
    }
    NFA_states = i;
    outputs = z;
    DFA_states = 0;
}

void print() {
    int i, j, k, faltu;

    printf("States");
    for (i = 0; i < NFA_symbols; i++) {
        printf("\t\t%c", 97 + i);
    }

    puts("");
    for (i = 0; i < NFA_states; i++) {
        printf("Q%d", i);
        for (j = 0; j < NFA_symbols; j++) {
            printf("\t\t");
            k = 0;
            do {
                if (NFAtab[i][j][0] == '\0') {
                    printf("-");
                } else {
                    if (k > 0) {
                        printf("Q%c,", NFAtab[i][j][k - 1]);
                    }
                }
            } while (NFAtab[i][j][k++] != '\0');
        }
        puts("");
    }
    puts("\nOUTPUT STATES:");
    for (i = 0; i < outputs; i++) {
        if (i < outputs - 1) {
            printf("%c,", fin[i]);
        } else {
            printf("%c", fin[i]);
        }
    }
}

void print_DFA() {
    int i, j;
    puts("STATE TRANSITION TABLE");
    printf("States");
    for (i = 0; i < NFA_symbols; i++) {
        printf("\t\t%c  ", 'a' + i);
    }
    printf("\n");
    for (i = 0; i < DFA_states; i++) {
        printf("Q%d", i);
        for (j = 0; j < NFA_symbols; j++) {
            if (DFAtab[i][j] == -1) {
                printf("\t\t-");
            }
            printf("\t\tQ%d", DFAtab[i][j]);
        }
        printf("\n");
    }
    puts("\nOUTPUT STATES:");
    for (i = 0; i < s; i++) {
        if (i < s - 1) {
            printf("%d,", dfa_finals[i]);
        } else {
            printf("%d", dfa_finals[i]);
        }
    }
}


void merge(char *arr1, char *arr2) {
    char temp[30], *result = temp, *p = arr1;
    while (*p && *arr2) {
        if (*p == *arr2) {
            *result++ = *p++;
            arr2++;
        } else if (*p < *arr2) {
            *result++ = *p++;
        } else {
            *result++ = *arr2++;
        }
    }
    *result = '\0';
    if (*p) {
        strcat(result, p);
    } else if (*arr2) {
        strcat(result, arr2);
    }
    strcpy(arr1, temp);
}


void next_state(char *nextstates, char *cur_states, int symbol) {
    int i;
    char temp[40];
    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++) {
        // printf("current states length=%d\n", strlen(cur_states));
        // puts(NFAtab[cur_states[i] - '0'][symbol]);
        merge(temp, NFAtab[cur_states[i] - '0'][symbol]);
    }
    // puts(temp);
    strcpy(nextstates, temp);
}

void prepare_final_table(char *state, int st) {
    int i, j;
    for (j = 0; j < outputs; j++) {
        for (i = 0; i < strlen(state); i++) {
            if (state[i] == fin[j]) {
                dfa_finals[s++] = st;
                return;
            }
        }
    }
}

int state_at(char *state, char statename[][40], int *pn) {
    int i;
    if (!*state) {
        return -1;
    }
    for (i = 0; i < *pn; i++)
        if (!strcmp(state, statename[i])) {
            return i;
        }
    strcpy(statename[i], state);
    prepare_final_table(state, *pn);
    return (*pn)++;
}


int nfa2dfa() {
    char state[40][40];
    int i = 0;
    int n = 1;
    char next[40];
    int j;
    strcpy(state[0], "0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < NFA_symbols; j++) {
            next_state(next, state[i], j);
            DFAtab[i][j] = state_at(next, state, &n);
        }
    }
    return n;
}


int main() {
    int i;
    read();
    print();
    while (1) {
        puts("\n*******************************************\n\t\tMENU\n\n1.NFA to DFA\n2.Show Table\n3.Exit\n");
        scanf("%d", &i);
        switch (i) {
            case 1:
                s = 0;
                DFA_states = nfa2dfa();
                print_DFA();
                break;
            case 2:
                print();
                break;
            case 3:
                return 0;
        }
    }
}
