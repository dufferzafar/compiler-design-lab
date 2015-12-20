#include<stdio.h>
//#include<conio.h>
int lead[30], n = 0;
void check(int a) {
    int i, flag = 0;
    // printf("a%d ",a);
    for (i = 0; i < n; i++)
        if (lead[i] == a) {
            flag = 1;
            break;
        }
    if (flag == 0) {
        lead[n++] = a;
    }
}
void main() {
    int i, j;
    char c, str[10];
    FILE *fp = fopen("tacinp.txt", "r+");
    //clrscr();
    for (i = 0; i < 30; i++) {
        lead[i] = -1;
    }
    c = fgetc(fp);
    while (c != EOF) {
        if (n == 0) {
            i = 0;
            str[i++] = c;
            while (c != ':') {
                str[i++] = c;
                c = fgetc(fp);
            }
            str[i] = NULL;
            lead[n++] = atoi(str);
            printf(" l%d ", lead[n - 1]);
        } else if (c == 'g') {
            c = fgetc(fp);
            if (c == 'o') {
                c = fgetc(fp);
                if (c == 't') {
                    c = fgetc(fp);
                    if (c == 'o') {
                        i = 0;
                        c = fgetc(fp);
                        printf("%c ", c);
                        if (c == ' ') {
                            c = fgetc(fp);
                        }
                        printf("%c ", c);
                        str[i++] = c;
                        c = fgetc(fp);
                        printf("%c ", c);
                        while (c != '\n' && c != EOF) {
                            if (c == EOF) {
                                break;
                            }
                            str[i++] = c;
                            c = fgetc(fp);
                            printf("%c ", c);
                        }
                        str[i] = NULL;
                        check(atoi(str));
                        i = 0;
                        c = fgetc(fp);
                        if (c == EOF) {
                            break;
                        }
                        str[i++] = c;
                        c = fgetc(fp);
                        while (c != ':') {
                            str[i++] = c;
                            c = fgetc(fp);
                        }
                        str[i] = NULL;
                        check(atoi(str));
                    }
                }
            }
        }
        c = fgetc(fp);
        printf("%c ", c);
    }
    i = 0;
    printf("\n");
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
            if (lead[i] > lead[j]) {
                lead[i] ^= lead[j] ^= lead[i] ^= lead[j];
            }
    for (i = 0; i < n - 1; i++) {
        printf("%d %d-%d\n", i, lead[i], lead[i + 1] - 1);
    }
    printf("%d %d-onwards", i, lead[n - 1]);
    //       getch();
}
