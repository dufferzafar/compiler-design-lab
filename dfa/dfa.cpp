#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#define MAX_ROWS 5
#define MAX_COLS 5

/*

INPUT FILE FORMAT:

Initial state
Set of final states
Transition table

-1 represents no transition

---

0
0 1 2
1 2
0 1
1 0

*/

#define INPUT_FILE "input.txt"

int initial_state;

int final_states[10];
int final_states_count = 0;

int transition[MAX_ROWS][MAX_COLS] = { 0 };
int rows = 0;
int cols = 0;

////////////////////////////////////////////////////////////////////

// Converts a space separated string to array
void line_to_arr(string line, int arr[], int & size) {
    string cell;
    istringstream line_stream(line);

    size = 0;
    while(getline(line_stream, cell, ' ')) {
        arr[size] = atoi(cell.c_str());
        size++;
    }
}

void print_arr(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void print_matrix(int mat[][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        print_arr(mat[i], cols);
    cout << endl;
}

////////////////////////////////////////////////////////////////////

void read_file() {
    ifstream file(INPUT_FILE);
    if (!file.is_open()) {
        cerr << "Couldn't open input file: " << INPUT_FILE;
    }

    string line;

    // First line contains initial state
    getline(file, line);
    initial_state = atoi(line.c_str());

    // Second line contains a set of final states
    getline(file, line);
    line_to_arr(line, final_states, final_states_count);

    // Rest of the file contains a transition table
    rows = 0;
    while (getline(file, line)) {
        line_to_arr(line, transition[rows], cols);
        rows++;
    }
}

int main(int argc, char const *argv[]) {

    read_file();

    // print_matrix(transition, rows, cols);
    // print_arr(final_states, final_states_count);

    // We begin at the inital state
    int cur_state = initial_state;

    // Input String
    string input;

    cout << "Enter input string: ";
    cin >> input;
    cout << endl;

    // Stores the length of the input that has been read
    int i = 0;

    // Make all the transitions
    int length = input.length();
    for (i = 0; i < length; ++i) {

        // Convert char '1'/'0' to int 1/0
        int cur_input = int(input[i]) - 48;

        cur_state = transition[cur_state][cur_input];

        // Break if there is no transition
        if (cur_state == -1) {
            break;
        }
    }

    // Check whether the current state is one of the final states
    bool current_is_in_final = false;
    for (int j = 0; j < final_states_count; ++j) {
        if (final_states[j] == cur_state)
            current_is_in_final = true;
    }

    // Input is accepted when final state is reached and entire input string has been read
    if (current_is_in_final && (i == input.length())) {
        cout << "Input accepted.";
    } else {
        cout << "Input NOT accepted.";
    }

    return 0;
}
