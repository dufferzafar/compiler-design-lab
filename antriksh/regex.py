#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>
#include <set>

using namespace std;

#define INPUT_FILE "regex.txt"

set<int> expression;
set<int>::iterator it;

int main(){
    ifstream file(INPUT_FILE);

    string line;
    int var;
    // separating the units combined with a dot
    getline(file,line);
    istringstream line_stream(line);
    string dot_sep;
    while(getline(line_stream, dot_sep, '.')) {
        //cout<<dot_sep<<".";
        expression.insert(atoi(dot_sep.c_str()));
    }

    it = expression.begin();
    while(it != expression.end())
    {
        cout << *it << endl;
        it++;
    }

}
