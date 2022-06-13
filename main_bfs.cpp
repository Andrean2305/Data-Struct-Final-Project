#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>
#include <string.h>
#include "board.cpp"
#include "player.cpp"
#include "target.cpp"

using namespace std;

clock_t c_start = clock();
// Below arrays detail all eight possible movements
// for a knight
int row[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int col[] = { -1, 1, 1, -1, 2, -2, 2, -2 };
 
// Check if (x, y) is valid chessboard coordinates.
// Note that a knight cannot go out of the chessboard
bool isValid(int x, int y, int N) {
    return (x >= 0 && x < N) && (y >= 0 && y < N);
}                                                 
 
// A queue node used in BFS
struct Node
{
    // (x, y) represents chessboard coordinates
    // `dist` represents its minimum distance from the source
    int x, y, dist;
 
    // Node constructor
    Node(int x, int y, int dist = 0): x(x), y(y), dist(dist) {}
 
    // As we are using struct as a key in a `std::set`,
    // we need to overload `<` operator`.
    // Alternatively, we can use `std::pair<int, int>` as a key
    // to store the matrix coordinates in the set.
 
    bool operator<(const Node& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
};

bool checkcor(int x,int y, int x1, int y1){
    for (int i = 0; i < 8; i++){
        if(x + row[i] == x1 && y + col[i] == y1){
            return true;
        }
    }
    
    return false;
}
 
// Find the minimum number of steps taken by the knight
// from the source to reach the destination using BFS
int findShortestDistance(int N, Node src, Node dest)
{   

    // set to check if the matrix cell is visited before or not
    set<Node> visited;
 
    // create a queue and enqueue the first node
    queue<Node> q;
    q.push(src);
    int parameter = 0;
    int x_check;
    int y_check;
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and process it
        Node node = q.front();
        q.pop();
 
        int x = node.x;
        int y = node.y;
        int dist = node.dist;
 
        // if the destination is reached, return distance
        if (x == dest.x && y == dest.y) {
            return {dist};
        }
 
        // skip if the location is visited before
        if (!visited.count(node))
        {   
            // mark the current node as visited
            visited.insert(node);
 
            // check for all eight possible movements for a knight
            // and enqueue each valid movement
            for (int i = 0; i < 8; i++)
            {
                // get the knight's valid position from the current position on
                // the chessboard and enqueue it with +1 distance
                int x1 = x + row[i];
                int y1 = y + col[i];
                           
                if (isValid(x1, y1, N)) {
                    
                    q.push({x1, y1, dist + 1});

                    
                }
            }
        }
    }

    // return infinity if the path is not possible
    return INT_MAX;
}

void print_str(const char str[],string prefix,int n, const int lenght, int x, int y, int x1, int y1, int max, int finish[], int board)
    {
        if (lenght == 1)
            {
                for (int j = 0; j < n; j++){
                    static int test[50];
                    int x_now = x;
                    int y_now = y;
                    int x_target = x1;
                    int y_target = y1;

                    string testing = prefix + str[j];

                    // cout << (int)testing[0] - 48 << endl;
                    for (int i = 0; i < max; i++){
                        test[i] = (int) testing[i] - 48;
                        if(x_now + row[test[i]] >= 0 && x_now + row[test[i]]<= board && y_now + col[test[i]]>= 0 && y_now + col[test[i]]<= board){
                            test[i] = (int) testing[i] - 48;
                            x_now += row[test[i]];
                            y_now += col[test[i]];
                        }
                        // cout << n << endl;
                    }

                    // && x_now >= 0 && x_now <= board && y_now >= 0 && y_now <= board
                    if(x_now == x_target && y_now == y_target){
                        // cout << "PATTERN = ";
                        // cout << test[0] << ' ' << test[1] << ' ' << test[2];
                        for (int i = 0; i < max; i++){
                            finish[i] = test[i];
                        // cout << n << endl;

                    }
                    }

                }

            }//Base case: lenght = 1, print the string "lenght" times + the remaining letter
        else
            {
               // One by one add all characters from "str" and recursively call for "lenght" equals to "lenght"-1
                for (int i = 0; i < n; i++){

                // Next character of input added
                    print_str(str, prefix + str[i], n, lenght - 1,x, y, x1, y1,max, finish,board);
                // "lenght" is decreased, because we have added a new character
                }
            }

}

int main() {
  board catur(0);
  player me(99,99);
  target you(99,99);

  int max_step;
  int finish[max_step];
  
  while (catur.board_length_width < 3){
    cout << "Enter Board Size (Min 3) : ";
    cin >> catur.board_length_width;
    cout << endl;
  }
  
  while(me.x_coordinate < 0 || me.x_coordinate > catur.board_length_width){
    cout << "Enter your x-coordinate [Min 0] [Max Board Size] : ";
    cin >> me.x_coordinate;
    cout << endl;
  }
  while(me.y_coordinate < 0 || me.y_coordinate > catur.board_length_width){
    cout << "Enter your y-coordinate [Min 0] [Max Board Size] : ";
    cin >> me.y_coordinate;
    cout << endl;
  }

  while(you.x_coordinate < 0 || you.x_coordinate > catur.board_length_width){
    cout << "Enter target x-coordinate [Min 0] [Max Board Size] : ";
    cin >> you.x_coordinate;
    cout << endl;
  }
  while(you.y_coordinate < 0 || you.y_coordinate > catur.board_length_width){
    cout << "Enter target y-coordinate [Min 0] [Max Board Size] : ";
    cin >> you.y_coordinate;
    cout << endl;
  }
  cout << "Your Coordinates now : " << me.x_coordinate << ", " << me.y_coordinate << endl;
  cout << "Your Target : " << you.x_coordinate << ", " << you.y_coordinate << endl;

  string drawing[catur.board_length_width][catur.board_length_width];
  for (int i = 0; i<catur.board_length_width; i++){
        for (int j = 0; j < catur.board_length_width; j++){
        drawing[i][j] = "O";}
   }
   
   drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "H";
   drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "T";
  
  cout << endl << "--------This is your board--------" <<endl;
  cout << "" << endl;
  for (int i = 0; i<catur.board_length_width; i++){
        for (int j = 0; j < catur.board_length_width; j++){
        cout << drawing[i][j] << "  " ;
        }
        cout << endl;
  }

  // source coordinates
  Node begin = {me.x_coordinate - 1, me.y_coordinate - 1}; //SRC

  // destination coordinates
  Node target = {you.x_coordinate - 1, you.y_coordinate - 1};
  if(me.x_coordinate == you.x_coordinate && me.y_coordinate == you.y_coordinate){
    cout << "You already reach your target";
  }else {
    cout << endl << "The minimum moves to get to the target is " << findShortestDistance(catur.board_length_width, begin, target) << endl;
    //   cout << "CPU time used: " << findShortestDistance_time << " ms\n";
    max_step = findShortestDistance(catur.board_length_width, begin, target);
    char arr[] = {'0', '1', '2', '3', '4', '5','6','7'};

    int n = sizeof arr;

    if(max_step > 10){
        cout << "The program is autokilling itself due to overload data. You can't see the history";
    return 0;
  }else{
    print_str(arr, "", n, max_step,me.x_coordinate,me.y_coordinate,you.x_coordinate,you.y_coordinate,max_step,finish,catur.board_length_width);
  }
  }
//   for (int i = 0; i<max_step ; i++){
//         cout<<finish[i] << ' ';
//   }
  clock_t c_end = clock();
  long double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
  cout << "CPU time used: " << time_elapsed_ms << " ms\n";
  cout << "CPU time used: " << time_elapsed_ms / 1000.0 << " s\n";

  cout << endl << "Doy want to see the steps?" << endl;
  cout << "Input (Y) if yes and (N) if no" << endl;

  string answer;
  cin >> answer;
  string userinput;
  int steps = 0;

  int x_now = me.x_coordinate;
  int y_now = me.y_coordinate;
  while(answer == "Y" || answer == "y" || answer == "yes"){
    cout << "STEPS : " << steps << '/' << max_step << endl;
    for (int i = 0; i<catur.board_length_width; i++){
        for (int j = 0; j < catur.board_length_width; j++){
            cout << drawing[i][j] << "  " ;
        }
        cout << endl;
   }
   cout<< "Input (N) to go next, (B) to go back, (C) for input step, (Q) to quit" << endl;
   cin >> userinput;
   if (userinput == "N" || userinput == "n" || userinput == "next"){
     if(steps >= max_step){
        cout << "This is already last step" << endl;
     }else{
            drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "O";
            drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "O";

            me.x_coordinate += row[finish[steps]];
            me.y_coordinate += col[finish[steps]];
            steps ++;

            drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "H";
            drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "T";
            if(steps == max_step){
                drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "*";
            }
       }
   }
   else if (userinput == "B" || userinput == "b" || userinput == "back"){
     if(steps <= 0){
        cout << "This is already the first step" << endl;
     }else {
        drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "O";
        drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "O";
        steps --;
        me.x_coordinate -= row[finish[steps]];
        me.y_coordinate -= col[finish[steps]];
        drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "H";
        drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "T";

       }
   }
   else if (userinput == "C" || userinput == "c" || userinput == "custom"){
    drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "O";
    drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "O";
    int custom;
    cout << "Input the step: ";
    cin >> custom;

    while(custom < 0 || custom > max_step){
        if (custom < 0){
            cout << "You cant input anything below zero" << endl;
        }else if (custom > max_step){
            cout << custom << " exceed the max number of step"<< endl;
        }
        cout << "Now, input your customize number again : ";
        cin >> custom;
    }
    me.x_coordinate = x_now;
    me.y_coordinate = y_now;
    for (int i = 0; i < custom; i++){
        me.x_coordinate += row[finish[i]];
        me.y_coordinate += col[finish[i]];
    }
    drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "H";
    drawing[catur.board_length_width - (you.y_coordinate + 1) + 1][you.x_coordinate - 1] = "T";

    if(custom == max_step){
        drawing[catur.board_length_width - (me.y_coordinate + 1) + 1][me.x_coordinate - 1] = "*";
    }
    steps = custom;
    
   }
   else if (userinput == "Q" || userinput == "q" || userinput == "quit" ){
        break;
   }else {
    cout << "I don't really understand that" << endl;
   }
  }
  cout << "Bye-Bye";

  return 0;
}
