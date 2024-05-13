/*----------------------------------------------------------------------------
-		        SE 185: Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name:		Ryan Aun Shern Chin															 -
- 	Section:	2															 -
-	NetID:		ryanchin														     -
-	Date:		1/31/24															 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>   // Google this header file to learn more! :)

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    double a, b, c;

    /* Put your code after this line */
	printf("a : \n");
	scanf("%lf", &a);
	printf("b : \n");
	scanf("%lf", &b);



    /* This next line will calculate the square root of whatever value is
     * inside the parenthesis and assigns it to the variable filler. */
    c = sqrt( pow(b,2) + pow(a,2) );
	printf("c = %lf\n", c);

    return 0;
}
