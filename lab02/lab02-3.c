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

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int integer_result;
    double decimal_result;

    integer_result = 77 / 5;
    printf("The value of 77/5 is %d, using integer math.\n", integer_result); //changed "%lf" to "%d" because integer_result is a variable of int type

    integer_result = 2 + 3;
    printf("The value of 2+3 is %d.\n", integer_result); // added missing "integer_result" as the argument according to the printf syntax

    decimal_result = 1.0 / 22.0;
    printf("The value 1.0/22.0 is %lf.\n", decimal_result); //changed "%d" to "%lf" beacuse decimal_result is of double type

    return 0;
}
