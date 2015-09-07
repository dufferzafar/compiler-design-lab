#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define MAX_ROWS 5
#define MAX_COLS 5

// Transition table is filled with these values at the beginning
#define EMPTY -99

/*

INPUT FILE FORMAT:

Initial state
Set of final states
Transition table

Multiple transition states are separated by comma

-1 represents no transition

---

0
0 1
1,0,2 2
-1 1,0
1,2 0

*/

#define INPUT_FILE "input.txt"

////////////////////////////////////////////////////////////////////

void print_1d(int arr[], int size, char sep) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << sep;
    cout << endl;
}

void print_table(int mat[][MAX_COLS][MAX_ROWS]) {
    for(int i = 0; i < MAX_ROWS; ++i) {
        for(int j = 0; j < MAX_COLS; ++j) {
            for(int k = 0; k < MAX_ROWS; ++k) {
                if (mat[i][j][k] != EMPTY)
                    cout << mat[i][j][k] << ",";
            }

            cout << " ";
        }

        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////

int initial_state;

set<int> final_states;

// i = current state
// j = current input
// k = next state
int transition[MAX_ROWS][MAX_COLS][MAX_ROWS];

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
    istringstream line_stream(line); string cell;
    while(getline(line_stream, cell, ' ')) {
        final_states.insert(atoi(cell.c_str()));
    }

    // Rest of the file contains a transition table
    int i = 0;
    while (getline(file, line)) {

        string cell;
        istringstream line_stream(line);

        int j = 0;
        // Columns are separated by space
        while(getline(line_stream, cell, ' ')) {

            string elem;
            istringstream cell_stream(cell);

            int k = 0;
            // Then each column is further separated by a comma
            while(getline(cell_stream, elem, ',')) {
                transition[i][j][k] = atoi(elem.c_str());
                k++;
            }

            j++;
        }

        i++;
    }
}

int main(int argc, char const *argv[]) {

    // Clear transition table
    for(int i = 0; i < MAX_ROWS; ++i)
        for(int j = 0; j < MAX_COLS; ++j)
            for(int k = 0; k < MAX_ROWS; ++k)
                transition[i][j][k] = EMPTY;

    read_file();
    // print_table(transition);

    string input;
    cout << "Enter input: ";
    cin >> input;

    // We begin at the initial state
    vector<int> current_states;
    current_states.push_back(initial_state);

    // Iterate over each input character
    for(int i = 0; i < input.size(); i++) {
        int cur_input = input[i] - 48;

        // States that can be reached from the current state
        vector<int> next_states;

        // Iterate over each of the current states
        for(int j = 0; j < current_states.size(); j++) {
            int cur_state = current_states[j];

            // Find the set of possible next states
            for(int k = 0; k < MAX_ROWS; k++) {
                int next_state = transition[cur_state][cur_input][k];
                if (next_state != EMPTY) {

                    // No transition possible
                    if (next_state == -1) {
                        cout << "Input NOT accepted";
                        return 0;
                    }

                    next_states.push_back(next_state);
                }
            }
        }

        current_states = next_states;
    }

    // Convert the current_states vector to a set, so we can easily take intersection
    // current_states was initially taken as a vector because we had to access an element by index
    set<int> set_current_states(current_states.begin(), current_states.end());

    // If any of the current states is also a final state,
    // then the input is considered accepted
    std::vector<int> intersection;
    set_intersection(set_current_states.begin(), set_current_states.end(),
                     final_states.begin(), final_states.end(),
                     back_inserter(intersection));

    // If the intersection is not null
    if (intersection.size() > 0) {
        cout << "Input Accepted";
    } else {
        cout << "Input NOT Accepted";
    }

    return 0;
}
