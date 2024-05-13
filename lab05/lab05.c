/*----------------------------------------------------------------------------
-		         SE 185: Lab 05 - Conditionals (What's up?)	    	         -
-	Name:			Ryan Aun Shern Chin 														 -
- 	Section:		2														 -
-	NetID:			ryanchin    													     -
-	Date:			2/21/24														 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
double magnitude(double ax, double ay, double az);
int close_to (double tolerance, double point, double value);
int orientation(double gx, double gy, double gz);
int exit_program(int button);
/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc lab05.c -o lab05
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -a -g -b | ./lab05

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int triangle, circle, x_button, square;
    double ax, ay, az, gx, gy, gz;
    int last_orientation = 0;
    int current_orientation = 1;

    while (1)
    {
        scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
              &ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);

        /* printf for observing values scanned in from ds4rd.exe,
         * be sure to comment or remove in final program */
        /*printf("Echoing output: %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d \n",
               ax, ay, az, gx, gy, gz, triangle, circle, x_button, square);*/

        /* It would be wise (mainly save time) if you copy your code to calculate
         * the magnitude from lab03-1.c. You will also need to copy your
         * prototypes and functions to the appropriate sections in this program. */

        //printf("The acceleration's current magnitude is: %lf\n", magnitude(ax, ay, az));
		//printf("\n%d\n", close_to(0.25, 1, 1.35)); //testing close_to
		current_orientation = orientation(gx, gy, gz);
        if ((current_orientation != last_orientation) && (magnitude(ax, ay, az) <= 0.2)) { // magnitude value <= 0.2 so that no repeats in a row
            //printf("Current: %d, Last %d\n", current_orientation, last_orientation); //testing boolean
            if(current_orientation == 1){
                printf("Top\n");
            }
            else if(current_orientation == 2){
                printf("Bottom\n");
            }
            else if(current_orientation == 3){
                printf("Left\n");
            }
            else if(current_orientation == 4){
                printf("Right\n");
            }
            else if(current_orientation == 5){
                printf("Front\n");
            }
            else if(current_orientation == 6){
                printf("Back\n");
            }
            last_orientation = current_orientation;
        }

        if(exit_program(triangle)){
            printf("\nTriangle button pressed .... Shutting down \n");
            break;
        }
        fflush(stdout);
    }

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
double magnitude(double ax, double ay, double az)
{
    return sqrt(pow(ax,2)+pow(ay,2)+pow(az,2));
}
int close_to (double tolerance, double point, double value){
	
	if((value <= (point + tolerance)) && (value >= (point - tolerance))) {
		return 1;
	}
	else{
		return 0;
	}
}

//function to determine which way controller is facing
int orientation (double gx, double gy, double gz){

	if(close_to(.15, 1, gy)){
        return 1; //top
	}
	else if(close_to(.15, -1, gy)){	
        return 2; //bottom
	}
    else if(close_to(.30, -1, gx)){
        return 3; //left
	}
	else if(close_to(.30, 1, gx)){
        return 4; //right
	}
	else if(close_to(.20, -1, gz)){
        return 5; //front
	}
	else if(close_to(.20, 1, gz)){
        return 6; //back
	}
    return 1;
}

//function to exit program
int exit_program(int button){
    if (button == 1){
        return 1;
    }
}