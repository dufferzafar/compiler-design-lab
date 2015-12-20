#include <stdio.h>
#include <fstream.h>
#include <conio.h>
#include <iomanip.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int leader[20];
int j=0;

int cfg[20][20];

int cfgr[20][20];

int contains(char *c)
{
	char *p=strstr(c,"goto");
	if(p!='\0')
	{
		return 1;
	}
	return 0;
}

int target(char *c)
{
       char *p=strstr(c,"goto");
       while(!isdigit(*++p));
       return atoi(p);
}

int findindex(int a)
{
	for(int i=0;i<j;i++)
	{
		if(leader[i]==a)
			return i;
	}
	return -1;
}

void makecfg(char *c,int bno)
{
	cout<<"\nChecking line :"<<c<<endl;
	char *p=strstr(c,"if");
	if(p)
	{
		char *p=strstr(c,"goto");
		while(!isdigit(*++p));
		int target=atoi(p);
		int tar=findindex(target);
		cout<<bno<<"->"<<tar<<endl;
		cfg[bno][tar]=1;
		cout<<bno<<"->"<<bno+1<<endl;
		cfg[bno][bno+1]=1;
	}
	else
	{
		char *p=strstr(c,"goto");
		if(p)
		{
			while(!isdigit(*++p));
			int target=atoi(p);
			int tar=findindex(target);
			cout<<bno<<"->"<<tar<<endl;
			cfg[bno][tar]=1;
		}
		else
		{
			cout<<bno<<"->"<<bno+1<<endl;
			cfg[bno][bno+1]=1;
		}
	}
}


int not(int a)
{
	for(int i=0;i<j;i++)
	{
		if(leader[i]==a)
			return 0;
	}
	return 1;
}


void main()
{
	clrscr();
	int i=1;
	ifstream f;
	f.open("tac.txt");
	leader[j]=1;
	j++;
	char c[30][100];
	int fno=1;
	while(!f.eof())
	{
		f.getline(c[fno],100,'\n');
		cout<<setw(2)<<i<<". ";
		puts(c[fno]);
		i++;
		if( contains(c[fno]) )
		{
			if(not(i))
			{
				leader[j]=i;
				j++;
			}
			if(not(target(c[fno])))
			{
				leader[j]=target(c[fno]);
				j++;
			}
		}
		fno++;
	}
	int lines=i-1;// ungetc
	for(i=0;i<j-1;i++)
	{
		for(int k=0;k<j-i-1;k++)
		{
			if(leader[k]>leader[k+1])
			{
				int temp=leader[k];
				leader[k]=leader[k+1];
				leader[k+1]=temp;
			}
		}
	}
	cout<<"Leaders:"<<endl;
	for(i=0;i<j;i++)
	{
		cout<<leader[i]<<endl;
	}
	cout<<"Blocks:"<<endl;
	for(i=0;i<j-1;i++)
	{
		cout<<i<<":"<<leader[i]<<"-"<<leader[i+1]-1<<endl;
	}
	cout<<i<<":"<<leader[i]<<"-"<<lines;

	for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
			cfg[i][k]=0;
	}


	for(i=1;i<j;i++)
	{
		makecfg(c[leader[i]-1],i-1);
	}
	makecfg(c[lines],j-1);

	cout<<endl<<endl;
	for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
			cout<<cfg[i][k]<<" ";
		cout<<endl;
	}

	for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
		{
			cfgr[i][k]=cfg[k][i];
		}
	}
	/*cout<<endl;
	for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
			cout<<cfgr[i][k]<<" ";
		cout<<endl;
	} */
	getch();
	int D[20][20];
	D[0][0]=1;
	for(int k=1;k<j;k++)
	{
		D[0][k]=0;
	}
	for(i=1;i<j;i++)
	{
		for(k=0;k<j;k++)
		{
			D[i][k]=1;
		}
	}
	cout<<endl;
	/*for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
			cout<<D[i][k]<<" ";
		cout<<endl;
	} */
	//getch();
	int changes=10;
	while(changes)
	{
		//changes=0;
		for(i=1;i<j;i++)
		{
			for(int k=0;k<j;k++)
			{
				if(cfgr[i][k]==1)
				{
					for(int p=0;p<j;p++)
					{
						D[i][p] = D[k][p]&D[i][p];
					}
				}
			}

			int self[20];
			for(k=0;k<j;k++)
			{
				self[k]=0;
			}
			self[i]=1;
			for(int p=0;p<j;p++)
			{
				D[i][p] = self[p]|D[i][p];
			}

		}
		changes--;
	}

	cout<<endl;
	for(i=0;i<j;i++)
	{
		for(int k=0;k<j;k++)
			cout<<D[i][k]<<" ";
		cout<<endl;
	}
	getch();
}