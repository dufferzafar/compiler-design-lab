#include<stdio.h>
#include<conio.h>
int lead[30]={1,2,4,5,6,9,10},n=7,adj[10][10];
int block(int num)
{
	int i,blockno=0;
        for(i=0;i<n-1;i++)
        	if(num>=lead[i]&&num<=lead[i+1]-1)
                	return blockno;
                else
                	blockno++;
}
void main()
{
	int i,j,numi=1,numj,numg,flag=0;
        char c,str[10];
        FILE *fp=fopen("tacinp.txt","r+");
        clrscr();
        c=fgetc(fp);
        for(i=0;i<10;i++)
              	for(j=0;j<10;j++)
                	adj[i][j]=0;
        while(c!=EOF)
        {
        	if(c=='0')
		{
                	i=0;
                        str[i++]=c;
			while(c!=':')
                        {
                        	str[i++]=c;
                                c=fgetc(fp);
                        }
                        str[i]=NULL;
                        numj=numi;
                        numi=atoi(str);
                        //printf("numi %d\t",numi);
                        if(block(numi)!=block(numj) && flag==0)
                           	adj[block(numj)][block(numi)]=1;
                }
                else if(c=='g')
                {
                	c=fgetc(fp);
                        if(c=='o')
                        {
                        	c=fgetc(fp);
                                if(c=='t')
                                {
                                	c=fgetc(fp);
                                        if(c=='o')
                                        {
                                        //	if(block(numi)!=block(numj))
                                         //		adj[block(numj)][block(numi)]=1;
                                        	i=0;
                                                c=fgetc(fp);
                                                if(c==' ')
                                                	c=fgetc(fp);
                                                str[i++]=c;
                                                c=fgetc(fp);
                                                while(c!='\n' && c!=EOF)
                      				{
                                               	if(c==EOF)
                                                        	break;
                        				str[i++]=c;
                                			c=fgetc(fp);
                                                        printf("%c ",c);
                        			}
                            			str[i]=NULL;
                                                numg=atoi(str);
                                                printf("\nnumg %d",block(numg));
                                                adj[block(numi)][block(numg)]=1;
                        			//check(atoi(str));
                                                i=0;
                                                c=fgetc(fp);
                                                if(c==EOF)
                                                	break;
	                        		str[i++]=c;
                                                c=fgetc(fp);
						while(c!=':')
			                        {
                        				str[i++]=c;
			                                c=fgetc(fp);
                        			}
			                        str[i]=NULL;
                                                numj=numi;
                                                numi=atoi(str);
                                                if(flag==1)
	                                                adj[block(numj)][block(numi)]=1;
                                                flag=0;
                        			//check(atoi(str));
                                        }
                                }
                        }
                }
                else if(c=='i')
                {
                	c=fgetc(fp);
                        if(c=='f')
                        {
                        	flag=1;
                        	if(block(numi)!=block(numj))
                        		adj[block(numi)][block(numj)]=1;
                        }
                }
                c=fgetc(fp);
        }
        printf("\n");
        for(i=0;i<10;i++,printf("\n"))
        	for(j=0;j<10;j++)
                	printf("%d ",adj[i][j]);
        getch();
}