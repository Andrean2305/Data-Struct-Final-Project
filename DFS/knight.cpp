#include "Knight.h"

void partFive(int knight[2], int target[2])
{

    Cell foundCell = knightShortestPath(knight, target);

    foundCell.printPath();
}

void createBoard(int arr[][9])
{
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            arr[i][j] = 0;
        }
    }
}

bool insideBoard(int x, int y, int size)
{
    // all four border checks
    if (x >= 1 && x <= size && y >= 1 && y <= size)
    {
        return true;
    }
    return false;
}

bool isTarget(Cell current, int target[2])
{
    if (current.x == target[0] && current.y == target[1])
    {
        return true;
    }
    return false;

}

void getAllPaths(queue<Cell>* path, int board[][9], Cell current, int dx[8], int dy[8])
{
    int x, y;
    for (int i = 0; i < 8; i++)
    {
        // possible position we can reach
        x = current.x + dx[i];
        y = current.y + dy[i];

        // if spot we havent reached yet now can be reached
        // have to check if its in the board or not as it will throw exception
        if (insideBoard(x, y, 8) && board[x][y] == 0) {
            // marks it as reached
            board[x][y] = 1;
            current.x = x;
            current.y = y;
            // add current x,y after processing to cell path so we can track moves
            current.path.push_back(current);
            // adds current cell to path so we can process it later
            path->push(current);
        }
    }
}

Cell knightShortestPath(int knight[2], int target[2])
{
    // knights possible steps.
    int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    // chess board
    int board[9][9];
    createBoard(board);
    // starting pos of the knight marked as visted as we start here
    board[knight[0]][knight[0]] = 1;

    // queue of the cells we have visited
    queue<Cell> path;
    Cell current(knight[0], knight[1]);
    // either knight or target is out of bounds from the start
    if (!insideBoard(knight[0], knight[1], 8) || !insideBoard(target[0], target[1], 8))
    {
        cout << "Outside of the board, Please pick a cell within (1 - 8)" << endl;
        return current;
    }
    // add current cell x,y to cells path (track for itself)
    current.path.push_back(current);
    // add current knight pos to the queue
    path.push(current);
    while (!path.empty())
    {
        // gets current cell and stores it
        current = path.front();
        // removes cell after stored
        path.pop();
        // we have reached our target
        if (isTarget(current, target))
        {
            // returns cells when found so we can print the cell from other function
            cout << endl <<"Spot reached!" << endl;
            return current;

        }
        // goes through all the different ways we can move
        getAllPaths(&path, board, current, dx, dy);
    }
    // if not found returns cell
    return current;
}