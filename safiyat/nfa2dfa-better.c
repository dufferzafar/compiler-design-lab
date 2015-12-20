#include <stdio.h>
#include <string.h>

#define STATES  256
#define SYMBOLS 20

int N_symbols;
int NFA_states;
char *NFAtab[STATES][SYMBOLS];

int DFA_states; /* number of DFA states */
int DFAtab[STATES][SYMBOLS];

/*Print state-transition table.*/
void put_dfa_table(
    int tab[][SYMBOLS], /* DFA table */
    int nstates,    /* number of states */
    int nsymbols)   /* number of input symbols */
{
    int i, j;

    puts("STATE TRANSITION TABLE");

    /* input symbols: '0', '1', ... */
    printf("     | ");
    for (i = 0; i < nsymbols; i++) printf("  %c  ", '0'+i);

    printf("\n-----+--");
    for (i = 0; i < nsymbols; i++) printf("-----");
    printf("\n");

    for (i = 0; i < nstates; i++) {
        printf("  %c  | ", 'A'+i);  /* state */
        for (j = 0; j < nsymbols; j++)
            printf("  %c  ", 'A'+tab[i][j]);
        printf("\n");
    }
}

/*Initialize NFA table.*/
void init_NFA_table()
{
/*
    NFA table for ex.21 at p.76

    NFAtab[0][0] = "01";
    NFAtab[0][1] = "0";
    NFAtab[1][0] = "";
    NFAtab[1][1] = "01";

    NFA_states = 2;
    DFA_states = 0;
    N_symbols = 2;
*/
/*
    NFA table for ex.17 at p.72
*/
    NFAtab[0][0] = "12";
    NFAtab[0][1] = "13";
    NFAtab[1][0] = "12";
    NFAtab[1][1] = "13";
    NFAtab[2][0] = "4";
    NFAtab[2][1] = "";
    NFAtab[3][0] = "";
    NFAtab[3][1] = "4";
    NFAtab[4][0] = "4";
    NFAtab[4][1] = "4";

    NFA_states = 5;
    DFA_states = 0;
    N_symbols = 2;
}

/*String 't' is merged into 's' in an alphabetical order.*/
void string_merge(char *s, char *t)
{
    char temp[STATES], *r=temp, *p=s;

    while (*p && *t) {
        if (*p == *t) {
            *r++ = *p++; t++;
        } else if (*p < *t) {
            *r++ = *p++;
        } else
            *r++ = *t++;
    }
    *r = '\0';

    if (*p) strcat(r, p);
    else if (*t) strcat(r, t);

    strcpy(s, temp);
}

/*Get next-state string for current-state string.*/
void get_next_state(char *nextstates, char *cur_states,
    char *nfa[STATES][SYMBOLS], int n_nfa, int symbol)
{
    int i;
    char temp[STATES];

    temp[0] = '\0';
    for (i = 0; i < strlen(cur_states); i++)
        string_merge(temp, nfa[cur_states[i]-'0'][symbol]);
    strcpy(nextstates, temp);
}


int state_index(char *state, char statename[][STATES], int *pn)
{
    int i;

    if (!*state) return -1; /* no next state */

    for (i = 0; i < *pn; i++)
        if (!strcmp(state, statename[i])) return i;

    strcpy(statename[i], state);    /* new state-name */
    return (*pn)++;
}

/*
    Convert NFA table to DFA table.
    Return value: number of DFA states.
*/
int nfa_to_dfa(char *nfa[STATES][SYMBOLS], int n_nfa,
    int n_sym, int dfa[][SYMBOLS])
{
    char statename[STATES][STATES];
    int i = 0;  /* current index of DFA */
    int n = 1;  /* number of DFA states */

    char nextstate[STATES];
    int j;

    strcpy(statename[0], "0");  /* start state */

    for (i = 0; i < n; i++) {   /* for each DFA state */
        for (j = 0; j < n_sym; j++) {   /* for each input symbol */
            get_next_state(nextstate, statename[i], nfa, n_nfa, j);
            dfa[i][j] = state_index(nextstate, statename, &n);
        }
    }

    return n;   /* number of DFA states */
}

void main()
{
    init_NFA_table();
    DFA_states = nfa_to_dfa(NFAtab, NFA_states, N_symbols, DFAtab);
    put_dfa_table(DFAtab, DFA_states, N_symbols);
}
