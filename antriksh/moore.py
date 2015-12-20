#include "iostream"
#include "fstream"
#include "cstring"

using namespace std;

#define M 4
#define N 2

int main(){
	int fs;
	int regex[10][10];
	int i,j, initial, final[10], k,m, flag=0, state, stin;
	char inval[100], outval[10], output[100];

	ifstream in("inmoore.txt");
	
	in>>initial;
	// cout<<initial;

	i=0;
	while(1){
		in>>fs;
		if(fs==-1){
			break;
		}
		final[i] = fs;
		i++;
	}

	m=i;

	for (i=0;i<M;i++){
		in>>outval[i];
		for (j=0;j<N;j++){
			in>>regex[i][j];
		}
	}

	cout<<"Input String : \n";
	cin>>inval;

	k = strlen(inval);
	state = 0;
	for(i=0;inval[i]!='\0';i++){
		stin = inval[i] - 97;
		output[i] = outval[state];
		state = regex[state][stin];
		
		if (state==-1){
			cout<<"Invalid code input. Breaking Code.\n";
			return 0;
		}
	}

	k=i;

	for(i=0;i<m;i++){
		if(state == final[i]){
			flag=1;
			break;
		}
	}

	if (flag==1)
	{
		cout<<"Output : ";
		for (int i = 0; i < k; i++)
		{
			cout<<output[i];
		}
		cout<<endl;
	}
	else{
		printf("This is no match !\n");
	}
	return 0;
}