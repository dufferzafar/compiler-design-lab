#include<stdio.h>
#include<string.h>
#include<ctype.h>

char mat[30][30];
char fin[30];
char inp[30];
int no_st,no_out,max=0;

void read()
{
	FILE *fp;
	char ch;
	int i,j,z,flag;
	i=0;
	j=0;
	z=0;
	flag=0;
	fp=fopen("accept_dfa_data.txt","r");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(flag==0)
		{
			if(ch==' ')
			{
				continue;
			}
			else if(isdigit(ch) || ch=='#')
			{
				mat[i][j++]=ch;
			}
			else if(ch=='\n')
			{
				mat[i][j]='\0';
				i++;
				if(max<j)
					max=j;
				j=0;
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
    int i,j;
	printf("States");
	for(i=0;i<max;i++)
	{
		printf("\t\t%c",97+i);
	}
	puts("");
	for(i=0;i<no_st;i++)
	{
		printf("Q%d",i);
		for(j=0;mat[i][j]!='\0';j++)
		{
			if(mat[i][j]=='#')
			{
				printf("\t\t-");	
			}
			else
			{
				printf("\t\tQ%c",mat[i][j]);		
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

int dfa_accepted()
{
	int current_state,current_input,len,i;
	char var1,var2;
	i=0;
	len=strlen(inp);
	var1='0';
	while(i<len)
	{	
		
		var2=inp[i];
		current_input=var2-'a';
		current_state=var1-'0';
		var1=mat[current_state][current_input];
		if(var1=='#')
		{
			return 0;
		}
		i++;
	}
	current_state=var1-'0';
	
	for(i=0;i<no_out;i++)
	{
		if((fin[i]-'0')==current_state)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void validate()
{
	if(dfa_accepted())
	{
		printf("'%s' is a valid string for the dfa in accept_dfa_data.txt",inp);
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
		puts("\n*******************************************\n\t\tMENU\n\n1.DFA matching\n2.Show Table\n3.Exit\n");
		scanf("%d",&i);
		switch(i)
		{
			case 1:if(input())
			       {
			       	validate();
			       }
				   break;
			case 2:print();
			       break;
			case 3:return 0;
		}
	}
}
