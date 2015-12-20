#include<stdio.h>
#include<string.h>
struct nfa {
    char trans[6][6];
    int num[6];
    char state[10];
} obj[20], dfa[20];
int row, col, n;
char str[20];
void readfromfile() {
    FILE *fp;
    char ch;
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0;
    fp = fopen("input3.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (ch == ' ') {
            obj[i].num[j]++;
            j++;
            k = 0;
        } else if (ch == '\n') {
            obj[i].num[j] = ++k;
            col = j + 1;
            obj[i].state[l++] = i + '0';
            i++;
            l = 0;
            j = 0;
            k = 0;
        } else if (ch == ',') {
            k++;
            obj[i].num[j] = k;
        } else {
            obj[i].trans[j][k] = ch;
        }
    }
    obj[i].num[j]++;
    row = ++i;
    n = l;
    printf("\nrow=%d,,col=%d", row, col);
    printf("\n");
    for (i = 0; i < row; i++) {
        printf("%c\t", obj[i].state[0]);
        for (j = 0; j < col; j++) {
            for (k = 0; k < obj[i].num[j]; k++) {
                printf("%c,", obj[i].trans[j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }
}

void recursion(int i, int curr) {
    int k;
    printf("curr=%d", curr);
    if (curr == 2 && i == strlen(str)) {
        printf("\nAccepted");
    }
    for (k = 0; k < obj[curr].num[str[i] - 97]; k++) {
        if (obj[curr].trans[str[i] - 97][k] != '-') {
            curr = obj[curr].trans[str[i] - 97][k] - '0';
        } else {
            return;
        }
        recursion(i + 1, curr);
    }
}


int main() {
    readfromfile();
    printf("\nEnter the String:");
    scanf("%s", str);
    recursion(0, 0);
    return 0;
}

