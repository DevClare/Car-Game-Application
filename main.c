#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main(int argc, char *argv[])
{
    FILE* file;
    int row, column;
    int i, j, k;
    char** border;

    if (argc == 2)  /* to make sure only 2 command line arguments insert by user to proceed */
    {
        file = fopen(argv[1], "r");
        if (file == NULL)   /* display error message when file cannot be open */   
        {
            perror("Error opening the file");
        }
        else
        {
            fscanf(file, "%d %d", &row, &column);   /* get the row and column number from the file*/
            border = (char**) malloc((row + 2) * sizeof(char*));    /* initialize array size */
            for(i = 0; i < row + 2; i++)
            {
                border[i] = (char*) malloc((column + 2) * sizeof(char)); 
            }
            while (fgetc(file) != EOF)  /* check the end of file */
            {
                j = 1;
                while (j <= row)
                {
                    for (k = 1; k <= column; k++)
                    {
                        fscanf(file, "%c ", &border[j][k]);  /* initialize the value inside map array */
                    }
                    j++;
                }
            }
            
            map(border, row, column);   /* call map function to set the game map */
            fclose(file);
        }
        for (k = 0; k < row + 2; k++)   
        {
            free(border[k]);
        }
        free(border);
    }

    else if (argc < 2)  /* print error message when command line arguments insert less than 2 */
    {
        printf("Please enter the file name.\n");
        printf("usage: ./traffic <fileName>\n");
    }

    else    /* print error message when command line arguments insert more than 2 */
    {
        printf ("Please only enter the file name.\n");
        printf("usage: ./traffic <fileName>\n");
    }

    return 0;
}