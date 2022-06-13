#include <iostream>
#include <vector>
using namespace std;

//Initializing the chess board

class board {
  public :
    vector<vector<char>>tile{
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
        {'O','O','O','O','O','O','O','O'},
    }; 

    int board_length_width;

    board(int n){
      board_length_width = n;
    }

};

