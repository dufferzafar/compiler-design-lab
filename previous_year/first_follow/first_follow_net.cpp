#include <stdio.h>
#include <ctype.h>
#define prod 8  // define number of productions
#define nonterm 5  // defines number of non terminals

char input[prod][prod];

struct firTab
{
    int n;
    char firT[nonterm];
};

struct folTab
{
    int n;
    char folT[nonterm];
};

struct folTab follow[nonterm];
struct firTab first[nonterm];
int col;
void findFirst(char,char);
void findFollow(char,char);
void folTabOperation(char,char);
void firTabOperation(char,char);

int main()
{
    int i=0,j,c=0,cnt=0;
    char ip;
    char b[prod];

    FILE *fp;

    fp = fopen("file.txt","r");

    while(!feof(fp))
    {
        fscanf(fp,"%s",&input[i]);
        i++;
    }

    for(i=0;i<prod;i++)
    {
        c=0;
        for(j=0;j<i+1;j++)
        {
            if(input[i][0] == b[j])
            {
                c=1;
                break;
            }
        }
        if(c !=1)
        {
          b[cnt] = input[i][0];
          cnt++;
        }

    }

     printf("\n");

    for(i=0;i<cnt;i++)
    {
       col=1;
       first[i].firT[0] = b[i];
       first[i].n=0;
       findFirst(b[i],i);
    }

    for(i=0;i<cnt;i++)
    {
        col=1;
        follow[i].folT[0] = b[i];
        follow[i].n=0;
        findFollow(b[i],i);
    }

    printf("\n");

   for(i=0;i<cnt;i++)
   {
        for(j=0;j<=first[i].n;j++)
        {
                if(j==0)
                {
                    printf("First(%c) : {",first[i].firT[j]);
                }
                else
                {
                    printf(" %c",first[i].firT[j]);
                }
        }
        printf(" } ");
        printf("\n");

    }

     printf("\n");

   for(i=0;i<cnt;i++)
   {
        for(j=0;j<=follow[i].n;j++)
        {
                if(j==0)
                {
                    printf("Follow(%c) : {",follow[i].folT[j]);
                }
                else
                {
                    printf(" %c",follow[i].folT[j]);
                }
        }

        printf(" } ");
        printf("\n");
    }

return 0;

}


void findFirst(char ip,char pos)
{
    int i;
    for(i=0;i<prod;i++)
    {
        if(ip == input[i][0])
        {
            if(isupper(input[i][3]))
            {
                findFirst(input[i][3],pos);
            }

            else
            {
            first[pos].firT[col]=input[i][3];
            first[pos].n++;
            col++;
            }
        }
    }
}


void findFollow(char ip,char row)
{
    int i,j;

    if(row==0 && col==1)
    {
        follow[row].folT[col]= '$';
        col++;
        follow[row].n++;
    }

    for(i=0;i<prod;i++)
    {
        for(j=3;j<7;j++)
        {
            if(input[i][j] == ip)
            {
                if(input[i][j+1] == '\0')
                {
                    if(input[i][j] != input[i][0])
                    {
                        folTabOperation(input[i][0],row);
                    }
                }

                else if(isupper(input[i][j+1]))
                {
                    if(input[i][j+1] != input[i][0])
                    {
                        firTabOperation(input[i][j+1],row);

                    }
                }

                else
                {
                    follow[row].folT[col] = input[i][j+1];
                    col++;
                    follow[row].n++;


                }
            }
        }
    }
}


void folTabOperation(char ip,char row)
{
    int i,j;

    for(i=0;i<nonterm;i++)
    {
        if(ip == follow[i].folT[0])
        {
            for(j=1;j<=follow[i].n;j++)
            {
                follow[row].folT[col] = follow[i].folT[j];
                col++;
                follow[row].n++;
            }
        }
    }
}


void firTabOperation(char ip,char row)
{
    int i,j;
    for(i=0;i<nonterm;i++)
    {
        if(ip == first[i].firT[0])
        {
            for(j=1;j<=first[i].n;j++)
            {
                if(first[i].firT[j] != '0')   // denotes epsilon
                {
                    follow[row].folT[col] = first[i].firT[j];
                    follow[row].n++;
                    col++;
                }
                else
                {
                    folTabOperation(ip,row);
                }
            }
        }
    }
}


/*
INPUT -

Enter productions in format A->B+T

E->TA
A->+TA
A->0
T->FB
B->*FB
B->0   // 0 denotes epsilon
F->(E)
F->#

*/
