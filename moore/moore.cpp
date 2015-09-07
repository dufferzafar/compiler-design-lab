#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#define MAX_ROWS 5
#define MAX_COLS 5

/*

INPUT FILE FORMAT:

states, output

0 2, 1
1 1, 0
1 0, 1

*/

#define INPUT_FILE "input.txt"

int  state_matrix[MAX_ROWS][MAX_COLS];
int  output[MAX_ROWS];

////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////

// Read file and fill matrices
void read_file() {
    ifstream file(INPUT_FILE);
    if (!file.is_open()) {
        cerr << "Couldn't open input file: " << INPUT_FILE;
    }

    string line;

    int i = 0;
    while (getline(file, line)) {

        string cell;

        // Remove the last three characters from the line; for eg: ', 2'
        istringstream line_stream(line.substr(0, line.length() - 3));

        int j = 0;
        while(getline(line_stream, cell, ' ')) {

            // Cell is of the form 'state'
            // We store it by converting to int
             state_matrix[i][j] = cell[0] - 48;

            j++;
        }

        // The last character contains the output of that state
        output[i] = line[line.length() - 1] - 48;

        i++;
    }
}

int main(int argc, char const *argv[])
{
    read_file();

    // print_matrix(state_matrix, 3, 2);
    // print_arr(output, 3);

    // Initial State
    int cur_state = 0;

    // Current Output
    int cur_output = 0;

    // Input String
    string input;

    cout << "Enter input string: ";
    cin >> input;
    cout << endl;

    // Header
    cout << "Output: " << endl << endl;
    cout << "I - S - O" << endl;
    cout << "---------" << endl;

    // Print intial values
    // cout << "-" << " - " << cur_state << " - " << cur_output << endl;
    // cout << "---------" << endl;

    int length = input.length();
    for (int i = 0; i < length; ++i)
    {
        // Convert char '1'/'0' to int 1/0
        int cur_input = int(input[i]) - 48;

        cur_state = state_matrix[cur_state][cur_input];
        cur_output = output[cur_state];

        cout << cur_input << " - " << cur_state << " - " << cur_output << endl;
    }

    return 0;
}
