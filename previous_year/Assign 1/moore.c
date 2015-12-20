#include<stdio.h>
#include<ctype.h>
#include<string.h>

int max, no_st;
char mat[40][40], out[40], inp[40], str[40];

void read() {
    FILE *fp;
    int i, j;
    int z;
    char ch;
    z = 0;
    i = 0;
    j = 0;
    fp = fopen("moore_data.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (ch == ' ') {
            continue;
        } else if (isdigit(ch) || ch == '#') {
            mat[i][j++] = ch;
        } else if (ch == '\n') {
            continue;
        } else if (isalpha(ch)) {
            out[z++] = ch;
            mat[i][j] = '\0';
            i++;
            if (max < j) {
                max = j;
            }
            j = 0;
        }
    }
    no_st = z;
}

void print() {
    int i, j;
    printf("States");
    for (i = 0; i < max; i++) {
        printf("\t\t%c", 97 + i);
    }
    printf("\t\t OUTPUT\n");
    for (i = 0; i < no_st; i++) {
        printf("Q%d", i);
        for (j = 0; mat[i][j] != '\0'; j++) {
            printf("\t\t%c", mat[i][j]);
        }
        printf("\t\t%c", out[i]);
        puts("");
    }
}

int process() {
    int i, j, z, len, current_state, current_inp;
    char var;
    i = 0;
    j = 0;
    z = 0;
    len = strlen(inp);
    puts("OUTPUT::");
    while (j < len) {
        str[z++] = out[i];
        current_state = i;
        current_inp = inp[j++] - 97;
        var = mat[current_state][current_inp];
        if (var == '#') {
            return 0;
        }
        i = var - 48;
    }
    str[z++] = out[i];
    str[z] = '\0';
    return 1;
}

void validate() {
    if (process()) {
        puts(str);
    } else {
        puts("Invalid String!!");
    }
}

int input() {
    int i;
again:
    puts("\n\nEnter a String to check its validation!!");
    scanf("%s", inp);
    for (i = 0; inp[i] != '\0'; i++) {
        if (isalpha(inp[i])) {
            inp[i] = tolower(inp[i]);
        } else {
            puts("Invalid string [Please use English alphabets only]");
            return 0;
        }
    }
    return 1;
}

int main() {
    int i;
    read();
    print();
    while (1) {
        puts("\n****************************************************\n1.Moore Machine\n2.Show Table\n3.Exit\n");
        scanf("%d", &i);
        switch (i) {
            case 1:
                if (input()) {
                    validate();
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
