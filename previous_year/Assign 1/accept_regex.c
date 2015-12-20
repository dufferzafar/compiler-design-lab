#include<stdio.h>
#include<ctype.h>
#include<string.h>
char inp[40], mat[40][40], regex[40];
int no, row;

void read() {
    int i = 0, j;
    char ch;
    FILE *fp;
    fp = fopen("accept_regex_data.txt", "r");
    while (!feof(fp)) {
        fscanf(fp, "%c", &ch);
        if (ch != '\n') {
            regex[i++] = ch;
        }
    }
    no = i;
    regex[i] = '\0';
}

void prepare_matrix() {
    int i, x, y;
    x = 0;
    y = 0;
    for (i = 0; i < no; i++) {
        if (isalpha(regex[i])) {
            mat[x][y++] = regex[i];
        } else if (regex[i] == '+') {
            mat[x][y] = '\0';
            y = 0;
            x++;
        } else if (regex[i] == ')') {
            mat[x][y] = '\0';
            row = ++x;
        }
    }
    // printf("( %d )", row);
}


void p() {
    int i;
    for (i = 0; i < row; i++) {
        puts(mat[i]);
    }
}
void print() {
    puts(regex);
}

int compare(char *arr1, char *arr2, int st, int end) {
    int i, j;
    for (i = st, j = 0; i < end; i++, j++) {
        if (arr1[j] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

void validate(int flag) {
    if (flag) {
        puts("String Accepted!!!");
    } else {
        puts("String Not Accepted!!!");
    }
}


void match() {
    int i = 0, flag = 1, j;
    prepare_matrix();
    // p();
    input();
    if (regex[strlen(regex) - 1] == '*') {
        while (i < strlen(inp)) {
            for (j = 0; j < row; j++) {
                if (compare(mat[j], inp, i, strlen(mat[j]) + i)) {
                    printf("$$\n");
                    i = i + strlen(mat[j]);
                    flag = 1;
                    break;
                } else {
                    flag = 0;
                }
            }
            if (flag == 0) {
                break;
            }
        }
    } else {
        for (j = 0; j < row; j++) {
            if (compare(mat[j], inp, 0, strlen(inp))) {
                printf("$\n");
                flag = 1;
                break;
            } else {
                flag = 0;
            }
        }
    }
    validate(flag);
}

input() {
    int i;
    puts("Enter a String to be Matched\n");
    scanf("%s", inp);
}

int main() {
    int i;
    read();
    print();
    while (1) {
        puts("\n*******************************************\n\t\tMENU\n\n1.Match Regular Expression to a String\n2.Show Regex\n3.Exit\n");
        scanf("%d", &i);
        switch (i) {
            case 1:
                match();
                break;
            case 2:
                print();
                break;
            case 3:
                return 0;
        }
    }
}
