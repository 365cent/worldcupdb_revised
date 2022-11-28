/*==============================================================
| Name: worldCupDB.c
| The 2211 World Cup is fast approaching. Your work on building worldCupDB.c (Assignment 4) was a great start but it's time to build version 2.0. The old version was missing a few important features:
| You need to keep track of an arbitrary number of teams, not just the 32 who qualified for the tournament
| There is no way to delete teams
| You need to keep a database of players as well
| The program is a little large. It's time to break it up into individual files
| Usage: ./worldCupDB [debug] (then follow the instructions)
| Desciption of parameters:
|   mode: 0 for normal mode, 1 for debug mode
|   quit: whether to quit the program
|   command: the command entered by the user
--------------------------------------------------------------
*/

#include "worldCupDB.h"

// Function prototypes
int debug_mode(int argc, char *argv[]);
void help();

// Main function
int main(int argc, char *argv[])
{
	int mode = 0, quit = 0;
	char command;
	mode = debug_mode(argc, argv);
	// Greeting
	printf("******************\n* 2211 World Cup *\n******************\n");
	while (!quit)
	{
		printf("Enter operation code: ");
		if (scanf(" %c", &command) != 1)
		{
			while (getchar() != '\n')
				;
			printf("Invalid command");
		}
		else
		{
			while (getchar() != '\n')
				;
#ifdef DEBUG
			printf("Command: %c", command);
#endif
			// Convert to uppercase, and run the corresponding function
			switch (toupper(command))
			{
			case 'T':
				worldcup_team(mode);
				break;
			case 'P':
				worldcup_player(mode);
				break;
			case 'H':
				help();
				break;
			case 'Q':
				// Quit
				printf("\nThanks for using World Cup DBMS!\n");
				quit = 1;
				break;
			default:
				// Catch invalid input
				printf("Invalid operation code.");
				help();
				break;
			}
		}
	}
	return 0;
}

// Function to check if debug mode is enabled
int debug_mode(int argc, char *argv[])
{
	if (argc != 1 && strcmp(argv[1], "debug") == 0)
	{
		printf("Debug mode enabled\n");
#ifndef DEBUG
#define DEBUG
#endif
		return 1;
	}
	else
	{
#ifdef DEBUG
#undef DEBUG
#endif
		return 0;
	}
}

// Function to print help
void help()
{
	printf("Here is what I can help you with: \n\
t - Control teams\n\
p - Control players\n\
h - Help\n\
q - Quit\n\
If you need more help with control teams or control players, \n\
press \"t\" or \"p\" then press \"h\".\n");
	return;
}
