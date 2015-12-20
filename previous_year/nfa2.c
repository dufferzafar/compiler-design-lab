#include<stdio.h>
#include<string.h>
int nfa[10][10][10];
char input[20],n;
void read()
{
	char ch;
	int i,j,k,temp=0;
	FILE *fp=fopen("nfainput.txt","r+");
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			for(k=0;k<10;k++)
				nfa[i][j][k]=-1;
	ch=fgetc(fp);
	i=k=j=0;
	while(ch!=EOF)
	{
		if(ch==' ')
		{
			j++;
			k=0;
		}
		else if(ch=='\n')
		{
			i++;
			if(j==0 && temp==0)
			{
				n=i;
				temp=1;
			}
			j=k=0;
		}
		else if(ch==',')
			k++;
		else
			nfa[i][j][k]=ch-'0';
		ch=fgetc(fp);
	}
	printf("%d\n",n);
	for(i=0;i<10;i++,printf("\n"))
		for(j=0;j<10;j++)
			for(k=0;k<10;k++)
				if(nfa[i][j][k]!=-1)
					printf("%d ",nfa[i][j][k]);
}
int nfacheck(int cur,int i)
{
	int j=0,k;
	if(i>=strlen(input))
	{	
		for(k=n;k<10;k++)
			if(cur==nfa[k][0][0])
				return 1;
		return 0;
	}
	if(nfa[cur][input[i]-'a'][j]>-1 && i<strlen(input))
	{
		while(nfa[cur][input[i]-'a'][j]>-1 && i<strlen(input))
			if(nfacheck(nfa[cur][input[i]-'a'][j],i+1)==0)
				j++;
			else
				return 1;
		return 0;
	}
	else
		return 0;
}
void main()
{
	int cur=0;
	read();
	printf("Enter a string\n");
	scanf("%s",input);
	if(nfacheck(cur,0)==1)
		printf("String Accepted\n");
	else
		printf("String not Accepted\n");
}
