#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "buffer.h"
#include "newSleep.h"
#include "gameMap.h"
#include "carMove.h"
#include "linkedlist.h"

/* function to move the car */
int carMove(char** border, car* locate, player* post)
{
    int carRow = locate->row, carColumn = locate->column;
    int carHit = 0;
    if (border[carRow][carColumn] == '<')
    {
        carHit = carLeft(border, carRow, carColumn, locate, post);
    }
    else if (border[carRow][carColumn] == '>')
    {
        carHit = carRight(border, carRow, carColumn, locate, post);
    }
    else if (border[carRow][carColumn] == '^')
    {
        carHit = carUp(border, carRow, carColumn, locate, post);
    }
    else if (border[carRow][carColumn] == 'v')
    {
        carHit = carDown(border, carRow, carColumn, locate, post);
    }
    return carHit;
}

int carLeft(char** border, int carRow, int carColumn, car* locate, player* post)
{
    int gameOver = 0;
    if (border[carRow][carColumn - 1] == 'P' && post->road == 1)
    {
        carColumn--;
        locate->row = carRow;
        border[carRow][carColumn] = '<';
        border[carRow][carColumn + 1] = '.';
        gameOver = 1;
    }
    else if (border[carRow][carColumn - 1] == '.')
    {
        carColumn--;
        locate->column = carColumn;
        border[carRow][carColumn] = '<';
        border[carRow][carColumn + 1] = '.';
    }
    else if (border[carRow - 1][carColumn] == '.')
    {
        carRow--;
        locate->row = carRow;
        border[carRow][carColumn] = '^';
        border[carRow + 1][carColumn] = '.';
    }
    else if (border[carRow + 1][carColumn] == '.')
    {
        carRow++;
        locate->row = carRow;
        border[carRow][carColumn] = 'v';
        border[carRow - 1][carColumn] = '.';
    }
    return gameOver;
}

int carRight(char** border, int carRow, int carColumn, car* locate, player* post)
{
    int gameOver = 0;
    if (border[carRow][carColumn + 1] == 'P' && post->road == 1)
    {
        carColumn++;
        locate->column = carColumn;
        border[carRow][carColumn] = '>';
        border[carRow][carColumn - 1] = '.';
        gameOver = 1;
    }
    else if (border[carRow][carColumn + 1] == '.')
    {
        carColumn++;
        locate->column = carColumn;
        border[carRow][carColumn] = '>';
        border[carRow][carColumn - 1] = '.';
    }
    else if (border[carRow - 1][carColumn] == '.')
    {
        carRow--;
        locate->row = carRow;
        locate->direction = '^';
        border[carRow][carColumn] = '^';
        border[carRow + 1][carColumn] = '.';
    }
    else if (border[carRow + 1][carColumn] == '.')
    {
        carRow++;
        locate->row = carRow;
        locate->direction = 'v';
        border[carRow][carColumn] = 'v';
        border[carRow - 1][carColumn] = '.';
    }
    return gameOver;
}

int carUp(char** border, int carRow, int carColumn, car* locate, player* post)
{
    int gameOver = 0;
    if (border[carRow - 1][carColumn] == 'P' && post->road == 1)
    {
        carRow--;
        locate->row = carRow;
        border[carRow][carColumn] = '^';
        border[carRow + 1][carColumn] = '.';
        gameOver = 1;
    }
    else if (border[carRow - 1][carColumn] == '.')
    {
        carRow--;
        locate->row = carRow;
        border[carRow][carColumn] = '^';
        border[carRow + 1][carColumn] = '.';
    }
    else if (border[carRow][carColumn + 1] == '.')
    {
        carColumn++;
        locate->column = carColumn;
        locate->direction = '>';
        border[carRow][carColumn] = '>';
        border[carRow][carColumn - 1] = '.';
    }
    else if (border[carRow][carColumn - 1] == '.')
    {
        carColumn--;
        locate->column = carColumn;
        locate->direction = '<';
        border[carRow][carColumn] = '<';
        border[carRow][carColumn + 1] = '.';
    }
    return gameOver;
}

int carDown(char** border, int carRow, int carColumn, car* locate, player* post)
{
    int gameOver = 0;
    if (border[carRow + 1][carColumn] == 'P' && post->road == 1)
    {
        carRow++;
        locate->row = carRow;
        border[carRow][carColumn] = 'v';
        border[carRow - 1][carColumn] = '.';
        gameOver = 1;
    }
    else if (border[carRow + 1][carColumn] == '.')
    {
        carRow++;
        locate->row = carRow;
        border[carRow][carColumn] = 'v';
        border[carRow - 1][carColumn] = '.';
    }
    else if (border[carRow][carColumn + 1] == '.')
    {
        carColumn++;
        locate->column = carColumn;
        locate->direction = '>';
        border[carRow][carColumn] = '>';
        border[carRow][carColumn - 1] = '.';
    }
    else if (border[carRow][carColumn - 1] == '.')
    {
        carColumn--;
        locate->column = carColumn;
        locate->direction = '<';
        border[carRow][carColumn] = '<';
        border[carRow][carColumn + 1] = '.';
    }
    return gameOver;
}