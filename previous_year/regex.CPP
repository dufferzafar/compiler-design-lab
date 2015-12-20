#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<stdio.h>
char token[50][10],regex[100],count=0;
void read()
{
	int i=0,j,n=0;
	ifstream fin;
	fin.open("kcd2.txt",ios::in);
	char ch;
	while(fin.get(ch))
	{
		regex[n++]=ch;
		if(ch>='a'&&ch<='z')
			token[count][i++]=ch;
		else
		{
			token[count][i]=NULL;
			i=0;
			count++;
		}
	}
	regex[n]=NULL;
	cout<<"Regular exp read is : "<<regex;
	for(i=0;i<count;i++)
		puts(token[i]);
}
void check()
{
	char str[20],temp[10];
	int i,j,k,l,flag=0;
	cout<<"\n\nEnter a string: ";
	gets(str);
	for(i=0,j=0;i<strlen(str);i++)
	{
		for(l=0,k=j;k<=i;k++)
			temp[l++]=str[k];
		temp[l]=NULL;
		for(k=0;k<count;k++)
		{
			if(strcmp(token[k],temp)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			flag=0;
			j=i+1;
		}
	}
	if(j==strlen(str))
		cout<<"\nAccepted...";
	else
		cout<<"\nNot Accepted...";
}
void main()
{
	clrscr();
	read();
	check();
	getch();
}