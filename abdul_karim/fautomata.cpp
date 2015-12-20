#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
     string line;
     
     int automata[100][100],counti,countj;
     int size;
     counti=0;
     
     for(int i=0;i<100;i++)
     {
          for(int j=0;j<100;j++)
          {
               automata[i][j]=100;
          }
     }
     ifstream myfile( "input.txt" );
     if (myfile)  
     {
          while (getline( myfile, line ))
          {     
               countj=0;
               {
                    for(int i=0;i<line.size(); i++)
                    {
                         if(line[i]==' ')
                         {
                         
                         }
                         else
                         {
                              if(line[i]=='-')
                              {
                                   i++;
                                   automata[counti][countj++]=(line[i]-48)* -1;
                              }
                              else if(line[i]>=48 && line[i]<=56)
                              {
                                   automata[counti][countj++]=(line[i]-48);
                              }
                              
                         }
                    }
                    counti++;
               }
          }
          myfile.close();
     }
     else cout << "fooey\n";
     
     cout<<"FINITE AUTOMATA\n";
     for(int i=0;i<counti;i++)
     {
          for(int j=0;j<5;j++)
          {
               if(automata[i][j]!=100)
               printf("%d ",automata[i][j]);
          }
          printf("\n");
     }
     
     int initial=automata[0][0];
     int final=automata[1][0];
     
     char instance[100];
     cout<<"Enter the string"<<endl;
     cin>>instance;
     int sizeins=strlen(instance);
     cout<<sizeins;
     
     int row,col;
     row=initial;
     for(int i=0;i<sizeins;i++)
     {
          col=instance[i]-97;
          if(automata[row+2][col]==final)
               cout<<"accepted"<<endl;
          else if (automata[row+2][col]==-1)
          {
                    cout<<"error and not accepted"<<endl;
               }
          else
          {
               row=automata[row+2][col];
               row+=2;
          }
     }
     return 0;
}