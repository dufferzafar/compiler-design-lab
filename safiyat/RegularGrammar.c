#include<stdio.h>
#include<string.h>
char a[10][100];
int n;
int isTerminal(char x) {
    if (islower(x)) {
        return 1;
    } else {
        return 0;
    }
}
int isVariable(char x) {
    if (isupper(x)) {
        return 1;
    } else {
        return 0;
    }
}
int findVariable(char x) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i][0] == x) {
            return i;
        }
    }
}
int main() {
    FILE *p;
    int i = 0, j, k, flag = 1;
    char str[100], ch;
    p = fopen("file.txt", "r");
    while (!feof(p)) {
        fgets(a[i], 90, p);
        i++;
    }
    n = i;
    do {
        fflush(stdin);
        printf("\nEnter string\n");
        gets(str);
        j = 0, k = 2;
        for (i = 0; str[i] != '\0'; i++) {
            while ((str[i] != a[j][k]) || (a[j][k] == '$')) {
                while ((a[j][k] != '|') && (a[j][k] != '\0')) {
                    k++;
                }
                if (a[j][k] == '\0') {
                    flag = 0;
                    break;
                } else {
                    k++;
                }
            }
            if ((a[j][k] == '$') && (str[i] != '\0')) {
                flag = 0;
            }
            if (flag != 0) {
                k++;
                if (isVariable(a[j][k])) {
                    j = findVariable(a[j][k]);
                    k = 2;
                } else if (a[j][k] == '|' && str[i + 1] != '\0') {
                    flag = 0;
                    break;
                }
            } else {
                flag = 0;
                break;
            }
        }
        if (flag == 0) {
            printf("\nString not accepted\n");
        } else {
            printf("\nString accepted\n");
        }
        printf("\ndo you want to continue ?(y/n))");
        scanf("%c", &ch);
    } while (ch == 'y');
    getch();
}
