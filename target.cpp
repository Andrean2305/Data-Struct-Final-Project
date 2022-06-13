#include <iostream>
#include <vector>
using namespace std;

class target{
  public :
    int x_coordinate;
    int y_coordinate;

    vector<vector<int>>moves; //Declaring what is the move that was   taken so we can show some kind of moves history

  target(int x, int y){
    x_coordinate = x;
    y_coordinate = y;
  }

};  
