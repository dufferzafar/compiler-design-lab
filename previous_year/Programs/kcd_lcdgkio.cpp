#include<iostream>
#include<fstream>
using namespace std;
#include<string.h>
char tac[20][100];
int n=0,leader[20],nl=0,block[20][2],nb=0;
int cfg[20][20],dominator[20][20],gen[20][20],kill[20][20],in[20][20],out[20][20];
void read()
{
	fstream fin;
	fin.open("tac.txt",ios::in);
	while(!fin.eof())
		fin.getline(tac[n++],100,'\n');
}
void leaders()
{
	leader[nl++]=0;
	for(int i=0;i<n;i++)
	{
		char *temp=strstr(tac[i],"goto");
		if(temp!='\0')
		{
			leader[nl++]=i+1;
			int l=strlen(tac[i]);
			for(int j=0;j<l-4;j++)
			{
				if(tac[i][j]=='g' && tac [i][j+1]=='o' && tac [i][j+2]=='t' && tac [i][j+3]=='o' )
				{
					j=j+5;
					leader[nl]=0;
					while(isdigit(tac[i][j]))
						leader[nl]=leader[nl]*10 + (tac[i][j++]-'0');
					leader[nl]--;
					nl++;
				}
			}
		}
	}
}
void sort_leaders()
{
	for(int i=0;i<nl-1;i++)
		for(int j=i+1;j<nl;j++)
			if(leader[j]<leader[i])
			{
				leader[i]=leader[i]+leader[j];
				leader[j]=leader[i]-leader[j];
				leader[i]=leader[i]-leader[j];
			}
			else if(leader[i]==leader[j])
			{
				for(int k=j;k<nl-1;k++)
					leader[k]=leader[k+1];
				nl--;
			}
}
void blocks()
{
	for(int i=0;i<nl-1;i++)
	{
		block[nb][0]=leader[i];
		block[nb++][1]=leader[i+1]-1;
	}
	block[nb][0]=leader[nl-1];
	block[nb++][1]=n-1;
}
void make_cfg()
{
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<nb;j++)
		{
			if(block[j][0]==block[i][1]+1)
				cfg[i][j]=1;
			else
				cfg[i][j]=0;
		}
		for(int k=block[i][0];k<=block[i][1];k++)
		{
			int find=0;
			char *temp=strstr(tac[k],"goto");
			if(temp!='\0')
			{
				int l=strlen(tac[k]);
				for(int j=0;j<l-4;j++)
				{
					if(tac[k][j]=='g' && tac [k][j+1]=='o' && tac [k][j+2]=='t' && tac [k][j+3]=='o' )
					{
						j=j+5;
						while(isdigit(tac[k][j]))
							find=find*10 + (tac[k][j++]-'0');
						find--;
					}
				}
				for(int j=0;j<nb;j++)
				{
					if(block[j][0]==find)
						cfg[i][j]=1;
				}
			}
		}
	}
}
void dominators()
{
	dominator[0][0]=1;
	for(int i=1;i<nb;i++)
		dominator[0][i]=0;
	for(int i=1;i<nb;i++)
		for(int j=0;j<nb;j++)
			dominator[i][j]=1;
	for(int i=1;i<nb;i++)
	{
		for(int j=0;j<nb;j++)
			if(cfg[j][i]==1)
				for(int k=0;k<nb;k++)
					dominator[i][k] = dominator[i][k] & dominator[j][k];
		int self[20];
		for(int j=0;j<nb;j++)
			self[j]=0;
		self[i]=1;
		for(int j=0;j<nb;j++)
			dominator[i][j] = dominator[i][j] | self[j];
	}
}

void genkill()
{
	for(int i=0;i<nb;i++)
		for(int j=0;j<nb;j++)
		{
			gen[i][j]=kill[i][j]=0;
		}
	for(int i=0;i<nb;i++)
	{
		for(int j=block[i][0];j<=block[i][1];j++)
		{
			for(int k=0;tac[j][k]!='\n';k++)
			{
				if(tac[j][k]=='=')
					gen[i][j]=1;
			}
		}
	}
	for(int i=0;i<nb;i++)
	{
		for(int j=block[i][0];j<=block[i][1];j++)
		{
			if(gen[i][j]==1)
			{
				for(int k=0;k<n;k++)
				{
					if(k<block[i][0] || k>block[i][1])
					{
						if(tac[k][3]==tac[j][3] && tac[k][4]==tac[j][4])
							kill[i][k]=1;
					}
				}
			}
		}
	}
}
void inout()
{
	for(int i=0;i<nb;i++)
		for(int j=0;j<n;j++)
		{
			in[i][j]=0;
			out[i][j]=gen[i][j];
		}
	int change=1;
	int temp[20][20];
	while(change)
	{
		change=0;
		for(int i=0;i<nb;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(i!=0)
					in[i][j]=out[i-1][j];
				temp[i][j]=in[i][j];
				temp[i][j]=temp[i][j] - kill[i][j];
				if(temp[i][j]<0)
					temp[i][j]=0;
				temp[i][j]=temp[i][j] + gen[i][j];
				if(temp[i][j]>1)
					temp[i][j]=1;
				if(temp[i][j]!=out[i][j])
					change=1;
				out[i][j]=temp[i][j];
			}
		}
	}
}
void print()
{
	cout<<"TAC is:\n";
	for(int i=0;i<n;i++)
		puts(tac[i]);

	cout<<"\nLeaders are :  ";
	for(int i=0;i<nl;i++)
		cout<<leader[i]+1<<"  ";

	for(int i=0;i<nb;i++)
		cout<<"\n\nBlock "<<i+1<<" : "<<block[i][0]+1<<"->"<<block[i][1]+1;

	cout<<"\n\nCFG:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<nb;j++)
			cout<<" "<<cfg[i][j];
		cout<<"\n";
	}

	cout<<"Dominators:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<nb;j++)
			cout<<" "<<dominator[i][j];
		cout<<endl;
	}

	cout<<"\n\nGEN:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<n;j++)
			cout<<" "<<gen[i][j];
		cout<<"\n";
	}

	cout<<"\n\nKILL:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<n;j++)
			cout<<" "<<kill[i][j];
		cout<<"\n";
	}

	cout<<"\n\nIN:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<n;j++)
			cout<<" "<<in[i][j];
		cout<<"\n";
	}

	cout<<"\n\nOUT:\n";
	for(int i=0;i<nb;i++)
	{
		for(int j=0;j<n;j++)
			cout<<" "<<out[i][j];
		cout<<"\n";
	}

}
int main()
{
	read();
	leaders();
	// sort_leaders();
	// blocks();
	// make_cfg();
	// dominators();
	// genkill();
	// inout();
	print();
	return 0;
}
