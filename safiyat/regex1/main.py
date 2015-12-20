#include <iostream>
#include <string>
#include "regexp.h"

using namespace std;

int main()
{
	string a, t;
	cout << "Enter the Regular Expression: ";
	cin >> a;
	regexp r(a);
	if(!r.isvalid())
	{
		cout << "Invalid Regular Expression!!!" << endl;
		return -1;
	}
	while(true)
	{
		cout << "Enter the test string: ";
		cin >> t;
		if(t == "end")
			break;
		if(r.validate(t))
			cout << "String is a valid match." << endl;
		else
			cout << "String is an invalid match." << endl;
	}
	return 0;
}