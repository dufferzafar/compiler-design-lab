#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char tac[20][30];
int nt=0,lead[20],nl=0,cfg[20][20],gen[20][20],kill[20][20],in[20][20],out[20][20],oldout[20],dom[20][20];
void read()
{
	int j=0;
	char ch;
	FILE *fp=fopen("tac.txt","r");
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		if(ch=='\n')
		{
			tac[nt++][j]='\0';
			j=0;
		}
		else
			tac[nt][j++]=ch;
		ch=fgetc(fp);
	}
	tac[nt++][j]='\0';
	fclose(fp);
}
void leaders()
{
	int i,j,k=1,leadt[20],t;
	char *temp,str[5];
	leadt[0]=1;
	for(i=0;i<nt;i++)
	{
		temp=strstr(tac[i],"goto");
		if(temp!='\0')
		{
			temp=temp+5;
			//printf("%c",*temp);
			j=0;
			while(*temp!=';')
				str[j++]=*(temp++);
			str[j]='\0';
			leadt[k++]=atoi(str);
			leadt[k++]=i+2;
		}
	}
	for(i=0;i<k;i++)
		for(j=i+1;j<k;j++)
			if(leadt[i]>leadt[j])
			{
				t=leadt[i];
				leadt[i]=leadt[j];
				leadt[j]=t;
			}
	for(i=0;i<k;i++)
		if(leadt[i]!=leadt[i+1])
			lead[nl++]=leadt[i];
	for(i=nl;i<20;i++)
		lead[i]=lead[nl-1]+10;
}
int block(int line)
{
	int i,block=0;
	for(i=0;i<nl;i++)
	{
		if(line>=lead[i] && line<=lead[i+1]-1)
			return block+1;
		else
			block++;
	}
}
void makecfg()
{
	int i,j,k;
	char *t1,*t2,str[5];
	for(i=0;i<nl;i++)
		for(j=0;j<nl;j++)
			cfg[i][j]=0;
	for(i=0;i<nt;i++)
	{
		t1=strstr(tac[i],"if");
		t2=strstr(tac[i],"goto");
		if(t1=='\0' && t2!='\0')
		{
			t2=t2+5;
			j=0;
			while(*t2!=';')
				str[j++]=*(t2++);
			str[j]='\0';
			cfg[block(i+1)-1][block(atoi(str))-1]=1;
		}
		else
		{
			if(block(i+1)!=block(i+2) && i+1<nt)
				cfg[block(i+1)-1][block(i+2)-1]=1;
			if(t1!='\0')
			{
				t2=t2+5;
				j=0;
				while(*t2!=';')
					str[j++]=*(t2++);
				str[j]='\0';
				cfg[block(i+1)-1][block(atoi(str))-1]=1;
			}
		}
	}
}
void makegen()
{
	int i,j;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			gen[i][j]=0;
	for(i=0;i<nt;i++)
		if(tac[i][4]=='=')
			gen[block(i+1)-1][i]=1;
}
void makekill()
{
	int i,j,k;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			kill[i][j]=0;
	for(i=0;i<nt;i++)
		if(tac[i][4]=='=')
			for(j=0;j<nt;j++)
				if(j!=i && tac[j][3]==tac[i][3])
					kill[block(i+1)-1][j]=1;
}
void inout()
{
	int i,j,k,change=1;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
		{
			in[i][j]=0;
			out[i][j]=gen[i][j];
		}
	while(change)
	{
		change=0;
		for(i=0;i<nl;i++)
		{
			for(j=0;j<nl;j++)
				if(cfg[j][i]==1)
					for(k=0;k<nt;k++)
						in[i][k]=in[i][k]|out[j][k];
			for(j=0;j<nt;j++)
				oldout[j]=out[i][j];
			for(j=0;j<nt;j++)
			{
				if(in[i][j]==1 && kill[i][j]==1)
					out[i][j]=0;
				else
					out[i][j]=in[i][j];
			}
			for(j=0;j<nt;j++)
				out[i][j]=out[i][j]|gen[i][j];
			for(j=0;j<nt;j++)
				if(oldout[j]!=out[i][j])
					change=1;
		}
	}
}
void dominator()
{
	int i,j,k,self[20];
	dom[0][0]=1;
	for(i=1;i<nl;i++)
		dom[0][i]=0;
	for(i=1;i<nl;i++)
		for(j=0;j<nl;j++)
			dom[i][j]=1;
	for(i=0;i<nl;i++)
	{
		for(j=0;j<nl;j++)
			if(cfg[j][i]==1)
				for(k=0;k<nl;k++)
					dom[i][k]=dom[i][k]&dom[j][k];
		for(j=0;j<nl;j++)
			self[j]=0;
		self[i]=1;
		for(j=0;j<nl;j++)
			dom[i][j]=dom[i][j]|self[j];
	}
}
void print()
{
	int i,j;
	for(i=0;i<nt;i++)
		printf("%s",tac[i]);
	printf("\n");
	for(i=0;i<nl;i++)
		printf("%d ",lead[i]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nl;j++)
			printf("%d ",cfg[i][j]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nt;j++)
			printf("%d ",gen[i][j]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nt;j++)
			printf("%d ",kill[i][j]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nt;j++)
			printf("%d ",in[i][j]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nt;j++)
			printf("%d ",out[i][j]);
	printf("\n");
	for(i=0;i<nl;i++,printf("\n"))
		for(j=0;j<nl;j++)
			printf("%d ",dom[i][j]);
			
}
void main()
{
	read();
	leaders();
	makecfg();
	makegen();
	makekill();
	inout();
	dominator();
	print();
}
