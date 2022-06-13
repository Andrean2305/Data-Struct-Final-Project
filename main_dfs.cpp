// #include <iostream>
// #include "knight.h"

// const int moves = 8;
// const int x_inc [moves] = {-2, -2, -1, -1, 1, 1, 2, 2};
// const int y_inc [moves] = {1, -1, 2, -2, -2, 2, -1, 1};

// using namespace std;

// //Initializes count which keeps track of the moves, current row and current column.
// knight::knight(int size, int start_row, int start_col)
// {
// 	count = 1;
// 	board_size = size;
// 	curr_row = start_row;
// 	curr_col = start_col;

// 	for (int row = 0; row < board_size; row++)
// 	{
// 		for (int col = 0; col < board_size; col++)
// 		{
// 			if ((start_row == row) && (start_col == col))
// 				knight_square[row][col] = count;
// 			else
// 				knight_square[row][col] = 0;
// 		}
// 	}
// 	count++;
// }

// //Attempts to solve the board by adding knights in valid positions
// void knight::solve_from(knight &tour)
// {
// 	if (tour.is_solved())
// 	{
// 		cout << "Solved!" << endl;
// 		tour.print();
// 		return;
// 	}
// 	else
// 	{
// 		for (int i = 0; i < 8; i++)
//         {
//             if (tour.move((curr_row + x_inc[i]), (curr_col + y_inc[i])))
//             {
//                 tour.insert((curr_row + x_inc[i]), (curr_col + y_inc[i]));
//             }
//             tour.solve_from(tour);
//         }
// 	}
// 	tour.remove(curr_row, curr_col);
// }

// //Checks to see if a move is valid.
// bool knight::move(int row, int col)
// {
// 	if (row < 0 || row >= board_size)
// 		return false;
// 	else if (col < 0 || col >= board_size)
// 		return false;
// 	else if (knight_square[row][col] != 0)
// 		return false;
// 	else
// 		return true;
// }

// //Inserts a knight into position if move is valid then increments the count.
// void knight::insert(int row, int col)
// {
// 	cout << "Insert : " << count << endl;
// 	knight_square[row][col] = count;
// 	curr_row = row;
// 	curr_col = col;
// 	count++;
// }

// //Removes knight
// void knight::remove(int row, int col)
// {
// 	count--;
// 	cout << "Remove : " << count << endl;
// 	for (int rows = 0; rows < board_size; rows++)
// 	{
// 		for (int cols = 0; cols < board_size; cols++)
// 		{
// 			if (knight_square[rows][cols] == (count - 1))
// 			{
// 				curr_row = rows;
// 				curr_col = cols;
// 			}
// 		}
// 	}
	
// }

// void knight::print()
// {
// 	for (int row = 0; row < board_size; row++)
// 	{
// 		for (int col = 0; col < board_size; col++)
// 		{
// 			cout << knight_square[row][col] << " ";
// 		}
// 		cout << endl;
// 	}
// }

// //Checks if board is solved
// bool knight::is_solved()
// {
// 	for (int row = 0; row < board_size; row++)
// 	{
// 		for (int col = 0; col < board_size; col++)
// 		{
// 			if (knight_square[row][col] <= 0)
// 				return false;
// 		}
// 	}
// 	return true;
// }

// int main()
// {
// 	int size;
// 	int start_row, start_col;

// 	cout << "Enter the size of the board: " << endl;
// 	cin >> size;
// 	cout << "Enter the start position for the row: " << endl;
// 	cin >> start_row;
// 	cout << "Enter the start position for the column: " << endl;
// 	cin >> start_col;

// 	knight tour(size, start_row, start_col);
// 	tour.solve_from(tour);
// 	tour.print();
// 	return 0;
// }



////////////////////////aaaaaaaaaaaaaaaaaaaa-
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>

/* MAX_GRID of 8 is a standard keyboard */
#define MAX_GRID 11
const char gHelpNotes[] = 
  "\n\nknights [OPTIONS] [SEARCHPATH]"
  "\nknights crossing program (v1.1, 12Feb12), by chris durso, ref. www.durso.org"
  "\n\nOPTIONS"
  "\n\n-v\n--verbose \tprint more information"
  "\n-g=#\n--grid=#\tuse grid of size # (default 8 for 8x8)."
  " Minimum 5, Maximum %d.  "
  "\n\t\tNote no white spaces!"
  "\n\nSEARCHPATH\n"
  "\nThe optional SEARCHPATH is a sequence of positive numbers not longer than"
  "\ngrid x grid in length, and thier numerical values in the range of 0 to "
  "\ngrid x grid and non repeating. Each number is sequence must be a legal "
  "\nchess knights move from the previous number in the SEARCHPATH."
  "\n\nCOORDINATE SYSTEM"
  "\n\nThe bottom left hand corner is noted as 0 and the increment first"
  "\ngoes up and wraps to the right.  The bottom left is 0, the top"
  "\nleft is grid -1, and the top right square is grid x grid -1.\n\n";

/* GLOBAL VARIABLES */
char gLegalMovesMatrix[MAX_GRID*MAX_GRID*2][8+1];

/* helpful offset to get the current position from gLegalMovesMatrix */
int  gLegalMoveToIndexOff;

/* track where have we been */
char gTally[MAX_GRID*MAX_GRID];

/* positionStack holds current position of ~5E54 different paths  */
char *gPositionStack[MAX_GRID*MAX_GRID];

/* how may current hits in gPositionStack */
int gHit;

/* how big is our grid */
int gGrid;

bool gVerbose;

/* END GLOBALS */
int rank(int i){
  return i/gGrid + 1;
}

int file( int i){
   return i%gGrid + 1;
}

/*
// use a lookup table instead of integer '/' 
//
*/
inline int 
legalMovesToPosition(char* ptr){
  // return (ptr - &(gLegalMovesMatrix[0][0]))/9; 
  return *(ptr + gLegalMoveToIndexOff);
}

int  
printStack(){ 
  assert(gHit && "should never unwind stack below 0th element or first hit");
  for( int i = 0; i < gHit ; i++)
      printf("%d ", legalMovesToPosition(gPositionStack[i]));
  
  printf("%d", *gPositionStack[gHit-1]);
  printf("\n");
  return gHit;
}

void printLegalMoves(){
 
  printf("\ngLegalMoveToIndexOff %d \n", gLegalMoveToIndexOff);
  int i;
  int gridSq = gGrid*gGrid;
  for(i = 0; i < gridSq;i++ ){
    int r = rank(i);
    int f = file(i);
  
    printf("%d (r:%d, f:%d) -> ", i, r, f);
    int moveIndex;
    for( moveIndex = 0; moveIndex < 8; moveIndex++){
      if((char)-1 == gLegalMovesMatrix[i][moveIndex])
	break;
      printf(" %d(%d,%d) ", gLegalMovesMatrix[i][moveIndex]
	     ,rank(gLegalMovesMatrix[i][moveIndex])
	     ,file(gLegalMovesMatrix[i][moveIndex]) );
     }
    printf("\n");
  }
  
  /* print the offsets */
  printf("\n");
  for(i = gridSq; i < 2*gridSq; i++ ){

    printf("%.2d index  ", i - gridSq);
    int col;
    for( col = 0; col < 8; col++){
      printf(" %.2d ", gLegalMovesMatrix[i][col]);
    }
    printf("\n");
  }
  
}

struct intPair{
  int file; 
  int rank;
};

void initLegalMoves(){

  int i;
  struct intPair moves[] = {
    {-1,-2},  /* ( 1 down 2 left  ) */
    {+1,-2},  /* ( 1 up   2 left  ) */
    {-2,-1},  /* ( 2 down 1 left  ) */
    {+2,-1},  /* ( 2 up   1 left  ) */
    {-2,+1},  /* ( 2 down 1 right ) */
    {+2,+1},  /* ( 2 up   1 right ) */
    {-1,+2},  /* ( 1 down 2 right ) */
    {+1,+2},  /* ( 1 up   2 right ) */
    {0,0}     /*  null terminated   */ };
	       
  int gridSq = gGrid*gGrid;
  gLegalMoveToIndexOff = gridSq*9;
  memset(gLegalMovesMatrix, -1, sizeof(gLegalMovesMatrix));
    
  /* for every position define its legal moves */
  for(i = 0; i < gridSq; i++ ){
    int colIndex;
    struct intPair *moveIndex;
    
    for(colIndex = 0,  moveIndex = moves; moveIndex->rank; ++moveIndex ){
      int r,f;
            
      r = rank(i) + moveIndex->rank;
      f = file(i) + moveIndex->file;
      
      if( r > 0 && r <= gGrid && f > 0 && f <= gGrid){
	gLegalMovesMatrix[i][colIndex++] = (r-1)*(gGrid) + (f-1);
      }
    }
    memset((char*)(&gLegalMovesMatrix[i + gridSq][0]), i, 9);
  }
}

int 
initTallyAndPositionStack(char* cur){
  char* first = cur;
  char* end = cur;

  assert(*cur != -1 && "stack must have non zero length");

  while(*end != -1)
    ++end;

  int maxIndex = gGrid*gGrid;
  
  memset(gTally, 0, sizeof(gTally));  // set the tally sheet to totally unexplored  
  gHit = 0;

  if((end - first)  > maxIndex){
    printf("\nIllegal path length ( %d) is too big for %d x %d grid.", int(end - first), gGrid, gGrid);
    return 3; 
  }

  /* enter each of the steps from the initial stack */
  for(; cur < end; ++cur){
    int i;

    if(*cur >= maxIndex){
      printf("\nIllegal path element, %d is too big for %d x %d grid.", int(*cur), gGrid, gGrid);
      return 4;
    }

    if(gTally[*cur] != 0 ){
      printf("\nIllegal, SEARCHPOSITION %d is repeated!", 
	     *cur);
      printf("\n");
      return 1;
    }

    gTally[*cur] = 1;
    gHit++;
   
    /* check all 9 potential prev moves to see if it is possible to get here 
    // from there
    */
    for(i = 0; i < 9; ++i){
      if((cur+1) == end){
	if(!gTally[gLegalMovesMatrix[*cur][i]])
	  break; // last does not repeat a spot
      } else {
	if(gLegalMovesMatrix[*(cur+1)][i] == *cur)
	  break;// inner matches
      }
    }

    if(9 == i){
      printf("\nIllegal, SEARCHPOSITION %d is inaaccesible from %d. ",
	     *(cur+1), *(cur));
      printf("\n");
      return 2;
    }
    
    gPositionStack[cur - first] = &gLegalMovesMatrix[*cur][i];
  }
  

  printf("initial stack: ");
  printStack();
  
  return 0; /* success */
}

int initialize(char *initialStack){
  initLegalMoves();
  return initTallyAndPositionStack(initialStack); 
}


void 
findSequentialSolutions(){
  
  int next = *gPositionStack[gHit - 1];
  unsigned long long miss = 0;
  unsigned long long paths = 0;
  int topSq = gGrid*gGrid -1;
  
  do {
    if(0 == gTally[next]){

      /* a good hit ! */
      gTally[next] = 1;
      gPositionStack[gHit] = gLegalMovesMatrix[next];
      
      if(gVerbose)
	printStack();

      if( topSq == gHit ){
	/* completed the path, print the results */
	printf("\n");
	
	printStack();

	paths++;
	printf("\npath %llu found after %llu many dead ends \n", 
	       paths,  miss );
     
	gHit++;
      } else {
	/* record hit
	// push stack,
	// and calculate next position
	*/
	next = *(gPositionStack[gHit++]);
      }

    } else {
	
      /* been there ! go elsewhwere
      // the current value of 'next' is not a valid place
      */

      while(-1 == *(gPositionStack[gHit-1] + 1) ){
	 gHit--;
	 if(0 == gHit ){
	   printf("\nALL DONE! have exhausted all paths on grid of %d "
		  "starting with %d", 
		  gGrid, legalMovesToPosition(gPositionStack[gHit]));
	   printf("\ntotal paths found %llu with %llu dead ends \n", 
		  paths,  miss );
	   return;
	 }
	 /* erase a position mark */
	 gTally[legalMovesToPosition(gPositionStack[gHit])] = 0;
      }
      
      miss ++;
      /* ok to try next */
      gPositionStack[gHit-1]++;
      next = *(gPositionStack[gHit-1]);
    }
  } while(1);
  
}

/*
// myStrCmp returns match forwarding begin until after "matchStr" 
*/
int myStrCmp( char** begin, const char* matchStr){
  
  int sl = strlen(matchStr);
  if(memcmp(*begin, matchStr, sl))
    return 0;
  *begin += sl;
  
  return 1;
}

/*
// Prints the coordinate grid
*/
void printcoordinategrid(){
  
  for(int i = 0; i < gGrid ; ++i){
    for(int j = gGrid-1; j < gGrid*gGrid; j+= gGrid )
      printf("%*d", 4, j-i);
    printf("\n");
  }
  printf("\n");  
}

int main(int args, char** argv){

  int i, num;
  gGrid = 8;
  gVerbose = false;
  char initialStackFromArg[MAX_GRID*MAX_GRID + 1];
  int  initialStackFromArgCount = 0;
  bool printHelpAndExit = false;
  
  memset((void*)initialStackFromArg, -1, sizeof(initialStackFromArg));
  
  for(++argv, i = 1; i <= (args-1); ++i, argv++){
    char **arg = argv;
    
    if      (myStrCmp(arg, "-v") || myStrCmp(arg, "--verbose")){
      gVerbose = true;
    }else if(myStrCmp(arg, "-g=") || myStrCmp(arg, "--grid=")){
      gGrid = atoi(*arg);
      if( gGrid > MAX_GRID || gGrid < 5 ){
	printf("\nValue for grid size %d out of range of 5-%d, exiting.\n", 
	       gGrid, MAX_GRID);
	return -1;
      }
    }else if(myStrCmp(arg, "-h") || myStrCmp(arg, "--help")){
      printHelpAndExit = true;
    }else if(1 == sscanf(*arg, "%d", &num )){
      if(initialStackFromArgCount == gGrid*gGrid ){
	printf("\nToo many elements in the SEARCHPATH only permitted %d"
	       " for grid of size %d\n", 
	       gGrid*gGrid, gGrid);
	return -3;
      }
      if(num > 127 || num < 0){
	printf("\nInput number %d out of range, negative numbers or those greater than 127 not accepted\n", num);
	return -4;
      }
      initialStackFromArg[initialStackFromArgCount++] = num;
    } else {
      printf("\nillegal option \"%s\", try --help for options\n", *arg);
      return -2;
    }
  }
  
  // default starting point 0 if not supplied on the cmd line
  if(initialStackFromArgCount == 0 )
    initialStackFromArg[0] = 0;

  if(printHelpAndExit){
    printf(gHelpNotes, MAX_GRID);
    printcoordinategrid();
    return 0;
  }

  if( initialize(initialStackFromArg))
    return -1; /* the initial stack is invalid */

  if(gVerbose)
    printLegalMoves();
  
  findSequentialSolutions();

  return 0;
}
