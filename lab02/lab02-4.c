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
#include <math.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    /* Put your code after this line */
	int a, b;
	a = 6427 + 1725;
	b = (6971 * 3925) - 95;
	printf("6427 + 1725 = %d\n", a);
	printf("(6971 * 3925) - 95 = %d\n", b);
	
	double c, d;
	c = 79 + 12 / 5;
	d = 3640.0 / 107.9;
	printf("79 + 12 / 5 = %0.2lf\n", c);
	printf("3640.0 / 107.9 = %0.2lf\n", d);
	
	int e, f;
	e = (22 / 3) * 3;
	f = 22 / (3 * 3);
	printf("(22 / 3) * 3 = %d\n", e);
	printf("22 / (3 * 3) = %d\n", f);
	
	
	double g, h, i;
	g = 22 / (3 * 3);
	h = 22 / 3 * 3;
	i = (22.0 / 3) * 3.0;
	printf("22 / (3 * 3) = %0.2lf\n", g);
	printf("22 / 3 * 3 = %0.2lf\n", h);
	printf("(22.0 / 3) * 3.0 = %0.2lf\n", i);
	
	int j;
	j = 22.0 / (3 * 3.0);
	printf("22.0 / (3 * 3.0) = %d\n", j);
	
	double k;
	k = 22.0 / 3.0 * 3.0;
	printf("22.0 / 3.0 * 3.0 = %0.2lf\n", k);
	
	double l;
	l = M_PI * pow((23.567 / 2), 2);
	printf("Area of a circle with circumference 23.567 = %0.2lf\n", l);
	// Area of a circle = Pi * (Radius)^2 , where Radius = Circumference/2
	
	double m;
	m = 14 * 0.3048;
	printf("14 feet = %0.2lf meters\n", m);
	// Given that 1 feet = 0.3048 meters, therefore formula should be 14 times 0.3048
	
	double n;
	n = ((76-32) / 1.8);
	printf("76 degrees Fahrenheit = %0.2lf degrees Celsius", n);
	// Given Celsius = (Fahrenheit - 32) /1.8 , sub in value of 76 Fahrenheit into equation as formula
	
    return 0;
}
