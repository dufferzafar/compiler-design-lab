#include <iostream>
#include <fstream>

#include <string>
#include <cstring>
#include <sstream>

#define INPUT_FILE "automata_input.txt"

// Dimensions of transition table
#define MAX_ROWS 25
#define MAX_COLS 25

using namespace std;

////////////////////////////////////////////////////////////////

void line_to_arr(string line, int arr[], int & size) {
	string cell;
	istringstream line_stream(line);

	size = 0;
	while(getline(line_stream, cell, ',')) {	
		arr[size++] = atoi(cell.c_str());
	}
}

void print_arr(int arr[], int size) {
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void print_matrix(int mat[][MAX_COLS], int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		print_arr(mat[i], cols);
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////

// Automata Attributes
int starting_state;

int final_states[10];
int final_states_num = 0;

int transition[MAX_ROWS][MAX_COLS] = { 0 };
int rows = 0;
int cols = 0;

////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	ifstream input(INPUT_FILE);
	if (!input.is_open()) {
		cerr << "Couldn't open input file: " << INPUT_FILE;
		return 1;
	}

	string line;

	// Get starting state
	getline(input, line);
	starting_state = atoi(line.c_str());

	// Get final states
	getline(input, line);
	line_to_arr(line, final_states, final_states_num);

	// Read Transition Table
	while (getline(input, line)) {
		line_to_arr(line, transition[rows++], cols);
	}

	// Print out file
	cout << starting_state << endl;
	print_arr(final_states, final_states_num);
	print_matrix(transition, rows, cols);
	return 0;
}