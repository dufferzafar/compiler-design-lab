#include<stdio.h>
int cfg[10][10],row=0,col=0,sav[10][10],k=0,l=0;
int dom(int node,int r1)
{
	int i=0,j,flag=0,m;
        if(r1==node)
        {
                k++;
                l=0;
                sav[k][l++]=0;
        	return 1;
        }
        for(j=0;j<=col;j++)
        {
               	if(cfg[r1][j]==1)
                {
                	if(flag==1)
                        {
                        	i=0;
                        	//k++;
                        	while(sav[k-1][i]!=-1 && sav[k-1][i]!=m)
                                	sav[k][i++]=sav[k-1][i];
                        	l=i;
                        }
                	flag=1;
                        sav[k][l++]=j;
                      	m=j;
	               	if(dom(node,j)==0)
	               	{
	               		sav[k][l]=-1;
	               		l--;
	               		flag=0;
	               	}
                }
        }
        if(flag==0)
        	return 0;
}
void main()
{
	int i,j,node,flag=0,m;
        FILE *fp=fopen("CFG.TXT","r+");
        char c;
        for(i=0;i<10;i++)
        	for(j=0;j<10;j++)
                	cfg[i][j]=sav[i][j]=-1;
        c=fgetc(fp);
        while(c!=EOF)
        {
        	if(c=='\n')
                {
                	row++;
                        col=0;
                }
                else if(c==' ')
                {
                	col++;
                }
                else
                {
                	cfg[row][col]=c-'0';
                }
                c=fgetc(fp);
        }
        for(i=0;i<=row;i++,printf("\n"))
        	for(j=0;j<=col;j++)
                	printf("%d ",cfg[i][j]);
	sav[k][l++]=0;
        printf("Enter the node\n");
        scanf("%d",&node);
        dom(node,0);
        i=0;
        while(sav[0][i]!=-1)
        {
        	j=1;
                flag=0;
                if(k==1)
                {
                	while(sav[0][i]!=-1)
                		printf("%d ",sav[0][i++]);
                	break;
                }
                while(j<k)
                {
                	m=flag=0;
                        while(sav[j][m]!=-1)
                        {
                        	if(sav[j][m]==sav[0][i])
                                {
                                	flag=1;
                                        break;
                                }
                                m++;
                        }
                        if(flag==0)
                        	break;
                        j++;
                }
                if(flag==1)
                	printf("%d ",sav[0][i]);
                i++;
        }
}
