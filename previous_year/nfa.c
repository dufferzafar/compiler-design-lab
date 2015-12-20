#include<stdio.h>
#include<string.h>
struct nfa {
    int state[10][10];
} q[10];
int curf;
int check(char input[], int cur, int i) {
    int k = 0, cur2;
    while (q[cur].state[input[i] - 'a'][k] != -1) {
        if (q[cur].state[input[i] - 'a'][k] != '-') {
            cur2 = q[cur].state[input[i] - 'a'][k];
            if (input[i + 1] == '\0') {
                curf = cur2;
                return 1;
            }
            if (check(input, cur2, i + 1) == 0) {
                k++;
            } else {
                return 1;
            }
        } else {
            k++;
        }
    }
    return 0;
}
void main() {
    int i, j, k, n, n1, cur, f = 0;
    char c, input[20];
    FILE *fp;
    fp = fopen("nfainput.txt", "r+");
    c = fgetc(fp);
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++) {
                q[i].state[j][k] = -1;
            }
    i = j = k = 0;
    while (c != EOF) {
        if (c == ',') {
            k++;
        } else if (c == ' ') {
            j++;
            k = 0;
        } else if (c == '\n') {
            if (j == 0 && f == 0) {
                f = 1;
                n1 = i;
            }
            i++;
            j = k = 0;
        } else if (c == '-') {
            q[i].state[j][k] = c;
        } else {
            q[i].state[j][k] = c - '0';
        }
        c = fgetc(fp);
    }
    n = ++i;
    for (i = 0; i < 10; i++, printf("\n"))
        for (j = 0; j < 10; j++)
            for (k = 0; k < 10; k++)
                if (q[i].state[j][k] != -1) {
                    printf("%d ", q[i].state[j][k]);
                }
    printf("\nEnter string\n");
    scanf("%s", input);
    cur = q[n1].state[0][0];
    i = f = 0;
    //printf(" %d ",cur);
    if (check(input, cur, i) == 1) {
        for (j = n1 + 1; j < n - 1; j++)
            if (q[j].state[0][0] == curf) {
                printf("String Accepted\n");
                f = 1;
                break;
            }
        if (f == 0) {
            printf("String not Accepted\n");
        }
    } else {
        printf("String not Accepted\n");
    }
}
