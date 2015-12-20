#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

#define STATE 4
#define ALPHA 3

#define AUTOMATA_INPUT "automata_input.txt"
#define TEST_CASES_INPUT "test_cases_input.txt"

int initial_state;

int final_states[10];
int final_states_count = 0;

int transition[STATE][ALPHA] = { 0 };
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

void print_matrix(int mat[][ALPHA], int rows, int cols) {
    for (int i = 0; i < rows; ++i)
        print_arr(mat[i], cols);
    cout << endl;
}

////////////////////////////////////////////////////////////////////

void read_file() {
    ifstream file(AUTOMATA_INPUT);
    if (!file.is_open()) {
        cerr << "Couldn't open input file: " << AUTOMATA_INPUT;
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

    // Print Automata
    cout<<"Automata" << endl;
    cout << "----------------------------------------------------";
    cout << endl << endl;

    cout<<"\t[A-Z],[a-z],_\t[0-9]\t\tSpecial\n";

    for(int i = 0; i < STATE; i++){
        cout << "q" << i << "\t";

        for(int j = 0; j < ALPHA; j++)
            cout << transition[i][j] << "\t\t";

        cout << endl;
    }
    cout<<"\n\n";

    // Open test cases
    ifstream test_cases(TEST_CASES_INPUT);

    int cur_state;
    int invalid;
    string line;

    const char *input_str;

    cout << "Test Cases" << endl;
    cout << "----------------------------------------------------";
    cout << endl << endl;

    // Read each line
    while (getline(test_cases, line)) {
        cout << line;

        input_str = line.c_str();

        cur_state = initial_state;

        invalid = 0;

        for (int i = 0; input_str[i] != '\0'; i++) {
            if ((input_str[i] >= 'a' && input_str[i] <= 'z') ||
                (input_str[i] >= 'A' && input_str[i] <= 'Z') ||
                input_str[i] == '_') {
                cur_state = transition[cur_state][0];
            } else if (input_str[i] >= '0' && input_str[i] <= '9') {
                cur_state = transition[cur_state][1];
            } else {
                cout << "\t\tRejected";
                invalid = 1; break;
            }
        }

        if (invalid) {
            cout << "\t\tInvalid Input\n";
        } else {
            if (cur_state == 1) {
                cout << "\t\tAccepted\t\tIdentifier\n";
            } else if (cur_state == 2) {
                cout << "\t\tAccepted\t\tNumber\n";
            } else {
                cout << "\t\tRejected\t\tInvalid Input\n";
            }
        }
    }

    return 0;
}
