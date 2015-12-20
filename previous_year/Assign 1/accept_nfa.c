#include<stdio.h>
#include<string.h>
#include<ctype.h>

char mat[30][30][30];
char fin[30];
char inp[30];
int no_st,no_out,maxj=0,len;

void read()
{
	FILE *fp;
	char ch;
	int i,j,k,z,flag;
	i=0;
	j=0;
	k=0;
	z=0;
	flag=0;
	fp=fopen("accept_nfa_data.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(flag==0)
		{
			if(ch==' ')
			{
				mat[i][j][k]='\0';
				k=0;
				j++;
			}
			else if(ch==',')
			{
				continue;
			}
			else if(ch=='\n')
			{
				mat[i][j][k]='\0';
				k=0;
				j++;
				if(maxj<j)
				{
					maxj=j;
				}
				mat[i][j][0]='\0';
				j=0;
				i++;
			}
			else if(isdigit(ch) || ch=='#')
			{
				mat[i][j][k++]=ch;
			}
			else if(ch=='@')
			{
			    flag=1;
			}
		}
		else
		{
			if(ch==' ' || ch==',')
			{
				continue;
			}
			else if(isdigit(ch))
			{
			    fin[z++]=ch;
			}
		}
	}
	no_st=i;
	no_out=z;
}

void print()
{
    int i,j,k;
	printf("States");
	for(i=0;i<maxj;i++)
	{
		printf("\t\t%c",97+i);
	}
	puts("");
	for(i=0;i<no_st;i++)
	{
		printf("Q%d",i);
		for(j=0;mat[i][j][0]!='\0';j++)
		{
			printf("\t\t");
			for(k=0;mat[i][j][k]!='\0';k++)
			{
				
				if(mat[i][j][k]=='#')
				{
					printf("-");	
				}
				else
				{
					printf("Q%c,",mat[i][j][k]);		
				}
			}
		}
		puts("");
	}
	puts("\nOUTPUT STATES:");
	for(i=0;i<no_out;i++)
	{
		if(i<no_out-1)
		{
			printf("%c,",fin[i]);	
		}
		else
		{
			printf("%c",fin[i]);
		}
		
	}	
}


int input()
{
	int i;
	again:
	puts("\n\nEnter a String to check its validation!!");
	scanf("%s",inp);
	for(i=0;inp[i]!='\0';i++)
	{
		if(isalpha(inp[i]))
		{
			inp[i]=tolower(inp[i]);
		}
		else
		{
			puts("Invalid string [Please use English alphabets only]");
			return 0;
		}
	}
	return 1;
}


int nfa_accepted(state,j,iter)
{
	char c,ch;
	int z=0,x;
	char next_States[30];
	if(j==len)
	{
		 for(x=0;x<no_out;x++)
		 {
		 	 if(fin[x]-'0'==state)
		 	 {
		 	 	return 1;
		 	 }
		 }
	}
	c=inp[j++];
	for(x=0;mat[state][c-'a'][x]!='\0';x++)
	{
		ch=mat[state][c-'a'][x];
		if(ch=='#')
		{
			return 0;
		}
		next_States[z++]=ch;
	}
	for(x=0;x<z;x++)
	{
		if(nfa_accepted(next_States[x]-'0',j,iter++))
		{
			return 1;
		}
	}
	return 0;
}

void validate()
{
	if(nfa_accepted(0,0,1))
	{
		printf("'%s' is a valid string for the nfa in accept_nfa_data.txt",inp);
	}
	else
	{
		puts("String is Invalid!!\nPlease try another string");
	}
}

int main()
{
	int i;
	read();
	print();
	while(1)
	{
		puts("\n*******************************************\n\t\tMENU\n\n1.NFA matching\n2.Show Table\n3.Exit\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:if(input())
			       {
			       	len=strlen(inp);
			       	validate();
			       }
				   break;
			case 2:print();
			       break;
			case 3:return 0;
		}
	}
}
