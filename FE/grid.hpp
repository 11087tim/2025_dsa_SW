# ifndef GRID
# define GRID
# include <iostream>
# include <vector>
# include <unistd.h>

using namespace std;


// Consider a 0-based array:
//  If a queen is placed at i-th row, j-th col, set arr[i] = j. 
//  Otherwise, set arr[i] = -1

void print_grid(int n, vector<int> &v){
    system("clear");
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if((i+j)%2) cout<<"\033[90;7m";
            else cout<<"\033[95;7m";
            if(v[i] == j) cout << " Q ";
            else cout << "   ";
        }
        cout << "\n";
    }
    sleep(1);
}
# endif