#include<iostream>
#include<fstream>
using namespace std;
#include<stdio.h>
#include<ctype.h>
#include<string.h>
int dfa[100][50],f[10],q,n,m,fc;
char states[10];
void read()
{
	ifstream fin;
	fin.open("kcd1.txt",ios::in);
	int i=0,j=0;
	char ch;
	while(fin.get(ch))
	{
		states[j++]=ch;
		if(ch=='\n')
		{
			states[j]=NULL;
			m=j;j=0;
			while(fin.get(ch))
			{
				dfa[i][j++]=ch-'0';
				if(ch=='\n')
				{
					i++;
					j=0;
				}
				if(ch==',')
				{
					q=dfa[i][j];
					j=0;
					cout<<ch;
					while(fin.get(ch))
					{
						fc=0;
						if(ch!=',')
						{
							f[j++]=ch-'0';
							fc++;
						}
						cout<<ch;
					}
					n=i;
				}
				cout<<ch;
			}
		}
	}
}
void print()
{
	cout<<"\nNo of states ="<<n;
	cout<<"\nNo of final states ="<<fc;
	cout<<"\nInitial state :"<<q;
	cout<<"\nFinal States :";
	for(int i=0;i<fc;i++)
		cout<<f[i]<<" ";
	cout<<"\nInput Symbols :";puts(states);
}

int input()
{
	char str[100];
	cout<<"\nEnter the input string : ";
	gets(str);
	int state=q,i=0;
	char ch;
	cout<<"State status: "<<state;
	while(str[i]!=NULL)
	{
		ch=str[i++];
		for(int j=0;j<=m;j++)
		{
			if( ch==states[j])
			{
				if(dfa[state][j] != '-'-'0')
				{
					state=dfa[state][j];
					cout<<"->"<<state;
					break;
				}
				else
				{
					cout<<"\nNot accepted...";
					return 0;
				}
			}
		}
	}
	for(int j=0;j<fc;j++)
	{
		if(state==f[j])
		{
			cout<<"\nAccepted...";
			return 0;
		}
	}
	cout<<"\nNot Accepted...";
}

int main()
{
	read();
	print();
	input();
	return 0;
}
