#include <stdio.h>
#include <string.h>
#include <ctype.h>

int NFA_States, DFA_States, NFA_symbols = -1, outputs, dfa_finals[40], s;

char NFA_Table[30][30][30];
char DFA_Table[30][30];
char Final[30];

void read() {
    FILE *fp;
    char ch;
    int i, j, k, z, flag;
    i = 0; j = 0; k = 0; z = 0;
    flag = 0;

    fp = fopen("input.txt", "r");

    while (!feof(fp)) {

        fscanf(fp, "%c", &ch);

        if (flag == 0) {
            if (ch == ' ') {
                NFA_Table[i][j][k] = '\0';
                k = 0;
                j++;
            } else if (ch == ',') {
                continue;
            } else if (ch == '\n') {
                NFA_Table[i][j][k] = '\0';
                k = 0;
                j++;
                if (NFA_symbols < j) {
                    NFA_symbols = j;
                }
                NFA_Table[i][j][0] = '\0';
                j = 0;
                i++;
            } else if (isdigit(ch)) {
                NFA_Table[i][j][k++] = ch;
            } else if (ch == '#') {
                NFA_Table[i][j][0] = '\0';
            } else if (ch == '@') {
                flag = 1;
            }
        } else {
            if (ch == ' ' || ch == ',') {
                continue;
            } else if (isdigit(ch)) {
                Final[z++] = ch;
            }
        }
    }
    NFA_States = i;

    outputs = z;

    DFA_States = 0;
}

void print() {
    int i, j, k;
    printf("Input NFA:\n\n");
    printf("States");
    for (i = 0; i < NFA_symbols; i++) {
        printf("\t\t%c", 97 + i);
    }
    puts("\n----------------------------------");
    for (i = 0; i < NFA_States; i++) {
        printf("Q%d", i);
        for (j = 0; j < NFA_symbols; j++) {
            printf("\t\t");
            k = 0;
            do {
                if (NFA_Table[i][j][0] == '\0') {
                    printf("-");
                } else {
                    if (k > 0) {
                        printf("Q%c,", NFA_Table[i][j][k - 1]);
                    }
                }
            } while (NFA_Table[i][j][k++] != '\0');
        }
        puts("");
    }
    puts("\nFinal States: ");
    for (i = 0; i < outputs; i++) {
        if (i < outputs - 1) {
            printf("%c,", Final[i]);
        } else {
            printf("%c", Final[i]);
        }
    }
}

void print_DFA() {
    int i, j;
    puts("\n\nConverted DFA:\n");
    printf("States");
    for (i = 0; i < NFA_symbols; i++) {
        printf("\t\t%c  ", 'a' + i);
    }
    puts("\n----------------------------------");
    for (i = 0; i < DFA_States; i++) {
        printf("Q%d", i);
        for (j = 0; j < NFA_symbols; j++) {
            if (DFA_Table[i][j] == -1) {
                printf("\t\t-");
            }
            printf("\t\tQ%d", DFA_Table[i][j]);
        }
        printf("\n");
    }

    puts("\nFinal States:");
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
        merge(temp, NFA_Table[cur_states[i] - '0'][symbol]);
    }
    strcpy(nextstates, temp);
}

void prepare_final_table(char *state, int st) {
    int i, j;
    for (j = 0; j < outputs; j++) {
        for (i = 0; i < strlen(state); i++) {
            if (state[i] == Final[j]) {
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
    int i = 0; int j; int n = 1;
    char next[40];
    strcpy(state[0], "0");
    for (i = 0; i < n; i++) {
        for (j = 0; j < NFA_symbols; j++) {
            next_state(next, state[i], j);
            DFA_Table[i][j] = state_at(next, state, &n);
        }
    }
    return n;
}


int main() {
    read(); print();
    DFA_States = nfa2dfa();
    print_DFA();
}
