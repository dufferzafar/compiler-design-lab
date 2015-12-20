/* C program to check given grammar is Regular Grammar or not. */

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int i,j,k,l,m,n=0,o,p,nv,z=0,t,x=0;
char str[10],temp[10],temp2[10],temp3[10];

struct prod
{
    char lhs[10],rhs[10][10];
    int n;
}pro[10];

void findter()
{
    for(k=0;k<n;k++)
    {
        if(temp[i]==pro[k].lhs[0])
        {
            for(t=0;t<pro[k].n;t++)
            {
                cout << temp << " - ";
                for(x=0;x<10;x++)
                    temp2[x]='\0';
                for(l=i+1;l<strlen(temp);l++)
                    temp2[l-i-1]=temp[l];
                temp[i]='\0';
                for(l=0;l<strlen(pro[k].rhs[t]);l++)
                    temp[i+l]=pro[k].rhs[t][l];
                strcat(temp,temp2);

                cout << temp << " - ";
                if(str[i]==temp[i])
                    return;
            }
        }
    }

}

int main()
{
    FILE *f;

    for(i=0;i<10;i++)
        pro[i].n=0;

    f=fopen("input.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%s",pro[n].lhs);
        if(n>0)
        {
            if( strcmp(pro[n].lhs,pro[n-1].lhs) == 0 )
            {
                pro[n].lhs[0]='\0';
                fscanf(f,"%s",pro[n-1].rhs[pro[n-1].n]);
                pro[n-1].n++;
                continue;
            }
        }
        fscanf(f,"%s",pro[n].rhs[pro[n].n]);
        pro[n].n++;
        n++;
    }
    n--;

    printf("\n\nTHE GRAMMAR IS AS FOLLOWS\n\n");
    for(i=0;i<n;i++)
        for(j=0;j<pro[i].n;j++)
            printf("%s -> %s\n",pro[i].lhs,pro[i].rhs[j]);

    o=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<pro[i].n;j++)
            if( pro[i].rhs[j][0]>=65 && pro[i].rhs[j][0]<=90 )
            {
                o=1;
                break;
            }
        if(o==1)
            break;
    }
    if(i==n)
        printf("\n\nTHE GRAMMAR is a REGULAR GRAMMAR !!!");
    else
    {
        printf("\n\nTHE GRAMMAR is NOT a REGULAR GRAMMAR !!!");
        // exit(1);
    }

    while(1)
    {
        for(x=0;x<10;x++)
            str[x]='\0';
        printf("\n\nENTER ANY STRING ( 0 for EXIT ) : ");
        scanf("%s",str);
        // if(str[0]=='0')
            // exit(1);

        for(j=0;j<pro[0].n;j++)
        {
            for(x=0;x<10;x++)
                temp[x]='\0';
            strcpy(temp,pro[0].rhs[j]);
            cout << temp << " - ";

            m=0;
            for(i=0;i<strlen(str);i++)
            {
                if(str[i]==temp[i])
                    m++;
                else if(str[i]!=temp[i] && temp[i]>=65 && temp[i]<=90)
                {
                    findter();
                    if(str[i]==temp[i])
                        m++;
                }
            }
            for(x=0;x<10;x++)
                temp3[x]='\0';
            strcpy(temp3,temp);
            temp3[strlen(temp)-1]='\0';
            //printf("%s",temp);
            if(m==strlen(str) && strcmp(temp3,str)==0 && strlen(temp3)!=1)
            {
                printf("\n\nTHE STRING can be PARSED !!!");
                break;
            }
            if(m==strlen(str) && strlen(str)==strlen(temp))
            {
                printf("\n\nTHE STRING can be PARSED !!!");
                break;
            }
        }

        if(j==pro[0].n)
            printf("\n\nTHE STRING can NOT be PARSED !!!");
    }

    printf("\n\n");

}
