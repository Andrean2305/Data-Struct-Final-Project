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

    void drawboard(){
      // for (int i; i<board_length_width; i++)
      //   for (int j; j < board_length_width; j++)
      //     board_draw[i][j] = "O";

      // for (int i; i<board_length_width; i++)
      //   for (int j; j < board_length_width; j++)
      //     cout << board_draw[i][j] ;
        
    }
};

