#include <stdio.h>
#include <iostream>
#include <ctime>
#include <stack>

using namespace std;

clock_t c_start = clock();

#define N 8

int Movement_Check(int i, int j, int board[N+1][N+1]) {
  if (i>=1 && i<=N && j>=1 && j<=N && board[i][j]==-1)
    return 1;
  return 0;
}

int knight_move(int board[N+1][N+1], int x, int y, int step, int x_move[], int y_move[]) {
  if (step == N*N) // finish recursive if it reach maximum steps/ already finish the tour
    return 1;

  for(int k=0; k<8; k++) {
    int next_x = x+x_move[k]; // check move increment x coordinate 
    int next_y = y+y_move[k]; // check move increment y coordinate

    if(Movement_Check(x+x_move[k], y+y_move[k], board)) {
      board[next_x][next_y] = step;
      if (knight_move(board, next_x, next_y, step+1, x_move, y_move)) // recursive method
        return 1;
      board[x+x_move[k]][y+y_move[k]] = -1; // backtracking
    }
  }

  return 0;
}

int startknighttour() {
  int board[N+1][N+1]; // define board "size"

  int i, j;
  for(i=1; i<=N; i++) {
    for(j=1; j<=N; j++) {
      board[i][j] = -1;
    }
  }

  int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};
  int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};
  
  board[1][1] = 0; // placing knight at cell(1, 1)

  if (knight_move(board, 1, 1, 1, x_move, y_move)) { // if backtracking function return true(1) it will call for loop to print all of the knight tour
    for(i=1; i<=N; i++) {
      for(j=1; j<=N; j++) {
        printf("%d\t",board[j][i]);
      }
      printf("\n");
    }
    return 100;
  }
  return 999;
}

int main() {
  printf("%d\n",startknighttour());

  clock_t c_end = clock();
  long double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
  cout << "CPU time used: " << time_elapsed_ms << " ms\n";
  cout << "CPU time used: " << time_elapsed_ms / 1000.0 << " s\n";

  return 0;
}