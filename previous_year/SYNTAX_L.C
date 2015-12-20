#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>


int checkSyntaxAnalysis()
{
	FILE*f;
	char str[3],ch,ch2;
        int i=0;

        f = fopen("syntax.txt","r");

        ch = fgetc(f);
        while(ch!=EOF)
        {
                if(i!=3)
                 str[i++]=ch;

                else
                {
                	if(strncmp(str,"for",3)==0)
                        {
                        	if(ch=='(')
                                {
                            		ch = fgetc(f);
                                        if(ch!=';')
                                        {
                                        	while(ch!='=')
                                      	 	{
                                       		 	ch = fgetc(f);
                                               	        if(ch==EOF)
                                                	{
                                                        	printf("\nError in initialization.");
                                                		return 2;
                                                	}
						}


                                                ch = fgetc(f);
                                                if(isalnum(ch))
                                                {
                                                	ch=fgetc(f);
                                                        if(ch==';')
                                                        {
                                                             ch=fgetc(f);
                                                             while(isalpha(ch))
                                                             {
                                                             	ch = fgetc(f);
                                                                if(ch==EOF)
                                                		{
                                                			return 3;
                                                		}
							     }

                                                             if(ch=='<'||ch=='>'||ch=='=')
                                                             {
                                                             	ch2=fgetc(f);

                                                                if(ch!='='&&(ch2=='='||isalnum(ch2
								)))
                                                                {

								}

                                                                else if(ch=='='&&ch2=='=')
                                                                {
                                                                	ch2=fgetc(f);
								}

                                                                else
                                                                {
                                                                        printf("\nError in condition.");
                                                                	return 4;
								}

                                                                ch=fgetc(f);
                                                                while(ch!=';')
                                                                {
                                                                	ch=fgetc(f);
                                                                        if(ch==EOF)
                                                                        {
                                                                                printf("\nError in condition.");
                                                                        	return 5;
									}
								}
                                                                while(ch!=')')
                                                                {
                                                                	ch=fgetc(f);
                                                                        if(ch==EOF)
                                                                        {
                                                                                printf("\nLoop bracket not closed.");
                                                                        	return 6;
                                                                        }
								}

                                                                ch = fgetc(f);
                                                                ch2 = fgetc(f);

                                                                if(ch=='{'&&ch2=='}')
                                                                {
                                                                	return 1;
								}

                                                                else
                                                                {
                                                                	printf("Error in loop parenthesis.");
                                                                	return 7;
                                                                }
							     }

							}
                                                        else
                                                        {
                                                                printf("\nError in condition.");
                                                        	return 8;
							}
						}
                                                else
                                                {
                                                        printf("\nError in initialization.");
                                                	return 9;
                                                }
                                        }

                                        else
                                        {
                                                printf("\nError in initialization.");
                				return 10;
					}
				}

                                else
                                {
                                	printf("\nError in loop parenthesis.");
					return 11;
                                }
			}

                        else
                        {
                                printf("\nError in loop label.");
                               	return 12;
			}
		}

                ch = fgetc(f);
	}

	return 1;
}

void main()
{
	int error;

	fflush(stdin);
        clrscr();

        error = checkSyntaxAnalysis();

	if(error==1)
        {
        	printf("\nFor Loop is syntactically correct.");
	}

        else
        {
        	printf("\nSyntax Error Code: %d",error);
	}

        getch();
}