# include <iostream>
# include <vector>
# include <unistd.h>
# include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;
using Row_t = Table::Row_t;

void print_grid(int n, vector<int> &v){
    system("clear");

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

    sleep(1);
}

int main()
{
    int n;
    cout << "Enter the size of the board (n for n-queens, up to 8): ";
    cin >> n;
    if (n < 1 || n > 8) {
        cout << "Invalid input." << endl;
        return 1;  
    }
    return 0;
}