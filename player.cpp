#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class player{
  public :
    int x_coordinate;
    int y_coordinate;

    vector<vector<int>>moves; //Declaring what is the move that was taken so we can show some kind of moves history

  player(int x, int y){
    x_coordinate = x;
    y_coordinate = y;
  }

  void movetotarget(){
    
  }
};  
