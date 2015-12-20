#include <stdio.h>
#include <string.h>

char reg[20], input[20];
int store[10], n;

void read() {
    int i, j, k;
    char ch;

    FILE *fp;
    fp = fopen("reg.txt", "r+");

    fscanf(fp, "%s", reg);

    for (i = strlen(reg); i > 0; i--) {
        reg[i] = reg[i - 1];
    }

    reg[0] = '(';
    reg[strlen(reg)] = ')';
    reg[strlen(reg) + 1] = '\0';

    printf("%s\nEnter a string\n", reg);
    scanf("%s", input);
}

void check() {
    int i = 0, j = 0, cur = 0, prev = 0, f = 0;
    char temp[20];

    while (input[i] != '\0') {
        f = 0;

		// This means the cur pointer reads the
		// current regex character.
        if (cur > strlen(reg)) {
            break;
        }

        if (reg[cur] == '(') {
            cur++;
        } else if (reg[cur] == input[i]) {
            f = 1;
            cur++;
            if (reg[cur] == '+') {
                cur = prev;
            }
            i++;
        } else if (reg[cur] == '+') {
            cur++;
        }
        //else if(reg[cur]=='*')
        //	prev=cur=cur+1;
        else if (reg[cur] == ')') {
            cur++;
            if (reg[cur] == '*') {
                cur = prev;
            } else {
                prev = cur;
            }
        } else {
            cur++;
        }
    }

    if (f == 1) {
        printf("String accepted\n");
    } else {
        printf("String not accepted\n");
    }
}
void main() {
    read();
    check();
}
