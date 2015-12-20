#include<stdio.h>
int main()
{
    int i, j, k, n, row, col, flag = 0;
    char ch, dfa[10][10], input[20], cur = '0', output[20];
    FILE *fp;
    fp = fopen("input.txt", "r+");
    ch = fgetc(fp);

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            dfa[i][j] = '$';

    i = j = 0;

    while (ch != EOF)
    {
        //printf("%c ",ch);
        if (ch == '\n')
        {
            i++;
            j = 0;
        }
        else if (ch == ' ')
            j++;
        else
            dfa[i][j] = ch;

        ch = fgetc(fp);
    }

    row = ++i;
    col = ++j;

    for (i = 0; i < row; i++, printf("\n"))
        for (j = 0; j < col; j++)
            if (dfa[i][j] != '$')
                printf("%c ", dfa[i][j]);

    printf("\nEnter string\n");
    scanf("%s", input);
    i = j = 0;
    output[j++] = dfa[cur - '0'][col - 1];

    while (input[i] != NULL)
    {
        flag = 0;

        if (dfa[cur - '0'][input[i] - 'a'] != '-' && dfa[cur - '0'][input[i] - 'a'] != '$' && input[i] - 'a' != col - 1)
        {
            cur = dfa[cur - '0'][input[i] - 'a'];
            output[j++] = dfa[cur - '0'][col - 1];
            i++;
            flag = 1;
        }

        if (flag == 0)
            break;
    }

    output[j] = NULL;

    if (flag == 0)
        printf("String not accepted\n");
    else
        printf("String accepted\n Output is %s\n", output);
}
