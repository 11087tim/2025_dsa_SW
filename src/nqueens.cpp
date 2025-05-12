# include <iostream>
# include <vector>
# include <unistd.h>
# include <tabulate/table.hpp>
# include <string>
# include <cctype>
# include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace tabulate;
using Row_t = Table::Row_t;

void print_grid(int n, const vector<int> &v, bool clear_output = true){
    if (clear_output) system("clear");

    Table grid;
    for(int i=0; i<n; ++i){
        Row_t tmp;
        for(int j=0; j<n; ++j){
            if(v[i] == j) tmp.push_back("Q");
            else tmp.push_back(" ");
        }
        grid.add_row(tmp);
    }
    cout << grid << endl;

    this_thread::sleep_for(chrono::milliseconds(500)); // Sleep for visualization
}


bool insert(int n, int row, int col, vector<int> &current)
{
    // Check if the current position is valid for placing a queen.
    // If valid, place the queen and return true. Otherwise, return false.
    for (int i = 0; i < n; ++i) {
        if (current[i] == -1) continue; // Skip empty rows
        if (current[i] == col || abs(current[i] - col) == abs(i - row)) {
            return false; // Conflict with another queen
        }
    }
    current[row] = col; // Place the queen
    return true;
}

bool solve_nqueens(int n, int r, const vector<int> &rows, vector<int> &current)
{
    // Try to place the remaining queens in the grid.
    // If all queens are placed successfully, return true. Otherwise, return false.
    // Requires the current with no conflict and the rows with available rows (has no queens already exist) unique.
    if (r == rows.size()) {
        return true; // All queens placed successfully
    }
    for (int c = 0; c < n; ++c) {
        // For visualization, we will print the grid after placing each queen.
        current[rows[r]] = c; // Try placing the queen in the current row
        print_grid(n, current); // Print the grid after placing the queen
        current[rows[r]] = -1; // Reset the position

        // Check if the current position is valid for placing a queen.
        if (insert(n, rows[r], c, current)) { // Try to place a queen
            if (solve_nqueens(n, r + 1, rows, current)) {
                return true; // Solution found
            }
            current[rows[r]] = -1; // Backtrack
        }
    }
    return false; // No valid position found
}

bool solve(int n, vector<pair<int, int>> &solution)
{
    // If the solution is found, return true. Otherwise, return false.
    // Assumed zero-based indexing for rows and columns.
    // Support for n-queens problem with n in [1, 8] and with some queens already placed.

    // Check whether all queens are not seeing each other.
    if (solution.size() > n) {
        cout << "Too many input pairs." << endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        return false; // Invalid solution
    }

    // Find the solution
    vector<int> current(n, -1); // Initialize the current row with -1 (no queen placed)
    for (int i = 0; i < solution.size(); ++i) {
        current[solution[i].first] = solution[i].second; // Place the queen
    }

    print_grid(n, current);

    for (int i = 0; i < solution.size(); ++i) {
        for (int j = i + 1; j < solution.size(); ++j) {
            if (solution[i].first == solution[j].first || solution[i].second == solution[j].second ||
                abs(solution[i].first - solution[j].first) == abs(solution[i].second - solution[j].second)) {
                cout << "Conflict between queens." << endl;
                this_thread::sleep_for(chrono::milliseconds(5000));
                return false; // Conflict between queens
            }
        }
    }

    vector<bool> row_mask(n, true); // Track available rows
    for (int i = 0; i < n; ++i) {
        if (current[i] != -1) {
            row_mask[i] = false; // Mark the row as occupied
        }
    }
    vector<int> rows; // Store the available rows
    for (int i = 0; i < n; ++i) {
        if (row_mask[i]) {
            rows.push_back(i); // Add available rows
        }
    }
    if (solve_nqueens(n, 0, rows, current)) { // Try to solve the n-queens problem
        for (int i = 0; i < n; ++i) {
            if (current[i] != -1) {
                solution.push_back({i, current[i]}); // Store the positions of queens
            }
        }
        return true; // Solution found
    } else {
        return false; // No solution found
    }
}

int main()
{
    string s;
    int n;
    while (true) {
        cout << "Enter the size of the board (n for n-queens, up to 8): ";
        cin >> s;
        if(!isdigit(s[0])){
            cout << "Invalid input. Try again." << endl;
            continue; // Invalid input
        }
        n = stoi(s);
        if (n < 1 || n > 8) {
            cout << "Invalid input. Try again." << endl;
            continue; // Invalid input
        }
        break; // Valid input
    }
    vector<pair<int, int>> solution; // Store the positions of queens
    cout << "Enter the positions of queens (row, column) or -1 to finish:" << endl;
    while (true) {
        int row, col;
        cin >> s;
        if(!isdigit(s[0]) && s[0]!='-'){
            cout << "Invalid input. Try again." << endl;
            continue; // Invalid input
        }
        row = stoi(s);
        if (row == -1) break; // End input

        cin >> s;
        while(!isdigit(s[0])){
            cout << "Invalid input. Try again." << endl;
            cin >> s;
        }
        col = stoi(s);

        if (row < 0 || row >= n || col < 0 || col >= n) {
            cout << "Invalid position. Try again." << endl;
            continue; // Invalid position
        }
        solution.push_back({row, col}); // Store the position of the queen
    }
    bool found = solve(n, solution); // Start solving the n-queens problem

    // Clear the output
    system("clear");

    // Check if the solution is found
    if (!found) {
        cout << "No solution found." << endl;
        return 0; // No solution found
    }

    // Print the final grid
    cout << "Solution found!" << endl;
    vector<int> positions(n, -1);
    for (const auto &p : solution) {
        positions[p.first] = p.second; // Store the positions of queens
    }
    print_grid(n, positions, false); // Print the final grid
    return 0;
}