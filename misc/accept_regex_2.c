#include <stdio.h>
#include <string.h>
char dfa[10][10], input[20];
int store[10], n;
void read() {
    int i, j, k;
    char ch;
    FILE *fp;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
            dfa[i][j] = store[i] = 0;
        }
    fp = fopen("reg.txt", "r+");
    ch = fgetc(fp);
    i = j = k = 0;
    while (ch != EOF) {
        if (ch == '+') {
            dfa[i][j] = '\0';
            i++;
            j = 0;
        } else if (ch == ')' || ch == '(') {
        } else if (ch == '*') {
            store[k++] = i++;
            j = 0;
        } else {
            dfa[i][j++] = ch;
        }
        ch = fgetc(fp);
    }
    dfa[i][j - 1] = 0;
    store[k] = i;
    n = ++i;
    for (i = 0; i < 10; i++) {
        printf("%s\t%d\n", dfa[i], store[i]);
    }
    printf("Enter a string\n");
    scanf("%s", input);
}
void check() {
    int i, flag = 0, fwd[10], start = 0, j, k, l = 0, flag2 = 0;
    char temp[20];
    for (i = 0; i < 10; i++) {
        fwd[i] = -1;
    }
    i = k = 0;
    while (input[i] != '\0') {
        if (flag == 0) {
            temp[k++] = input[i++];
            temp[k] = '\0';
        }
        if (flag2 == 0)
            for (j = store[l + 1]; j < 10; j++)
                if (temp[0] == dfa[j][0]) {
                    start = store[l] + 1;
                    l++;
                    break;
                }
        for (j = start; j <= store[l]; j++) {
            flag2 = 1;
            if (strcmp(temp, dfa[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            k = flag2 = 0;
            if (input[i] == '\0') {
                break;
            }
            flag = 0;
        }
    }
    if (flag == 1) {
        printf("String Accepted\n");
    } else {
        printf("String not Accepted\n");
    }
}
void main() {
    read();
    check();
}
