// Lab 09 DS4Talker Skeleton Code

// Ryan Aun Shern Chin | Lab Section: 2 | NetId: ryanchin | Date: 4/10/24

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#define WORDLENGTH 11 	/*Maximum length for a word*/
#define MAXWORDS 100  	/*Maximum words in DS4 Talker*/
#define DEBUGM 0	 	/*Set this to 0 to disable debug output*/

// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char *WL[MAXWORDS], char *file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char *str);

// gcc lab9.c -o test -lncurses
// ./ds4rd.exe -d 054c:09cc -D DS4_USB -t -b -bd -bt | ./test wordslist.txt

int main(int argc, char *argv[])
{
	char *wordlist[MAXWORDS];
	int wordcount = read_words(wordlist, argv[1]);
	int i; 

	// Word Table Variables
	int amount = 0;				    
	char space[50];

	// Initializing DS4 Variables
	int t, triangle, circle, x_button, square, right_joy_down, left_joy_down, options, share, R2, L2, R1, L1, d_up, d_left, d_down, d_right;

	
	// Cursor '*' Movement Variables
	int  down = 0;				/* Represents the imaginary "y-position" of the cursor in the word table's rows*/
	int  right = 0;				/* Represents the imaginary "x-position" of the cursor in the word table's columns*/
	int n_time = 200;			/* Variable to implement a delay*/

	// Sentence Logic Variables
	int n = 0; 					/* Represents the current index in the word list*/
	int length;					/* Represents the length of the word*/
	int place = 0;				/* Keeps track of the place already used for printed sentence*/
	int track = 0;				/* Element for data array to keep track of which data to use*/
	int data[100];				/* Array to store the history of the outputted sentence for clear and undo function*/

	// Initialize ncurses
	initscr();
	
	

	if (DEBUGM)
	{
		printf("Read %d words from %s \n", wordcount, argv[1]);
		for (i = 0; i < wordcount; i++)
		{
			printf("%s,", wordlist[i]);
		}
		printf("\n");
	}

	// Most of your code goes here. Do not forget to include the ncurses library

	// Word Table for user to choose from
	
	strcpy(wordlist[0],"the");
	
	for(int i = 0; i < 5; i++){   
		for(int j = 0; j < 15; j++){

			mvprintw(j,i*12,"%s",wordlist[amount]);
			amount++;
			refresh();
		}
	}

	do{
		
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", 
				&t, &triangle, &circle, &x_button, &square, &right_joy_down, &left_joy_down, &options, &share, &R2, &L2, &R1, &L2, &d_up, &d_left, &d_down, &d_right);

		// Cursor '*' Movement Logic
		if(t >= n_time){
			
			if(d_right == 1 && right < 4){ 							// Ensures that the movement to the right does not exceed the maximum number of 5 imaginary columns of the word table (0 to 4).
				mvprintw(down, 5 + (13 * right), "%c", ' ');		// (13 * right) identifies each word's corresponding X-Position in the terminal output for each imaginary word table column 
				right++;											// '+5' creates a buffer of 5 positions from the word to print the cursor (Blank Space for now as placeholder)
				n += 15; 											
				n_time = t + 200; 									// Action not repeated immediately (delay)
			}
			
			if(d_left == 1 && right > 0){
				mvprintw(down, 5 + (13 * right), "%c", ' ');
				right--;											// --right going left, ++right going right to the next imaginary column in the word table
				n -= 15;											// 'n' used for identifiying which word cursor is pointing towards later in an array
				n_time = t + 200;
			}
			
			if(d_down == 1 && down < 14){							// Ensures that the movement downwards does not exceed the maximum number of 15 imaginary rows of the word table(0 to 14).
				mvprintw(down ,5 + (13 * right), "%c", ' ');
				down++;												// --down going up, ++down going down to the next imaginary row in the word table
				n++;
				n_time = t + 200;
			}
			
			if(d_up == 1 && down > 0){
				mvprintw(down, 5 + (13 * right), "%c", ' ');
				down--;
				n--;
				n_time = t + 200;
			}
			
			
			// Append a space to the current sentence followed by the selected word. (Triangle)
			if(triangle == 1){
				mvprintw(20, place, " %s", wordlist[n]);			// n identified previously to indicate which word cursor is pointing to
				length = 1 + strlen(wordlist[n]);					// +1 to append a space
				place += length;
				track++;
				data[track] = length;
				n_time = t + 200;
				
			}
			
// Describe how you keep track of the word selected on the screen and how this interfaces with the DualShock 4. Is the interface reasonable?

// The 'track' variable identifies each selected word in the sentence from the word table utilizing it as an element in the array called 'data',that serves as a memory
// storage location for the outputted sentence. For each word that is outputted as a sentence, it is assigned to a specific location on the 'data[track]' array.
// 'But before this could work, 'n' is implemented previously to indicate which word the cursor controlled by the user is pointer towards to. This interfaces with the DS4
// where 'n''s value would change according to the user's input of either left, right, up or down. The changing of 'n' value is a representation of the cursor's location on
// terminal in the word list table. So, n will be added to 15 when right is pressed (since it is jumping about 15 position to reach the next column to the right) and vice 
// versa it is subtracted from 15 when left is pressed. When up is pressed, n will be decremented and down is pressed, n will be incremented. This value of n is then later called
// when identifiying which word is supposed to be printed where the program now knows the value of n is representing which word is the user trying to print. 

// This later is used when utilizing a variable called length to store the length of the selected word which is later used in another variable called place where place is
// kept on added by length to keep track of the printed sentence so that no words are printed overlapping each other when square or the triangle button is pressed by the user
// The same logic is used when undoing using cross but rather doing it backwards. In total deletion of the sentence logic using the downwards pressing of the joystick, place and track can be set to 0 as a "reset" procedure.
// Therefore this interface is reasonable.

// n location (visualization)
// 0  | 15
// 1  | 16
// 2  | 17

			// Append the word but without adding a space. (Square)
			if(square == 1){        
				mvprintw(20, place, "%s", wordlist[n]);
				length = strlen(wordlist[n]);				// length = length of current selected word
				place += length;							// Identifies the new 'place' or new total amount of word length is already printed on the sentence, so no overlapping of words printed
				                                            // It won't utilize this "new value of place" yet because the function that prints the word comes before it, which uses the previously known value of place (the total space before new word is printed)
															// So if this section of the code occurs again, the program calls the previously updated value of place and starts printing from that location in the sentence.
				
				track++;									// Keeping track of word selected
				data[track] = length;
				n_time = t + 200;
			}
			
			//Starting an entire new sentence. (Joystick press down)
			if( right_joy_down == 1 || left_joy_down == 1){      
				mvprintw(20, 0, "                                                 ", wordlist);
				place = 0;									// Reseting place and track to 0 (starts printing from the beginning again)
				track = 0;
			}

			// 'Undo' feature (Cross)
			if(x_button == 1){
				place -= length;
				track--;
				length = data[track];
				if(place < 0){
					place = 0;
				}
				mvprintw(20, place, "           ", wordlist);
				n_time = t + 200;
			}
		}

		// Cursor '*' Printing
		mvprintw(down, (5 + (13 * right)), "%c", '*');

		refresh();
	
	} while(1); 


	// Refresh the screen to display changes
	refresh();

	// End ncurses
	endwin();

	return 0;
}

// DO NOT MODIFY THIS FUNCTION!
void trimws(char *str)
{
	int length = strlen(str);
	int x;
	if (length == 0)
		return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0))
	{
		str[x] = '\0';
		x -= 1;
	}
}

// DO NOT MODIFY THIS FUNCTION!
int read_words(char *WL[MAXWORDS], char *file_name)
{
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE *fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL)
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}

