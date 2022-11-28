/*==============================================================
| Name: worldcup_team.h
| Team code (eg. 0, 1, 2, 3, 4, etc.)
| Each team code must be unique. There is no limit to the number of teams but each code will be greater than or equal to 0
| Team name (eg. "Australia", "Cameroon", "Canada", "Argentina", "Belgium", etc.)
| Only team names up to 25 characters in length are acceptable (including the null character - So think of this as 24+1). Each team name must be unique
| Group seeding (eg. "A1", "B3", "F2", etc.)
| Only groups A-H and seeds 1-4 are acceptable. (So only A1, A2, A3, A4, B1, B2, ..., H3, H4). Each group seeding must be unique
| Primary kit (uniform) colours (eg. "Red", "Orange", "Yellow", "Green", "Blue", "Indigo", and "Violet")
| Only the values "R", "O", "Y", "G", "B", "I", "V" are acceptable.
*/
#ifndef worldCupTeam
#define worldCupTeam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFSIZE 25

// Define team struct
typedef struct team
{
  int teamCode;           // a unique identifier for each team
  char teamName[BUFSIZE]; // +1 for null terminator
  char groupSeed[3];      // Group seed is a string of 2 characters
  char kitColor;          // Kit color is a single character
  struct team *next;      // Pointer to next team in linked list
} team;

int worldcup_team(int mode);
int insertTeam();
int insert(int teamCode, char teamName[BUFSIZE], char groupSeed[3], char kitColor);
int isExist(int teamCode);
int isNamed(char teamName[BUFSIZE]);
int isSeeded(char groupSeed[3]);
int search(int teamCode);
int updateTeam();
int deleteTeam();
int delete (int teamCode);
int printTeamList();
void printColor(char color);
int playerFromTeam(int teamCode);
int isTeamEmpty(int teamCode);
team *retrieveTeam(int teamCode);
void teamHelp();
#endif
