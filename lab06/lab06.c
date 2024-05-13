/*----------------------------------------------------------------------------
-                           SE 185: Lab 06 - Bop-It!                         -
- Name:       Ryan Aun Shern Chin                                                                -
- Section:    2                                                                -
- NetID:      ryanchin                                                                -
- Date:       2/28/24                                                                -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-                                Includes                                    -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------------
- Prototypes -
----------------------------------------------------------------------------*/
int gameButton();

/*----------------------------------------------------------------------------
- Notes -
-----------------------------------------------------------------------------*/
// Compile with gcc lab06.c -o lab06
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -b | ./lab06


/*----------------------------------------------------------------------------
- Implementation
-
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int t;
    int triangle = 0;
    int circle = 0;
    int cross = 0;
    int square = 0;
    int rounds = 1;
    int randNum;
    int roundCount = 0;
    int timer = 2500;
    int currentTime;

    srand(time(NULL)); /* This will ensure a random game each time. */
    printf("This is a Bop-It Game!\n");
    printf("Please press the Circle Button to begin!\n");

    while (triangle == 0 && circle == 0 && cross == 0 && square == 0)
    {
        scanf("%d,%d,%d,%d,%d", &t, &triangle, &circle, &cross, &square);
        if(circle) break;
    }

    while (rounds)
    {

        currentTime = t;

        int randNum = gameButton();

        while (currentTime + 260 > t) //delay after scanning in first input
        {
            scanf("%d,%d,%d,%d,%d", &t, &triangle, &circle, &cross, &square);
        }

        printf("You have %d miliseconds to respond!\n", timer);

        currentTime = t;

        while (currentTime + timer >= t)
        {

            scanf("%d,%d,%d,%d,%d", &t, &triangle, &circle, &cross, &square);

            if (!((triangle + circle + cross + square) == 0))
            {
                if((randNum == 1 && triangle == 1) || (randNum == 2 && circle == 1) || (randNum == 3 && cross == 1) || (randNum == 4 && square == 1))
                {
                    timer -= 100;
                    roundCount++;
                    break;
                }
                else
                {
                    printf("\nWrong Button! :(\nYou lose!\n");
                    rounds = 0;
                    break;
                }
            }
        }
        if (currentTime + timer < t)
        {
            printf("\nYou ran out of time. :(\nThanks for playing!\n");
            break;
        }
    }

    printf("You made it through %d rounds!\n", roundCount);

    return 0;
}


/* Put your functions here, and be sure to put prototypes above. */
int gameButton() {
    int randButton = rand() % 4 + 1;
    switch (randButton) {
        case 1:
            printf("\nPress the Triangle button\n");
            break;
        case 2:
            printf("\nPress the Circle button\n");
            break;
        case 3:
            printf("\nPress the Cross button\n");
            break;
        case 4:
            printf("\nPress the Square button\n");
            break;
    }

    return randButton;
}