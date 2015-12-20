#include <stdio.h>
#include <conio.h>

void main() {
    int i = 0, j, k, row = 0, col = 0, flag;
    char re[20], string[50], store[10][10], test[10];
    clrscr();
    printf("Enter Regular Expression\n");
    scanf("%s", re);
    printf("Enter string\n");
    scanf("%s", string);
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
            store[i][j] = NULL;
        }
    for (i = 0; re[i] != NULL; i++) {
        if (re[i] == '(' || re[i] == ')' || re[i] == '*') {
            continue;
        } else if (re[i] == '+') {
            store[row][col] = NULL;
            row++;
            col = 0;
        } else {
            store[row][col] = re[i];
            printf("%c ", store[row][col]);
            col++;
        }
    }
    store[row][col] = NULL;
    printf("\n");
    for (i = 0; string[i] != NULL; i++) {
        k = flag = 0;
        test[k] = string[i];
        test[k + 1] = NULL;
        printf("%s ", test);
        for (j = 0; j <= row; j++) {
            if (strcmp(store[j], test) == 0) {
                flag = 1;
                break;
            } else if (store[j][0] == string[i]) {
                test[++k] = string[++i];
                test[k + 1] = NULL;
                j = -1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
    if (flag == 0) {
        printf("String not accepted\n");
    } else {
        printf("String accepted\n");
    }
    getch();
}
