/*-----------------------------------------------------------------------------
-					          SE 185 Lab 07 - The DS4 Equalizer
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name:   Ryan Aun Shern Chin
- 	Section:    2
-	NetID:  ryanchin
-	Date:   3/20/24
-
-   This file provides the outline for your program
-   Please implement the functions given by the prototypes below and
-   complete the main function to make the program complete.
-   You must implement the functions which are prototyped below exactly
-   as they are requested.
- ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -g -b -j | ./test
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.141592653589

/* NO GLOBAL VARIABLES ALLOWED */


/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------
    PRE: Arguments must point to double variables or int variables as appropriate
    This function scans a line of DS4 data, and returns
    True when left button is pressed
    False Otherwise
    POST: it modifies its arguments to return values read from the input line.
------------------------------------------------------------------------------------*/
int read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S,
                int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y );

/*-----------------------------------------------------------------------------
    PRE: ~(-1.0) <= mag <= ~(1.0)
    This function scales the roll/pitch value to fit on the screen.
    Input should be capped at either -1.0 or 1.0 before the rest of your
    conversion.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
int scaleMagForScreen(double mag);

/*-----------------------------------------------------------------------------
    PRE: -128 <= mag <= 127
    This function scales the joystick value to fit on the screen.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
int scaleJoyForScreen(int rad);

/*----------------------------------------------------------------------------
    PRE: -39 <= number <= 39
    Uses print_chars to graph a number from -39 to 39 on the screen.
    You may assume that the screen is 80 characters wide.
----------------------------------------------------------------------------*/
void graph_line(int number, int switch_case);

/*-----------------------------------------------------------------------------
    PRE: num >= 0
    This function prints the character "use" to the screen "num" times
    This function is the ONLY place printf is allowed to be used
    POST: nothing is returned, but "use" has been printed "num" times
-----------------------------------------------------------------------------*/
void print_chars(int num, char use);

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main()
{
    double x, y, z;                                             /* Values of x, y, and z axis*/
    int t;                                                      /* Variable to hold the time value */
    int b_T, b_C, b_X, b_S;                                     /* Variables to hold the button statuses */
    int j_LX, j_LY, j_RX, j_RY;                                 /* Variables to hold the joystick statuses */
    int scaled_pitch, scaled_roll; 	                            /* Value of the roll/pitch adjusted to fit screen display */
    int scaled_joy;                                             /* Value of joystick adjusted to fit screen display */
    int toggle_button;

    /* Put pre-loop preparation code here */

    do
    {
        /* Scan a line of input */
        read_input(&t,
                &x, &y, &z,
                &b_T, &b_C, &b_X, &b_S,
                &j_LX, &j_LY, &j_RX, &j_RY);

        //printf("\n%d,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d,%d,%d\n", t, x, y, z, b_T, b_C, b_X, b_S, j_LX, j_LY, j_RX, j_RY); // Testing read_input

        /* Calculate and scale for pitch AND roll AND joystick */

        scaled_roll = scaleMagForScreen(x);
        scaled_pitch = scaleMagForScreen(y);

        scaled_joy = scaleJoyForScreen(j_RX);

        /* Switch between roll, pitch, and joystick with the up, down, and right button, respectivly */
        if( b_T == 1 ){
            //printf("roll"); //triangle for roll
			toggle_button = 1;
		}
		if( b_X == 1 ) {
			//printf("pitch"); //cross for pitch
			toggle_button = 2;
		}
        if( b_C == 1 ) {
			//printf("joy"); //circle for joystick
			toggle_button = 3;
		}

        /* Output your graph line */
        if(toggle_button == 1){
			//printf("roll");
			//printf("%d",scaled_roll); //test
			graph_line(scaled_roll, toggle_button);
		}
		if(toggle_button == 2){
			//printf("pitch");
            //printf("%d",scaled_pitch); //test
			graph_line(scaled_pitch, toggle_button);
		}
        if(toggle_button == 3){
			//printf("joy");
            graph_line(scaled_joy, 1);
		}


        fflush(stdout);

    } 
    while (b_S != 1); /* Modify to stop when left button is pressed */

    //printf("Exited Program");

}


/* Function Definitions */
int read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S,
                int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y ){

    scanf("%d,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d,%d,%d", time,
                 g_x,  g_y,  g_z,
                 button_T,  button_C,  button_X,  button_S,
                 l_joy_x,  l_joy_y,  r_joy_x,  r_joy_y);

}

int scaleMagForScreen(double mag){
    if(mag >= 1.0){
        mag = 1.0;
    }
    if(mag <= -1.0){
        mag = -1.0;
    }

    int smfs = asin(mag) * 39 * (2 / PI);
	return smfs;
}

int scaleJoyForScreen(int rad){
    if(rad >= 127){
        rad = 128;
    }
    else if(rad <= -128){  
        rad = -128;
    }
        
    int sjfs = rad * 39 * (1/128.0);
	return sjfs;
}

void print_chars(int num, char use){
	
	for(int i=0; i<fabs(num); i++) {
		printf("%c",use);
    }
}

void graph_line(int number, int switch_case){
	
    switch(switch_case){
        case 1: //roll
            if(number < 0){
                //printf("%d\n",number);
                print_chars(39,' '); 
                print_chars(number,'R');  
                print_chars(1,'\n');
                }
                else if(number > 0){
                //printf("%d\n",number);
                print_chars(40 - number,' ');
                print_chars(number,'L'); 
                print_chars(1,'\n');
                }
                else if(number == 0){
                //printf("%d\n",number);
                print_chars(39,' '); 
                print_chars(1,'0');  
                print_chars(1,'\n'); 
            }
        break;

        case 2: //pitch
            if(number > 0){
                //printf("%d\n",number);
                print_chars(39,' '); 
                print_chars(number,'F');  
                print_chars(1,'\n');
                }
                else if(number < 0){
                //printf("%d\n",number);
                print_chars(40 + number,' ');
                print_chars(number,'B');  
                print_chars(1,'\n');
                }
                else if(number == 0){
                //printf("%d\n",number);
                print_chars(39,' '); 
                print_chars(1,'0');  
                print_chars(1,'\n'); 
            }
        break;

        default:
            printf("\nError\n");
        break;
        
    }
	
}