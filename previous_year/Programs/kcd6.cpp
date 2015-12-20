#include<iostream>
using namespace std;
#include<fstream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
int dfa[100][50],f[10],q,n,m,fc;
char states[10],mealy[100][50];
int read()
{
	ifstream fin;
	fin.open("kcd6.txt",ios::in);
	int i=0,j=0;
	char ch;
	while(fin.get(ch))
	{
		states[j++]=ch;
		cout<<ch;
		if(ch=='\n')
		{
			states[j]=NULL;
			m=j;
			j=0;
			while(fin.get(ch))
			{
				cout<<ch;
				if(ch=='\n')
				{
					i++;
					j=0;
					continue;
                }
                if(ch==' ')
                {
                	j++;
                	continue;
                }	
                dfa[i][j]=ch-'0';
             	if(ch=='-')
					continue;
				fin.get(ch);
				if(ch==',')
				{
					cout<<ch;
					n=i;
					q=dfa[i][j];
					j=0;
					while(fin.get(ch))
					{
						cout<<ch;
						if(ch!=',')
							f[j++]=ch-'0';
					}
					fc=j;
					return 0;
				}
				mealy[i][j]=ch;	
			}
		}
	}

}
void print()
{
	cout<<"\n\nNo of states ="<<n;
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
	cin>>str;
	int state=q,i=0;
	char ch;
	cout<<"Output status: ";
	while(str[i]!=NULL)
	{
		ch=str[i++];
		for(int j=0;j<=m;j++)
		{
			if( ch==states[j])
			{
				if(dfa[state][ch-'a'] != '-' && state<n)
				{
					cout<<mealy[state][ch-'a'];
					state=dfa[state][ch-'a'];
					break;
				}
				else
				{
					cout<<"\nOops.. String you entered is not accepted...\n";
					return 0;
				}
			}
		}
	}
	for(int j=0;j<fc;j++)
	{
		if(state==f[j])
		{
			cout<<"\nAccepted...\n";
			return 0;
		}
	}
	cout<<"\nOops.. String you entered is not accepted...\n";
}

int main()
{
	read();
	print();
	input();
    return 0;
}
