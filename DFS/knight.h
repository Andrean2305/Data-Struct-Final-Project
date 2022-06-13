#pragma once
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;

struct Cell
{
    int x, y;
    vector<Cell> path;
    Cell(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void print()
    {
        cout << "(" << x << ", " << y << ")";

    }
    void printPath()
    {
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++)
        {
            path.at(i).print();
            if (i < path.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
};


void partFive(int knight[2], int target[2]);
bool insideBoard(int x, int y, int size);
void createBoard(int arr[][9]);
bool isTarget(Cell current, int target[2]);
Cell knightShortestPath(int knight[2], int target[2]);
void getAllPaths(queue<Cell>* path, int board[][9], Cell current, int dx[8], int dy[8]);