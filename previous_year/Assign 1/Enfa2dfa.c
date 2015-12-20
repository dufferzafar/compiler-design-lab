#include <stdio.h>
#include <string.h>
#define STATES	99
#define SYMBOLS	20

int N_symbols;
int N_NFA_states;
char *NFAtab[STATES][SYMBOLS];
char *NFA_finals;

int N_DFA_states;
int DFAtab[STATES][SYMBOLS];
char DFA_finals[STATES + 1];

char StateName[STATES][STATES + 1];
char Eclosure[STATES][STATES + 1];

void print_nfa_table(char *tab[][SYMBOLS], int nstates, int nsymbols,
                     char *finals) {
    int i, j;
    puts("\nNFA: STATE TRANSITION TABLE");
    printf("     | ");
    for (i = 0; i < nsymbols; i++) {
        printf("  %-6c", '0' + i);
    }
    printf("  e\n");
    printf("-----+--");
    for (i = 0; i < nsymbols + 1; i++) {
        printf("-------");
    }
    printf("\n");
    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", '0' + i);
        for (j = 0; j < nsymbols + 1; j++) {
            printf("  %-6s", tab[i][j]);
        }
        printf("\n");
    }
    printf("Final states = %s\n", finals);
}

void print_dfa_table(int tab[][SYMBOLS], int nstates, int nsymbols,
                     char *finals) {
    int i, j;
    puts("\nDFA: STATE TRANSITION TABLE");
    printf("     | ");
    for (i = 0; i < nsymbols; i++) {
        printf("  %c  ", '0' + i);
    }
    printf("\n-----+--");
    for (i = 0; i < nsymbols; i++) {
        printf("-----");
    }
    printf("\n");
    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", 'A' + i);
        for (j = 0; j < nsymbols; j++) {
            printf("  %c  ", tab[i][j]);
        }
        printf("\n");
    }
    printf("Final states = %s\n", finals);
}

void load_NFA_table() {
    /*
    	epsilon-NFA table for ex.24 at p.82
    	Last input symbol is an epsilon.
    	Input symbols : 0(a), 1(b), 2(epsilon)

    	NFAtab[0][0] = "0";
    	NFAtab[0][1] = "";
    	NFAtab[0][2] = "13";
    	NFAtab[1][0] = "2";
    	NFAtab[1][1] = "";
    	NFAtab[1][2] = "";
    	NFAtab[2][0] = "";
    	NFAtab[2][1] = "2";
    	NFAtab[2][2] = "3";
    	NFAtab[3][0] = "3";
    	NFAtab[3][1] = "";
    	NFAtab[3][2] = "";

    	N_symbols = 2;
    	N_NFA_states = 4;
    	NFA_finals = "3";
    	N_DFA_states = 0;
    */
    /*
    	epsilon-NFA table for ex.25 at p.82-83
    	Last input symbol is an epsilon.
    	Input symbols : 0(a), 1(b), 2(epsilon)
    */
    NFAtab[0][0] = "1";
    NFAtab[0][1] = "";
    NFAtab[0][2] = "";
    NFAtab[0][3] = "2";
    NFAtab[1][0] = "";
    NFAtab[1][1] = "3";
    NFAtab[1][2] = "";
    NFAtab[1][3] = "";
    NFAtab[2][0] = "";
    NFAtab[2][1] = "";
    NFAtab[2][2] = "2";
    NFAtab[2][3] = "3";
    NFAtab[3][0] = "";
    NFAtab[3][1] = "";
    NFAtab[3][2] = "";
    NFAtab[3][3] = "";
    N_symbols = 3;
    N_NFA_states = 4;
    NFA_finals = "3";
    N_DFA_states = 0;
}

/*
	String 't' is merged into 's' in an alphabetical order.

	Return value: number of items that are added to 's'.
*/
int string_merge(char *s, char *t) {
    int n = 0;
    char temp[STATES + 1], *r = temp, *p = s;
    while (*p && *t) {
        if (*p == *t) {
            *r++ = *p++;
            t++;
        } else if (*p < *t) {
            *r++ = *p++;
        } else {
            *r++ = *t++;
            n++;	/* an item is added to 's' */
        }
    }
    *r = '\0';
    if (*t) {
        strcat(r, t);
        n += strlen(t);
    } else if (*p) {
        strcat(r, p);
    }
    strcpy(s, temp);
    return n;
}

/*
	Get next-state string for current-state string.
	(state 스트링이므로 각 state에 대해 nextstate를 merge)
*/
void get_next_state_NFA(char *nextstates, char *cur_states,
                        char *nfa[STATES][SYMBOLS], int symbol) {
    int i;
    char temp[STATES + 1];
    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++) {
        string_merge(temp, nfa[cur_states[i] - '0'][symbol]);
    }
    strcpy(nextstates, temp);
}

/*
	StateName 테이블 'stnt'에서 'state'를 찾아 index를 return.
	'state'가 테이블에 없으면 끝에 추가하고 index를 return.
*/
int state_index(char *state, char stnt[][STATES + 1], int *pn) {
    int i;
    if (!*state) {
        return -1;    /* no next state */
    }
    for (i = 0; i < *pn; i++)
        if (!strcmp(state, stnt[i])) {
            return i;
        }
    strcpy(stnt[i], state);	/* new state-name */
    return (*pn)++;
}


void get_ep_states(int state, char *epstates, char *nfa[][SYMBOLS], int n_sym) {
    int i, n = 0;	/* 'n': number of added states */
    /* directly epsilon-accessible states */
    strcpy(epstates, nfa[state][n_sym]);
    do {	/* get all indirectly epsilon-accessible states */
        for (i = 0; i < strlen(epstates); i++) {
            n = string_merge(epstates, nfa[epstates[i] - '0'][n_sym]);
        }
    } while (n);	/* 더 이상 추가되는 state가 없을 때까지 */
}


void init_Eclosure(char eclosure[][STATES + 1], char *nfa[][SYMBOLS], int n_nfa,
                   int n_sym) {
    int i;
    printf("\nEpsilon-accessible states:\n");
    for (i = 0; i < n_nfa; i++) {
        get_ep_states(i, eclosure[i], nfa, n_sym);
        printf("    state %d : [%s]\n", i, eclosure[i]);
    }
    printf("\n");
}

/*
	Epsilon closure of 'states' is 'epstates'.
*/
void e_closure(char *epstates, char *states, char eclosure[][STATES + 1]) {
    int i;
    strcpy(epstates, states);
    for (i = 0; i < strlen(states); i++) {
        string_merge(epstates, eclosure[states[i] - '0']);
    }
}


int nfa_to_dfa(char *nfa[][SYMBOLS], int n_nfa, int n_sym, int dfa[][SYMBOLS]) {
    int i = 0;	/* current index of DFA */
    int n = 1;	/* number of DFA states */
    char nextstate[STATES + 1];
    char temp[STATES + 1];	/* epsilon closure */
    int j;
    init_Eclosure(Eclosure, nfa, n_nfa, n_sym);
    e_closure(temp, "0", Eclosure);
    strcpy(StateName[0], temp);	/* initialize start state */
    printf("Epsilon-NFA to DFA conversion\n");
    for (i = 0; i < n; i++) {	/* for each DFA state */
        for (j = 0; j < n_sym; j++) {	/* for each input symbol */
            get_next_state_NFA(nextstate, StateName[i], nfa, j);
            e_closure(temp, nextstate, Eclosure);
            dfa[i][j] = state_index(temp, StateName, &n);
            printf("    state %d(%4s) : %d --> state %2d(%4s)\n", i, StateName[i], j,
                   dfa[i][j], temp);
            dfa[i][j] += 'A';
        }
    }
    return n;	/* number of DFA states */
}


void get_DFA_finals(
    char *dfinals,	/* DFA final states */
    char *nfinals,	/* NFA final states */
    char stnt[][STATES + 1],	/* state-name table */
    int n_dfa) {	/* number of DFA states */
    int i, j, k = 0, n = strlen(nfinals);
    for (i = 0; i < n_dfa; i++) {
        for (j = 0; j < n; j++) {
            if (strchr(stnt[i], nfinals[j])) {
                dfinals[k++] = i + 'A';
                break;
            }
        }
    }
    dfinals[k] = '\0';
}

void main() {
    load_NFA_table();
    print_nfa_table(NFAtab, N_NFA_states, N_symbols, NFA_finals);
    N_DFA_states = nfa_to_dfa(NFAtab, N_NFA_states, N_symbols, DFAtab);
    get_DFA_finals(DFA_finals, NFA_finals, StateName, N_DFA_states);
    print_dfa_table(DFAtab, N_DFA_states, N_symbols, DFA_finals);
}
