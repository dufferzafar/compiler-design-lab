#include<stdio.h>
char comb[10][15];
int size;
void input() {
    FILE * fp;
    char ch;
    int i = 0, j = 0;
    fp = fopen("re.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (isalpha(ch)) {
            //printf("%c\t",ch);
            comb[i][j++] = ch;
        }
        if (ch == '+' || ch == ')') {
            comb[i][j] = '\0';
            i++;
            j = 0;
        }
    }
    size = i;
}
void main() {
    char in[20];
    int len, i = 0, j = 0, k = 0, flag;
    clrscr();
    input();
    printf("\nEnter the input string");
    scanf("%s", in);
    len = strlen(in);
    printf("\nstring length is %d", len);
    while (k < len) {
        flag = 0;
        for (i = 0; i < size; i++)
            if (in[k] == comb[i][0]) {
                flag = 1;
                for (j = 0; j < strlen(comb[i]); j++)
                    if (comb[i][j] != in[j + k] ) {
                        printf("\nString not accepted");
                        break;
                    }
                k += strlen(comb[i]);
                break;
            }
        if (flag == 0) {
            printf("\nString not accepted");
            break;
        }
    }
    if (flag == 1) {
        printf("\nString accepted");
    }
    getch();
}
