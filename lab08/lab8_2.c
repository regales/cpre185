/*-----------------------------------------------------------------------------
-					  		SE 185 Lab 08
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Ryan Aun Shern Chin
- Section: 2
-	NetID: ryanchin
-	Date:  4/2/24
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
/* Mathmatical constants */
#define PI 3.14159

/* 	Screen geometry
    Use ROWS and COLUMNS for the screen height and width (set by system)
    MAXIMUMS */
#define COLUMNS 100
#define ROWS 80

/* 	Character definitions taken from the ASCII table */
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

/*	Number of samples taken to form an moving average for the gyroscope data
    Feel free to tweak this. */
#define NUM_SAMPLES 10

/*-----------------------------------------------------------------------------
-								Static Data
-----------------------------------------------------------------------------*/
/* 2D character array which the maze is mapped into */
char MAZE[COLUMNS][ROWS];

/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*	POST: Generates a random maze structure into MAZE[][]
    You will want to use the rand() function and maybe use the output %100.
    You will have to use the argument to the command line to determine how
    difficult the maze is (how many maze characters are on the screen). */
void generate_maze(int difficulty);

/*	PRE: MAZE[][] has been initialized by generate_maze()
    POST: Draws the maze to the screen */
void draw_maze(void);

/*	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y */
void draw_character(int x, int y, char use);

/*	PRE: -1.0 < mag < 1.0
    POST: Returns tilt magnitude scaled to -1.0 -> 1.0
    You may want to reuse the roll function written in previous labs. */
double calc_roll(double mag);

/* 	Updates the buffer with the new_item and returns the computed
    moving average of the updated buffer */
double m_avg(double buffer[], int avg_size, double new_item);

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
/*	Main - Run with './ds4rd.exe -t -g -b' piped into STDIN */
void main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printw("You must enter the difficulty level on the command line.");
        refresh();
        return;
    }
    else
    {
        /* 	Setup screen for Ncurses
            The initscr functionis used to setup the Ncurses environment
            The refreash function needs to be called to refresh the outputs
            to the screen */
        initscr();
        refresh();

        /* WEEK 2 Generate the Maze */

        int diff;
        diff = atoi(argv[1]);
        generate_maze(diff);
        draw_maze();

        /* Read gyroscope data and fill the buffer before continuing */
        int t, q, w, e, r;
        double x, y, z;
        int maxTime = 700;
        int tempT = 700;
        int yPos = 0;
        int xPos = 50;
        double mAvg = 0;
        double xArray[NUM_SAMPLES];
        int slow = 0;
        int oldy = 0;
        int oldx = 50;
        int win = 0;
        int loseT = 0;
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &x, &y, &z, &q, &w, &e, &r);
            xArray[i] = x;
        }

        /* Event loop */
        do
        {

            /* Read data, update average */
            scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &x, &y, &z, &q, &w, &e, &r);
            loseT = t;
            mAvg = m_avg(xArray, NUM_SAMPLES, x);
            if (mAvg > .2)
            {
                slow++;
                if (slow == 10)
                {
                    draw_character(xPos, yPos, EMPTY_SPACE);
                    xPos--;
                    if (xPos < 100 && xPos > 0)
                    {
                        if (MAZE[xPos][yPos] == WALL)
                        {
                            xPos = oldx;
                        }
                        oldx = xPos;
                        
                    }
                    if (xPos < 0) 
                    {
                        xPos = 0;
                    }
                    else if (xPos > 100)
                    {
                        xPos = 100;
                    }
                    slow = 0;
                }
            }
            else if(mAvg < -.2)
            {
                slow++;
                if (slow == 10)
                {
                    draw_character(xPos, yPos, EMPTY_SPACE);
                    xPos++;
                    if (xPos < 100 && xPos > 0)
                    {
                        if (MAZE[xPos][yPos] == WALL)
                        {
                            xPos = oldx;
                        }
                        oldx = xPos;
                    }
                    if (xPos < 0) 
                    {
                        xPos = 0;
                    }
                    else if (xPos > 100)
                    {
                        xPos = 100;
                    }
                    slow = 0;
                }
            }
            draw_character(xPos, yPos, AVATAR);

            /* Is it time to move?  if so, then move avatar */
            if (t >= tempT + maxTime)
            {
                draw_character(xPos, yPos, EMPTY_SPACE);
                yPos++;
                if (MAZE[xPos][yPos] == WALL)
                {
                    yPos = oldy;
                }
                tempT = t;
                oldy = yPos;
            }
            if (MAZE[xPos + 1][yPos] == WALL && MAZE[xPos - 1][yPos] == WALL &&
                MAZE[xPos][yPos + 1] == WALL)
            {
                win = 1;
                while (t < loseT + 1000)
                {
                    scanf(" %d, %lf, %lf, %lf, %d, %d, %d, %d", &t, &x, &y, &z, &q, &w,
                          &e, &r);
                    draw_character(xPos, yPos, AVATAR);
                }
                break;
            }

        } while (yPos < ROWS); // Change this to end game at right time

        /* Print the win message */

        /* This function is used to cleanup the Ncurses environment.
        Without it, the characters printed to the screen will persist
        even after the progam terminates */
        endwin();
        if (win == 0)
        {
            printf("YOU WIN!\n");
        }
        else
        {
            printf("YOU LOSE!");
        }
    }
}

double m_avg(double buffer[], int avg_size, double new_item)
{

    int k;
    for (k = 0; k < avg_size - 1; k++)
        buffer[k] = buffer[k + 1];

    buffer[k] = new_item;

    double sum = 0.0;

    for (k = 0; k < avg_size; k++)
        sum += buffer[k];

    return sum / avg_size;
}

/* 	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y
    THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
    DO NOT NEED TO CHANGE THIS FUNCTION. */
void draw_character(int x, int y, char use)
{
    mvaddch(y, x, use);
    refresh();
}

void generate_maze(int difficulty)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            int random = rand() % 100;
            if (random < difficulty)
            {
                MAZE[j][i] = WALL;
            }
            else
            {
                MAZE[j][i] = EMPTY_SPACE;
            }
        }
    }
}
void draw_maze(void)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            draw_character(j, i, MAZE[j][i]);
        }
    }
}