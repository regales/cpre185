/*-----------------------------------------------------------------------------
-					          SE 185 Lab 07 - The DS4 Equalizer
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Alisala Mwamba
- 	Section: 1
-	NetID: mwambama
-	Date:   10/20/2023
-
-   This file provides the outline for your program
-   Please implement the functions given by the prototypes below and
-   complete the main function to make the program complete.
-   You must implement the functions which are prototyped below exactly
-   as they are requested.
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>



/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.141592653589

/* NO GLOBAL VARIABLES ALLOWED */
// notes: run with ./ds4rd-real.exe -d 054c:09cc -D DS4_USB -t -b -j | ./lab7
//final  ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b -g -j | ./lab07
//  final final ./ds4rd-real.exe -d 054c:09cc -D DS4_USB -t -g -b -j | ./lab7_1



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
int scaleMagForScreen(double gx);
//int scaleMagForScreen(double x);

/*-----------------------------------------------------------------------------
    PRE: -128 <= mag <= 127
    This function scales the joystick value to fit on the screen.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
int scaleJoyForScreen(double rad);

/*----------------------------------------------------------------------------
    PRE: -39 <= number <= 39
    Uses print_chars to graph a number from -39 to 39 on the screen.
    You may assume that the screen is 80 characters wide.
----------------------------------------------------------------------------*/
void graph_line(int num, char use);
/*-----------------------------------------------------------------------------
    PRE: num >= 0
    This function prints the character "use" to the screen "num" times
    This function is the ONLY place printf is allowed to be used
    POST: nothing is returned, but "use" has been printed "num" times
-----------------------------------------------------------------------------*/
void print_chars(int number,char right, char left);


/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main()
{
    double gx, gy, gz;                     /* Values of x, y, and z axis*/    //gyroscope
    int t;                              /* Variable to hold the time value */
    int b_Up, b_Down, b_Left, b_Right;  /* Variables to hold the button statuses */   // buttons, triangle,xbutton, square, then circle 
    int j_LX, j_LY, j_RX, j_RY;         /* Variables to hold the joystick statuses */
    int scaled_pitch, scaled_roll; 	    /* Value of the roll/pitch adjusted to fit screen display */
    int scaled_joy;                     /* Value of joystick adjusted to fit screen display */
    int scaled;
     int rollResult;
     int pitchResult;
     double joyResult;
     bool check1, check2, check3;  // use to toggle between roll,pitch and joystick 
     int timer;  
    /* Put pre-loop preparation code here */
     int i;
     int check =0;
     int toggle;
    do  
    {   
               read_input(&t, &gx, &gy, &gz, &b_Up, &b_Down, &b_Left, &b_Right, &j_LX, &j_LY, &j_RX, &j_RY);      
                    rollResult = scaleMagForScreen(gx);  //left and right, thats x roll                 
                    pitchResult = scaleMagForScreen(gz);   // forward and backward, pitch its z thats  both cannot refer to same thing
                    //printf("the pitch is %d \n", pitchResult);
                    joyResult =  scaleJoyForScreen(j_RX);   //joystick                                             
                        if(b_Up ==1){  //button to be pressed to switch between roll and pitch
                            toggle += 1;
                            while(b_Up==1){
                                read_input(&t, &gx, &gy, &gz, &b_Up, &b_Right, &b_Down, &b_Left, &j_LX, &j_LY, &j_RX, &j_RY);
                            }
                        }
                        if(b_Right == 1){// allow the same button to be pressed in order to switch betweeen roll, pitch and joystick
                            check += 1;
                            while(b_Right==1){
                                read_input(&t, &gx, &gy, &gz, &b_Up, &b_Right, &b_Down, &b_Left, &j_LX, &j_LY, &j_RX, &j_RY);
                            }
                        }
                              if( toggle == 4)  {
                                toggle = 1;
                              } 
                              else if(toggle == 1){
                                graph_line(toggle, rollResult);
                              }
                              else if(toggle == 2){
                                graph_line(toggle, pitchResult);
                              }
                              else if(toggle == 3){ 
                                if(check == 2){
                                    check = 0;
                                }
                                else if (check == 0){
                                    graph_line (3,joyResult); // // for joyStick
                                }
                                else if(check == 1){
                                    graph_line(4,scaleJoyForScreen(j_RY) );
                                }
                              }
                    
         /* Scan a line of input */

        /* Calculate and scale for pitch AND roll AND joystick */

        /* Switch between roll, pitch, and joystick with the up, down, and right button, respectivly */

        /* Output your graph line */

        fflush(stdout);

    } while (b_Left !=1 ); /* Modify to stop when left button is pressed */
         //printf("\n\n Game Ended!\n");
        return 0;
       }

       int read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S,
                int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y )
                {
            scanf("%d, %lf ,%lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d", time, g_x, g_y, g_z, button_T, button_C, button_X, button_S,l_joy_x, l_joy_y, r_joy_x, r_joy_y);
            // if(*button_S== 0){
            //     return 1;
            // }
            // else{
            //     return 0;
            // }
              
                }

      int scaleMagForScreen(double gx){
           if(gx > 1.0){
            gx = 1.0;
           }
           if(gx < -1.0){
             gx = -1.0;
           }
         //  int temp = gx * 39;

        return gx * 39; // if -1*39= -39, left side, if 1 * 39= 39, right side
      }      
         int scaleJoyForScreen(double rad){
            // return j_RX;
         //printf("number is %lf\n",rad);
           if(rad > 127.0){
            rad = 128;
           }
            else if(rad < -128){  // taking off the else statement will not give you the
             rad = -128;
           }
          //printf("number %lf\n",rad);
            return (rad / 128) * 39;  //127/127 = 1 * 39 = 39
   }          
      void graph_line(int num, char use){

           switch(num){
        case 1:
            use = use * -1;
            print_chars(use,'R','L'); // roll
              break;
         case 2:
             use = use * -1;
            print_chars(use,'F','B'); //pitch
             break;
         case 3:
             print_chars(use,'r','l'); //joystick
             break;
          case 4:
              print_chars(use,'f','b');
              break;
           default:
              printf("\n Error \n");
              break;

           }
      }
     
     void print_chars(int number,char right, char left){
    
        if(number > 0){
           for(int i = 0; i < 39; i++){
                printf(" ");
            }
            for( int i= 0; i < number; i++){ 
                 printf("%c",right);
             }
       }
        if(number < 0){
                for(int i = 0; i < number + 39; i++){
                    printf(" ");
            }
            for( int i= 0; i < (number* -1); i++){ 
                 printf("%c",left);
             }
       }
       if(number == 0){
        for(int i = 0; i < 39; i++){
            printf(" ");
        }
        printf("0");
      }
      printf("\n");


     }

