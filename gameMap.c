#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "buffer.h"
#include "newSleep.h"
#include "gameMap.h"
#include "carMove.h"
#include "linkedlist.h"

void map(char** border, int rowNum, int colNum) /* function to set the game */
{
    player* position = (player*) malloc(PLAYER_SIZE * sizeof(player)); /* initializing player struct */
    car* locate = (car*) malloc(CAR_SIZE * sizeof(car));    /* initializing car struct */
    int i, j, k, l;
    for (i = 0; i <= rowNum + 1; i++) /* setting the game border*/
    {
        for (j = 0; j <= colNum + 1; j++)
        {
            border[0][j] = '*';  /* setting top frame of the game */
            border[i][0] = '*';  /* setting left frame of the game */
            border[i][colNum + 1] = '*'; /* setting right frame of the game */  
            border[rowNum + 1][j] = '*'; /* setting bottom frame of the game */
        }
    }
    k = 1;
    while (k <= rowNum + 1)
    {
        for (l = 1; l <= colNum + 1; l++)   /* initalize game with value from file */
        {
            if (border[k][l] == '0')    /* 0 for empty space */
            {
                border[k][l] = ' ';
            }
            else if (border[k][l] == '1')   /* 1 for road */   
            {
                border[k][l] = '.';
            }
            else if (border[k][l] == '2')   /* 2 for car */  
            {
                border[k][l] = '>';
                locate->row = k;    /* store car row, column  and direction into car struct */
                locate->column = l;
                locate->direction = '>';
            } 
            else if (border[k][l] == '3')   /* 3 for player */
            {
                border[k][l] = 'P';
                position->curRow = k;   /* store player current row and column into player struct */
                position->curCol = l;
                position->road = 0;
            }
            else if (border[k][l] == '4')   /* 4 for the goal */
            {
                border[k][l] = 'G';
            }
        }
        k++;
    }
    game(border, rowNum, colNum, position, locate);   /*calling printScreen function to proceed with user input */
    free(locate);
    free(position);
    
}

/* function to display and run the game */
void game(char** border, int rowNum, int colNum, player* position, car* locate)
{
    LinkedList* pList  = createLinkedList();    /* initialize linked list for player */
    LinkedList* cList  = createLinkedList();    /* initialize linked list for car */

    int i, j, gameOver = 0, gameState = 0;
    char command;
    do
    {
        system("clear");    /* clear the screen before print out the game */
        for (i = 0; i <= rowNum + 1; i++)
        {
            for (j = 0; j <= colNum + 1; j++)
            {
                printf("%c", border[i][j]); /* print out the game map */
            }
            printf("\n");
        }
        printf("Press w to move up\n");
        printf("Press s to move down\n");
        printf("Press a to move left\n");
        printf("Press d to move right\n");
        printf("Press u to undo\n");

        disableBuffer(); /* to allow program to accept user input without pressing enter*/
        scanf("%c", &command);
        enableBuffer();

        switch(command)
        {
            case 'w':
                gameOver = moveUp(border, rowNum, position, locate, pList, cList); 
                gameState = 1;  /* game state 1 for winning the game */
                if (gameOver == 0)  /* only continue if player has not win the game */
                {
                    insertLast(cList, carNode(locate)); /* insert car struct to the linked list node */
                    gameOver = carMove(border, locate, position);
                    gameState = 2;  /* game state 2 for losing the game */
                }
                break;
            case 's':
                gameOver = moveDown(border, rowNum, position, locate, pList, cList);
                gameState = 1;  /* game state 1 for winning the game */
                if (gameOver == 0)  /* only continue if player has not win the game */
                {
                    insertLast(cList, carNode(locate)); /* insert car struct to the linked list node */
                    gameOver = carMove(border, locate, position);
                    gameState = 2;  /* game state 2 for losing the game */
                }
                break;
            case 'a':
                gameOver = moveLeft(border, colNum, position, locate, pList, cList);
                gameState = 1;  /* game state 1 for winning the game */
                if (gameOver == 0)  /* only continue if player has not win the game */
                {
                    insertLast(cList, carNode(locate)); /* insert car struct to the linked list node */
                    gameOver = carMove(border, locate, position);
                    gameState = 2;  /* game state 2 for losing the game */
                }
                break;
            case 'd':
                gameOver = moveRight(border, colNum, position, locate, pList, cList);
                gameState = 1;  /* game state 1 for winning the game */
                if (gameOver == 0)  /* only continue if player has not win the game */
                {
                    insertLast(cList, carNode(locate)); /* insert car struct to the linked list node */
                    gameOver = carMove(border, locate, position);
                    gameState = 2;  /* game state 2 for losing the game */
                }
                break;
            case 'u':
                if (cList->head != NULL || pList->head != NULL) /* only continue if player has move previously */
                {
                    undo(border, rowNum, colNum, position, locate, pList, cList);
                }
                else
                {
                    printf("\nNo undo movement, Player is in starting position.\n");   /* error message when there is no undo movement */
                    newSleep(0.3); /* to show message before continuing the game */
                }
                break;
            default:    /* for other input that is not valid */
                printf("\nInvalid key! Please enter w, s, a, d or u only.\n");
                newSleep(0.3); /* call function to pause the program to display message before continue */
                break;
        } 
    } while(gameOver != 1); /* looping through game while player not reach goal or hit a car*/  
    
    finalPrint(border, rowNum, colNum, gameState); /* finalPrint function, to display game map after game end */
    freeLinkedList(pList, &freeStruct);
    freeLinkedList(cList, &freeStruct);
    free(playerNode(position));
    free(carNode(locate));
}

/*function to proceed when player moving up*/
int moveUp(char** border, int totalRow, player* post, car* locate, LinkedList* pList, LinkedList* cList)   
{
    int gameEnd = 0;
    int rowPlayer = post->curRow, colPlayer = post->curCol; /* initialize player position */
    if (rowPlayer >= 2 && rowPlayer <= totalRow)    /* border guard */
    {
        post->pRow = rowPlayer; /* store previous row and column of player */
        post->pCol = colPlayer;

        if (post->road == 1)    /* check if previously player step on road */
        {
            border[rowPlayer][colPlayer] = '.';
            post->road = 0;
        }
        else if (post->road != 1)
        {
            border[rowPlayer][colPlayer] = ' ';
            post->road = 0;
        }

        if (border[rowPlayer - 1][colPlayer] == 'G')  /* player reach the goal */  
        {
            gameEnd = 1;
        }
        /* condition for jump over car */
        else if (border[rowPlayer - 1][colPlayer] == '>' || border[rowPlayer - 1][colPlayer] == '<' || border[rowPlayer - 1][colPlayer] == '^' || border[rowPlayer - 1][colPlayer] == 'v')
        {
            insertLast(cList, carNode(locate));
            carMove(border, locate, post);  
            post->road = 1;
            gameEnd = 2;
        }
        else if (border[rowPlayer - 1][colPlayer] == ' ') 
        {
            gameEnd = 0;
        }
        else if (border[rowPlayer - 1][colPlayer] == '.') 
        {
            post->road = 1; /* store 1 when player step on the road */
            gameEnd = 0;
        }
        rowPlayer--;
        post->curRow = rowPlayer;   /* store new row of player */
        border[rowPlayer][colPlayer] = 'P'; /* set new position of player */
        insertLast(pList, playerNode(post));    /* add the new position to the linked list */
    }
    else
    {
        gameEnd = 0;
    }
    return gameEnd;
}

/*function to proceed when player moving down*/
int moveDown(char** border, int totalRow, player* post, car* locate, LinkedList* pList, LinkedList* cList)
{
    int gameEnd = 0;
    int rowPlayer = post->curRow, colPlayer = post->curCol;/* initialize player position */
    if (rowPlayer >= 1 && rowPlayer < totalRow) /* border guard */
    {
        post->pRow = rowPlayer; /* store previous row and column of player */
        post->pCol = colPlayer;
        if (post->road == 1) /* check if previously player step on road */
        {
            border[rowPlayer][colPlayer] = '.';
            post->road = 0;
        }
        else if (post->road != 1)
        {
            border[rowPlayer][colPlayer] = ' ';
            post->road = 0;
        }

        if (border[rowPlayer + 1][colPlayer] == 'G')    /* player reach the goal */  
        { 
            gameEnd = 1;
        }
        /* condition for jump over car */
        else if (border[rowPlayer + 1][colPlayer] == '>' || border[rowPlayer + 1][colPlayer] == '<' || border[rowPlayer + 1][colPlayer] == 'v' || border[rowPlayer + 1][colPlayer] == '^')
        {
            insertLast(cList, carNode(locate));
            carMove(border, locate, post);
            post->road = 1;
            gameEnd = 2;
        }
        else if (border[rowPlayer + 1][colPlayer] == ' ')
        {
            gameEnd = 0;
        }
        else if (border[rowPlayer + 1][colPlayer] == '.')
        {
            post->road = 1; /* store 1 when player step on the road */
            gameEnd = 0;
        }
        rowPlayer++;
        post->curRow = rowPlayer; /* store new row of player */
        border[rowPlayer][colPlayer] = 'P'; /* set new position of player */
        insertLast(pList, playerNode(post));    /* add the new position to the linked list */
    }
    else
    {
        gameEnd = 0;
    }
    return gameEnd;
}

/* function to proceed when player moving to the left */
int moveLeft(char** border, int totalCol, player* post, car* locate, LinkedList* pList, LinkedList* cList)
{
    int gameEnd = 0;
    int rowPlayer = post->curRow, colPlayer = post->curCol; /* initialize player position */
    if (colPlayer >= 2 && colPlayer <= totalCol) /* border guard */ 
    {
        post->pRow = rowPlayer; /* store previous row and column of player */
        post->pCol = colPlayer;

        if (post->road == 1)    /* check if previously player step on road */
        {
            border[rowPlayer][colPlayer] = '.';
            post->road = 0;
        }
        else if (post->road != 1)
        {
            border[rowPlayer][colPlayer] = ' ';
            post->road = 0;
        }

        if (border[rowPlayer][colPlayer - 1] == 'G')    /* player reach the goal */
        {
            gameEnd = 1;   
        }
        /* condition for jump over car */
        else if (border[rowPlayer][colPlayer - 1] == '>' || border[rowPlayer][colPlayer - 1] == '<' || border[rowPlayer][colPlayer - 1] == '^' || border[rowPlayer][colPlayer - 1] == 'v')
        {
            insertLast(cList, carNode(locate));
            carMove(border, locate, post);
            post->road = 1;
            gameEnd = 2;
        }
        else if (border[rowPlayer][colPlayer - 1] == ' ')
        {
            gameEnd = 0;
        }
        else if (border[rowPlayer][colPlayer - 1] == '.')
        {
            post->road = 1; /* store 1 when player step on the road */
            gameEnd = 0;
        }
        colPlayer--;
        post->curCol = colPlayer;   /* store new column of player */
        border[rowPlayer][colPlayer] = 'P'; /* set new position of player */
        insertLast(pList, playerNode(post));    /* add the new position to the linked list */
    }
    else
    {
        gameEnd = 0;
    }
    return gameEnd;
}

/* function to proceed when player moving to the right */
int moveRight(char** border, int totalCol, player* post, car* locate, LinkedList* pList, LinkedList* cList)
{
    int gameEnd = 0;
    int rowPlayer = post->curRow, colPlayer = post->curCol; /* initialize player position */
    if (colPlayer >= 1 && colPlayer < totalCol) /* border guard */ 
    {
        post->pRow = rowPlayer; /* store previous row and column of player */
        post->pCol = colPlayer;
        if (post->road == 1)    /* check if previously player step on road */
        {
            border[rowPlayer][colPlayer] = '.';
            post->road = 0;
        }
        else if (post->road != 1)
        {
            border[rowPlayer][colPlayer] = ' ';
            post->road = 0;
        }

        if (border[rowPlayer][colPlayer + 1] == 'G')    /* player reach the goal */
        {
            gameEnd = 1;
        }
        /* condition for jump over car */
        else if (border[rowPlayer][colPlayer + 1] == '<' || border[rowPlayer][colPlayer + 1] == '>' || border[rowPlayer][colPlayer + 1] == '^' || border[rowPlayer][colPlayer + 1] == 'v')
        {
            insertLast(cList, carNode(locate));
            carMove(border, locate, post);
            post->road = 1;
            gameEnd = 2;   
        }
        else if (border[rowPlayer][colPlayer + 1] == ' ') 
        { 
            gameEnd = 0;
        }
        else if (border[rowPlayer][colPlayer + 1] == '.')
        {
            post->road = 1; /* store 1 when player step on the road */
            gameEnd = 0;
        }
        colPlayer++;
        post->curCol = colPlayer;   /* store new column of player */
        border[rowPlayer][colPlayer] = 'P'; /* set new position of player */
        insertLast(pList, playerNode(post));    /* add the new position to the linked list */
    }
    else
    {
        gameEnd = 0;
    }
    return gameEnd;
}

/* function to proceed when player undo*/
void undo(char** border, int totalRow, int totalCol, player* post, car* locate, LinkedList* pList, LinkedList* cList)
{
    player* pData = (player*) removeLast(pList); /* get player previous struct*/
    car* cData = (car*) removeLast(cList);  /* get car previous struct */
    int rowPlayer = post->curRow, colPlayer = post->curCol;
    int prevRow = pData->pRow, prevCol = pData->pCol, currentRow = pData->curRow, currentCol= pData->curCol, road = pData->road;
    char carDirection = cData->direction;
    int carRow = cData->row, carColumn = cData->column;

    border[locate->row][locate->column] = '.';  /* set the road when car movement is undo */

    /* set player and car struct after the movement is undo */
    locate->row = carRow;
    locate->column = carColumn;
    locate->direction = carDirection;
    post->curRow = prevRow;
    post->curCol = prevCol;
    post->road = road;
    
    /* border guard */
    if (colPlayer >= 1 && colPlayer <= totalCol && rowPlayer >= 1 && rowPlayer <= totalRow)
    {
        border[prevRow][prevCol] = 'P'; /* undo player movement */
        if(road == 1) /* check if road exist */
        {
            border[currentRow][currentCol] = '.';
        }
        else if (road == 0)
        {
            border[currentRow][currentCol] = ' ';
        }

        border[carRow][carColumn] = carDirection; /* undo car movement */
    }
}

/* function to print out the game after the game end */
void finalPrint(char** border, int rowNum, int colNum, int gameStatus) 
{
    int i, j;
    system("clear");    /*clear the screen before print out the game*/
    for (i = 0; i <= rowNum + 1; i++)
    {
        for (j = 0; j <= colNum + 1; j++)
        {
            printf("%c", border[i][j]);
        }
        printf("\n");
    }
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");   
    if (gameStatus == 1)    /* to check if player win or lose the game, gameStatus 1 for winning the game, 2 for losing the game*/
    {
        printf("\nYou Win!\n");
    }
    else
    {
        printf("\nYou Hit a car! You Lose!\n");
    }
}