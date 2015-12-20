/*		Q1.	Write a program to implement DFA		*/
#include<stdio.h>
#include<stdlib.h>
void main() {
    int i, j, flag, n, n1, dfa[10][10], cur;
    char c, input[20];
    FILE *fp;
    fp = fopen("dfainput.txt", "r+");
    c = fgetc(fp);
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
            dfa[i][j] = -1;
        }
    i = j = flag = 0;
    while (c != EOF) {
        if (c == ',') {
            if (j == 0 && flag == 0) {
                flag = 1;
                n = i;
            }
            j = 0;
            i++;
        } else if (c == '\n') {
            i++;
            j = 0;
        } else if (c == ' ') {
            j++;
        } else {
            dfa[i][j] = c - '0';
        }
        c = fgetc(fp);
    }
    n1 = ++i;
    for (i = 0; i < 10; i++, printf("\n"))
        for (j = 0; j < 10; j++)
            if (dfa[i][j] != -1) {
                printf("%d ", dfa[i][j]);
            }
    printf("Enter the string\n");
    scanf("%s", input);
    i = cur = 0;
    while (input[i] != '\0') {
        flag = 0;
        if (dfa[cur][input[i] - 'a'] >= 0) {
            cur = dfa[cur][input[i] - 'a'];
            flag = 1;
        }
        if (flag == 0) {
            break;
        }
        i++;
    }
    if (flag == 1) {
        flag = 0;
        for (i = n + 1; i < n1; i++)
            if (cur == dfa[i][0]) {
                flag = 1;
            }
    } else {
        printf("String not accepted\n");
        exit(0);
    }
    if (flag == 1) {
        printf("String accepted\n");
    } else {
        printf("String not accepted\n");
    }
}
