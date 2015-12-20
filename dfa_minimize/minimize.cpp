#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <map>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////

#define INPUT_FILE "input.txt"

#define MAX_ROWS 10
#define MAX_COLS 10

#define EMPTY -99

////////////////////////////////////////////////////////////////

// Automata Attributes
int initial_state;

vector<int> final_states;

int transition[MAX_ROWS][MAX_COLS];
int rows = 0;
int cols = 0;

int similarity[MAX_ROWS][MAX_ROWS];

// Stores similar pairs
vector< pair< int, int > > similar_pairs;

////////////////////////////////////////////////////////////////

// Returns whether state is final
int is_final(int state) {
    for (int i = 0; i < final_states.size(); i++) {
        if (state == final_states[i]) {
            return 1;
        }
    }
    return 0;
}

// Print similarity matrix
void print_similarity() {

    // Print header row
    cout << " ";
    for (int i = 0; i < rows; i++) {
        cout << i << " ";
    } cout << endl << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (similarity[i][j] == EMPTY) {
                cout << "  ";
            } else if (similarity[i][j] == -1) {
                cout << " -";
            } else {
                printf("%2d", similarity[i][j]);
            }
        }
        cout << endl;
    }
}

// Print transition matrix
void print_transitions() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << transition[i][j] << " ";
        }
        cout << endl;
    }
}

// Replace all transitions to state 'src' with state 'rep'
void replace_transitions(int src, int rep) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (transition[i][j] == src) {
                transition[i][j] = rep;
            }
        }
    }
}

// Convert a delimited line to array
void line_to_arr(string line, int arr[], int & size) {
    string cell;
    istringstream line_stream(line);

    size = 0;
    while (getline(line_stream, cell, ' ')) {
        arr[size] = atoi(cell.c_str());
        size++;
    }
}

////////////////////////////////////////////////////////////////

void read_file() {
    ifstream file(INPUT_FILE);

    string line;

    // Read initial state
    getline(file, line);
    initial_state = atoi(line.c_str());

    // Read final states
    getline(file, line);
    string cell; istringstream line_stream(line);
    while (getline(line_stream, cell, ' ')) {
        final_states.push_back(atoi(cell.c_str()));
    }

    // Read the rest of table
    rows = 0;
    while (getline(file, line)) {
        line_to_arr(line, transition[rows], cols);
        rows++;
    }

//  Print Final States
//    for (int i = 0; i < final_states.size(); i++) {
//        cout << final_states[i];
//    }

}

////////////////////////////////////////////////////////////////

// Checks whether s1 & s2 are similar
bool are_similar(int s1, int s2) {

    // Assume that the states are similar
    bool similar = true;

    // For each input check whether the target states are same
    for (int inp = 0; inp < cols; inp++) {
        similar = similar && (transition[s1][inp] == transition[s2][inp]);
    }

    return similar;
}

// Compare all states with each other and update similarity matrix
void compare_states(bool & update_occurred) {
    for (int s1 = 0; s1 < rows; s1++) {
        for (int s2 = s1; s2 < rows; s2++) {

            if (are_similar(s1, s2)) {
                similarity[s1][s2] = 1;

                // Don't insert trivial pairs
                if (s1 != s2) {

                    // Find whether the pair is already inserted or not
                    bool alread_inserted = false;
                    for(int i = 0; i < similar_pairs.size(); i++) {
                        pair<int, int> p(similar_pairs[i]);

                        if (p.first == s1 && p.second == s2)
                            alread_inserted = true;
                    }

                    //  Insert only when not already inserted
                    if (!alread_inserted) {
                        similar_pairs.push_back(pair<int, int> (s1, s2));
                        update_occurred = true;
                    }

                }

            } else {
                similarity[s1][s2] = -1;
            }
        }
    }
}

////////////////////////////////////////////////////////////////

int main() {

    read_file();
//    print_transitions();

    // Ensure that the similarity matrix is empty
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            similarity[i][j] = EMPTY;
        }
    }

    /////////////////////////////////
    // Perform initial optimizations
    /////////////////////////////////

    // Fill final state entries
    for (int st = 0; st < final_states.size(); st++) {
        for (int i = 0; i < rows; i++) {
            similarity[i][final_states[st]] = -1;
            similarity[final_states[st]][i] = -1;
        }
    }

    // Fill diagonal entries
    for (int i = 0; i < rows; i++) {
        similarity[i][i] = 1;
    }

    ///////////////////////////////////
    // Comparision amongst all states
    ///////////////////////////////////

    bool update_occurred;
    do {
        update_occurred = false;

        // Compare all states with each other
        compare_states(update_occurred);

        // Make updates to the transition table for each similar pair
        for(int i = 0; i < similar_pairs.size(); i++) {
            pair<int, int> p(similar_pairs[i]);
            replace_transitions(p.first, p.second);
        }

    } while (update_occurred);

    // Print Similarity Matrix
    cout << "Similarity Matrix: ";
    cout << endl << endl;
    print_similarity();
    cout << endl << endl;

    // Print All Similar Pairs
    cout << "Similar Pairs: ";
    cout << endl << endl;
    for(int i = 0; i < similar_pairs.size(); i++) {
        pair<int, int> p(similar_pairs[i]);
        cout << p.first << "  " << p.second << endl;
    }
}
