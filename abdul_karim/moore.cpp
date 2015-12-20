#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int main()
{
    ifstream infile; 
    infile.open("moore.txt"); 
    
    int initial,i=0,k=0,l=0,nf,nr,nc,m=0;
    char ch;
    //cout<<"helloworld";
    int moore[100][100],output[100];
    string rline;
    infile.get(ch);
    initial=(int)ch-48;
    getline(infile,rline);
    int j=0;
    int len;
/*
        len=rline.size();
        
        for(j=0;j<len;j++)
        {
            //final[j]=rline[i];
            // cout<<rline[i];
            if(rline[j]!=',')
            {
                cout<<"abdul";
            final[k]=rline[j];
            cout<<final[k];
                k++;
            }
        }
        cout<<"\n";*/
        //i++;
    
   // cout<<rline;
    cout<<initial<<"\n";
    i=0;
    
    while(getline(infile,rline)){
        len=rline.size();
        k=0;l=0;m=0;
        for(j=0;j<len;j++)
        {
           	if(j!=(len-1))
		{
		        if(rline[j]!=' ')
		        {
				if(rline[j]=='-')
		       	        moore[i][k]=-1;
			else
				moore[i][k]=rline[j]-'0';
		    		cout<<moore[i][k]<<" ";
		            k++;
				
		        }
            	}
		else
		{
			
		        if(rline[j]!=' ')
		        {
				
				output[i]=rline[j]-'0';
		    		cout<<output[i]<<" ";
		            
		        }
            	}
        }
      
        cout<<"\n";
        i++;
    }


    string inputVal;
    int inputvalIndex;
while(1){
    cout<<"\nEnter the string\n";
    cin>>inputVal;
    i=0;
    j=initial;k=0;
    int result;
	cout<<output[j];
    while(inputVal[i]!='\0')
    {
        inputvalIndex=inputVal[i]-'0';
//cout<<inputvalIndex<<"\n";
        
            result= moore[j][inputvalIndex];
           
        
        if(result==-1)
	break;
	 cout<<output[result];
	j=result;
        i++;
    }
  
}

cout<<"\n";
    return 0;
}
