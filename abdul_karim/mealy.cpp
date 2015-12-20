#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int main()
{
    ifstream infile; 
    infile.open("mealy.txt"); 
    
    int initial,i=0,k=0,l=0,nf,nr,nc,m=0;
    char ch;
    //cout<<"helloworld";
    int mealy[100][100],output[100][100];
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
           	if(m%2==0)
		{
		        if(rline[j]!=' ')
		        {
				if(rline[j]=='-')
		       	        mealy[i][k]=-1;
			else
				mealy[i][k]=rline[j]-'0';
		    		cout<<mealy[i][k]<<" "<<k<<" ";
		            k++;
				m++;
		        }
            	}
		else
		{
			
		        if(rline[j]!=' ')
		        {
				//cout<<"abdul";				
				if(rline[j]=='-')
		       	        output[i][l]=-1;
				else
				output[i][l]=rline[j]-'0';
		    		//cout<<output[i][l]<<" ";
		            l++;
				m++;
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
    while(inputVal[i]!='\0')
    {
        inputvalIndex=inputVal[i]-'0';
//cout<<inputvalIndex<<"\n";
        
            result= mealy[j][inputvalIndex];
           
        
        if(result==-1)
	break;
	 cout<<output[j][inputvalIndex];
	j=result;
        i++;
    }
  
}

cout<<"\n";
    return 0;
}
