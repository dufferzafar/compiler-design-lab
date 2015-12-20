#include<stdio.h>
#include<ctype.h>
#include<string.h>
# define states 30
# define inputs 30

char mat[states][inputs][2];
char inp_str[50], out_str[50];
int no_st, no_inp = -1, len;

void read() {
    int i, j, k;
    char ch;
    FILE *fp;
    i = 0;
    j = 0;
    fp = fopen("meely_data.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (ch == ' ') {
            mat[i][j][2] = '\0';
        } else if (ch == ',') {
            continue;
        } else if (isalpha(ch)) {
            mat[i][j][1] = ch;
            j++;
        } else if (isdigit(ch)) {
            mat[i][j][0] = ch;
        } else if (ch == '#') {
            mat[i][j][0] = ch;
            mat[i][j][1] = '\0';
            j++;
        } else if (ch == '\n') {
            mat[i][j][2] = '\0';
            i++;
            if (no_inp < j) {
                no_inp = j;
            }
            j = 0;
        }
    }
    no_st = i + 1;
}
void print() {
    int i, j;
    puts("State Transistion Diagram\n");
    printf("States");
    for (i = 0; i < no_inp; i++) {
        printf("\t\t%c", i + 97);
    }
    puts("");
    for (i = 0; i < no_st; i++) {
        printf("Q%d", i);
        for (j = 0; j < no_inp; j++) {
            if (mat[i][j][0] == '#') {
                printf("\t\t-");
            } else {
                printf("\t\tQ%c,%c", mat[i][j][0], mat[i][j][1]);
            }
        }
        puts("");
    }
}


int show_output(int i, int j) {
    int z, s;
    char curr_input, curr_state;
    z = 0, s = 0;
    curr_input = inp_str[z++];
    j = curr_input - 'a';
    curr_state = mat[i][j][0];
    if (curr_state == '#') {
        return 0;
    }
    out_str[s++] = mat[i][j][1];
    i = curr_state - '0';
    while (z < len) {
        curr_input = inp_str[z++];
        j = curr_input - 'a';
        curr_state = mat[i][j][0];
        if (curr_state == '#') {
            return 0;
        }
        out_str[s++] = mat[i][j][1];
        i = curr_state - '0';
    }
    out_str[s] = '\0';
}

void validate() {
    if (show_output(0, 0)) {
        puts("OUTPUT:");
        puts(out_str);
    } else {
        puts("Machine went to undefined state!!...\ntry another input string");
    }
}


int input() {
    int i;
    puts("Enter a Input String.");
    scanf("%s", inp_str);
    len = strlen(inp_str);
    for (i = 0; i < len; i++) {
        if (!isalpha(inp_str[i])) {
            return 0;
        } else {
            inp_str[i] = tolower(inp_str[i]);
        }
    }
    return 1;
}



int main() {
    int i;
    read();
    print();
    while (1) {
        puts("\n************************************************\n1.Meely Machine\n2.Show Table\n3.Exit");
        scanf("%d", &i);
        switch (i) {
            case 1:
                if (input()) {
                    validate();
                } else {
                    puts("ERROR!!!\nString pattern incorrect.\n");
                }
                break;
            case 2:
                print();
                break;
            case 3:
                return 0;
        }
    }
}
