/*----------------------------------------------------------------------------
-		    SE 185: Lab 03 - Introduction to the DS4 and Functions	    	 -
-	Name:			Ryan Aun Shern Chin														 -
- 	Section:		2														 -
-	NetID:			ryanchin													     -
-	Date:			2/7/24														 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/

int add(int triangle, int circle, int cross, int square);
/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc lab03-2.c -o lab03-2
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -b | ./lab03-2

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	
int triangle, circle, cross, square;

    while (1)
    {
		scanf("%d, %d, %d, %d", &triangle, &circle, &cross, &square);
		
		printf("%d\n", add(triangle, circle, cross, square));
    }

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */

int add(int triangle, int circle, int cross, int square) {
	
	return triangle + circle + cross + square;
}