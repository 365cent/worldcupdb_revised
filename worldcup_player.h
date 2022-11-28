/*==============================================================
| Name: worldcup_player.h
| Player code (eg. 0, 1, 2, 3, 4, etc.)
| Each player code must be unique. There is no limit to the number of players but each code will be greater than or equal to 0
| Player name (eg. "John Smith", "Jane Doe", etc.)
| Only names up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
| Player age (eg. 17, 18, 19, 20, etc.)
| Only integers 17-99 are acceptable
| Professional club affiliation (eg. "Manchester City", "Los Angeles FC", "Toronto FC", "AFC Ajax", etc.)
| Only names up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
--------------------------------------------------------------
*/

#ifndef worldCupPlayer
#define worldCupPlayer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DBLBUFSIZE 50

// Define player struct
typedef struct player
{
	int playerCode;							 // a unique identifier for each player
	char playerName[DBLBUFSIZE]; // +1 for null terminator
	int playerAge;							 // Player age is an integer
	char playerClub[DBLBUFSIZE]; // +1 for null terminator
	int teamCode;								 // Team code
	struct player *next;				 // Pointer to next team in linked list
} player;

int worldcup_player(int mode);
int insertPlayer();
int insertP(int playerCode, char playerName[DBLBUFSIZE], int playerAge, char playerClub[DBLBUFSIZE], int teamCode);
int isExist(int teamCode);
int isPlayerExist(int playerCode);
int isPlayerNamed(char playerName[DBLBUFSIZE]);
int searchPlayer(int playerCode);
int updatePlayer();
int deletePlayer(int playerCode);
int printPlayerList();
char *stripName(char name[DBLBUFSIZE]);
player *retrievePlayer(int playerCode);
void playerHelp();
#endif
