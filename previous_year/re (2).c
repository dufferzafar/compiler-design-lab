#include<stdio.h>
#include<string.h>
void main() {
    int i, j, k, row = 0, col = 0;
    char re[20], input[20], dfa[10][10];
    FILE *fp;
    fp = fopen("reinp.txt", "r+");
    fscanf(fp, "%s", re);
    printf("%s\nEnter string\n", re);
    scanf("%s", input);
    for (i = 0; re[i] != '\0'; i++) {
        if (re[i] == '(' || re[i] == ')' || re[i] == '*') {
            continue;
        } else if (re[i] == '+') {
            dfa[row++][col] = '\0';
            col = 0;
        } else {
            dfa[row][col++] = re[i];
        }
    }
    dfa[row++][col] = '\0';
    /*  for(i=0;i<row;i++,printf("\n"))
    	printf("%s",dfa[i]);*/
    i = 0;
    char temp[20];
    int flag = 0;
    k = 0;
    while (i < strlen(input)) {
        if (flag == 0) {
            temp[k++] = input[i++];
            temp[k] = '\0';
        }
        for (j = 0; j < row; j++) {
            if (strcmp(temp, dfa[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            k = 0;
            if (input[i] == '\0') {
                flag = 1;
                break;
            } else {
                flag = 0;
            }
        }
    }
    if (flag == 1) {
        printf("String Accepted\n");
    } else {
        printf("String Not Accepted\n");
    }
}
