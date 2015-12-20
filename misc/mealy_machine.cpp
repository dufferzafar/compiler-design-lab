#include <iostream>
#include <string.h>

using namespace std;

/**
 * i : present state
 *
 * j : input symbol
 *
 * Todo: Read from file
 */

int state_matrix[][2] = {
	{0, 1}, 
	{0, 1}
};

int output_matrix[][2] = {
	{1, 0}, 
	{1, 0}
};

int main(int argc, char const *argv[])
{
	// Initial State
	int cur_state = 0;

	// Current Output
	int cur_output = 0;

	// 
	char input[10]; 

	cout << "Enter input string" << endl;
	cin >> input;

	// Header
	cout << "Output: " << endl;
	cout << "S - O" << endl;

	int length = strlen(input);
	for (int i = 0; i < length; ++i)
	{
		int cur_input = int(input[i]) - 48;

		cur_state = state_matrix[cur_state][cur_input];
		cur_output = output_matrix[cur_state][cur_input];

		cout << cur_state << " - " << cur_output << endl;
	}	

	cout << endl;
	return 0;
}