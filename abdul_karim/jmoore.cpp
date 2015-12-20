#include<fstream>
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int main()
{
    int automata[100][100];
    string line;
    
    ifstream myfile ("inputmoore.txt");
    
    
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            automata[i][j]=100;
        }
    }
    int counti,countj;
    counti=0;
    if(myfile)
    {
        while(getline(myfile,line))
        {
            
            countj=0;
            //cout<<line<<endl;
            for(int i=0;i<line.size();i++)
            {
                if(line[i]!=' ')
                {
                    if(line[i]=='-')
                    {
                        i++;
                        automata[counti][countj++]=((line[i]-48)* -1);
                    }
                    else
                    {
                        automata[counti][countj++]=((line[i]-48));                
                    }
                }
            
            }
            
            counti++;
        }
        
        myfile.close();
    }
    int jmax;
    cout<<"MOORE MACHINE:"<<endl;
    for(int i=0;i<counti;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(automata[i][j]==100)
            {
                break;
                
            }
            else
            {
                cout<<automata[i][j]<<" ";
                if(i==1)
                    jmax=j-1;
            }
        }
        cout<<endl;
    }
    
    string str;
    
    /*cout<<endl<<"JMAX: "<<jmax<<endl;*/
    cout<<"Enter input string: ";
    cin>>str;
    
    int initial=automata[0][0];
    int now=initial+1;
    
    
    for(int i=0;i<str.size();i++)
    {
        
        char ch=str[i];                                         
        
        if((automata[now][ch-97]!= -1)&&(ch-97 <=jmax))
        {
            cout<<str[i]<<" : "<<automata[automata[now][ch-97] +1][jmax+1]<<endl;
        }
        else
            cout<<endl<<"then Error"<<endl;
        
        int now=automata[now][ch-97]+1;
    }
    return 0;
}