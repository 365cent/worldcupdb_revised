/*==============================================================
| Name: worldcup_player.c
| Description of parameters:
|   headP: the header of the linked list
|   quit: whether to return to the main menu
|   command: the command entered by the user
|   playerCode: a unique identifier for each player
|   playerName: the name of the player
|   playerAge: the age of the player
|   playerClub: the club of the player
|   curr: the current player pointer in the linked list
|   prev: the previous player pointer in the linked list
|   next: the next player pointer in the linked list
|   newPlayer: the new player instance
|   stripedPlayerName: the striped player name up to 21 characters
|   stripedPlayerClub: the striped player club up to 21 characters
|   empty: whether the linked list is empty
|   updated: whether the player is updated
|   teamCode: the team code of the player
---------------------------------------------------------------
*/

#include "worldcup_player.h"

player *headP = NULL;

int worldcup_player(int mode)
{
	int playerCode, quit = 0;
	char command;
	if (mode == 1)
	{
#ifndef DEBUG
#define DEBUG
#endif
		printf("Hello from worldcup_player\n");
	}
	while (!quit)
	{
		printf("[Player]Enter operation code: ");
		if (scanf(" %c", &command) != 1)
		{
			printf("Invalid command");
		}
		else
		{
			while (getchar() != '\n')
				;
			switch (toupper(command))
			{
			case 'I':
				insertPlayer();
				break;
			case 'S':
				printf("Enter player code: ");
				if (scanf("%d", &playerCode) != 1 || playerCode < 0)
				{
					printf("Invalid player code");
				}
				else
				{
					if (!searchPlayer(playerCode))
					{
						printf("Player not found. Use \"i\" to insert a player.\n");
					}
				}
				break;
			case 'U':
				updatePlayer();
				break;
			case 'D':
				printf("Enter player code: ");
				if (scanf("%d", &playerCode) != 1 || playerCode < 0)
				{
					printf("Invalid player code. Please try again.\n");
				}
				else
				{
					if (!retrievePlayer(playerCode))
					{
						printf("Player not found. Use \"i\" to insert a player.\n");
					}
					else
					{
						printf("You are about to delete player %d[%s]. Are you sure? (y/n): ", playerCode, retrievePlayer(playerCode)->playerName);
						if (scanf(" %c", &command) != 1)
						{
							printf("Invalid command. Please try again.\n");
						}
						else
						{
							if (toupper(command) == 'Y')
							{
								if (!deletePlayer(playerCode))
								{
									printf("Error: Failed to delete player %d[%s]. Please contact our customer service for help.\n", playerCode, retrievePlayer(playerCode)->playerName);
								}
							}
							else
							{
								printf("Player %d[%s] not deleted.\n", playerCode, retrievePlayer(playerCode)->playerName);
							}
						}
					}
				}
				break;
			case 'P':
				// Print all players
				if (printPlayerList())
				{
					printf("No player in database. Use \"i\" to insert a new player.\n");
				}
				break;
			case 'H':
				playerHelp();
				break;
			case 'Q':
				printf("You are now leaving the player menu.\n");
				quit = 1;
				break;
			default:
				// Catch invalid input
				printf("Invalid operation code.");
				playerHelp();
				break;
			}
		}
	}
}

int insertPlayer()
{
	int playerCode, playerAge, teamCode;
	char playerName[DBLBUFSIZE], playerClub[DBLBUFSIZE];
	// Insert a player
	printf("Enter player code: ");
	if (scanf("%d", &playerCode) != 1 || playerCode < 0)
	{
		while (getchar() != '\n')
			;
		printf("Invalid player code. Player not added.\n");
	}
	// Check if player code already exists
	else if (isPlayerExist(playerCode))
	{
		while (getchar() != '\n')
			;
		printf("Player code already exists. Use \"u\" to update a player.\n");
	}
	else
	{
		while (getchar() != '\n')
			;
		printf("Enter player name: ");
		// limit playerName to DBLBUFSIZE
		if (!fgets(playerName, DBLBUFSIZE, stdin) || strcspn(playerName, "\n") == DBLBUFSIZE - 1)
		{
			while (getchar() != '\n')
				;
			printf("Invalid player name. Player not added.\n");
		}
		else
		{
			// Remove blank space at the end of the string
			playerName[strlen(playerName) - 1] = '\0';
			if (isPlayerNamed(playerName))
			{
				printf("Player name is registered. Please pick another one.\n");
			}
			else
			{
				printf("Enter player age: ");
				// Check player age validity
				if (scanf("%d", &playerAge) != 1 || playerAge < 17 || playerAge > 99)
				{
					while (getchar() != '\n')
						;
					printf("Invalid player age. Player not added.\n");
				}
				else
				{
					while (getchar() != '\n')
						;
					printf("Enter player's professional club affiliation: ");
					// limit playerName to DBLBUFSIZE
					if (!fgets(playerClub, DBLBUFSIZE, stdin) || strcspn(playerName, "\n") == DBLBUFSIZE - 1)
					{
						while (getchar() != '\n')
							;
						printf("Invalid player's professional club affiliation. Player not added.\n");
					}
					else
					{
						// Remove blank space at the end of the string
						playerClub[strlen(playerClub) - 1] = '\0';
						printf("Enter team code: ");
						if (scanf("%d", &teamCode) != 1 || teamCode < 0)
						{
							while (getchar() != '\n')
								;
							printf("Invalid team code. Player not added.\n");
						}
						else if (!isExist(teamCode))
						{
							while (getchar() != '\n')
								;
							printf("Team code does not exist. Player not added.\n");
						}
						else
						{
							while (getchar() != '\n')
								;
							// Add player to database
							if (!insertP(playerCode, playerName, playerAge, playerClub, teamCode))
							{
								printf("Error: Failed to add player. Please contact our customer service for help.\n");
							}
							else
							{
								printf("Player %d[%s] added.\n", playerCode, playerName);
							}
						}
					}
				}
			}
		}
	}
}

// insertP() inserts a new player into the linked list
int insertP(int playerCode, char playerName[DBLBUFSIZE], int playerAge, char playerClub[DBLBUFSIZE], int teamCode)
{
	player *curr = headP, *prev, *new, newPlayer;
	newPlayer.playerCode = playerCode;
	strcpy(newPlayer.playerName, playerName);
	newPlayer.playerAge = playerAge;
	strcpy(newPlayer.playerClub, playerClub);
	newPlayer.teamCode = teamCode;
	new = (player *)malloc(sizeof(player));
	if (new == NULL)
	{
#ifdef DEBUG
		perror("malloc");
#endif
		printf("Error: It looks like our database is full, please contact our customer service for help.\n");
	}
	else
	{
		// If the list is empty, insert the new player at the headP
		if (curr == NULL)
		{
			*new = newPlayer;
			new->next = curr;
			headP = new;
			return 1;
		}
		// If the new player is smaller than the headP, insert it at the headP
		else if (curr->playerCode > playerCode)
		{
			*new = newPlayer;
			new->next = curr;
			headP = new;
			return 1;
		}
		else
		{
			// Find the position to insert the new player
			while (curr != NULL && curr->playerCode < playerCode)
			{
				prev = curr;
				curr = curr->next;
			}
			*new = newPlayer;
			new->next = curr;
			prev->next = new;
			return 1;
		}
	}
	return 0;
}

// isPlayerExist() checks if a player code already exists
int isPlayerExist(int playerCode)
{
	player *curr = headP;
	while (curr != NULL)
	{
		if (curr->playerCode == playerCode)
		{
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// isPlayerNamed() checks if a player name already exists
int isPlayerNamed(char playerName[DBLBUFSIZE])
{
	player *curr = headP;
	while (curr != NULL)
	{
		if (strcmp(curr->playerName, playerName) == 0)
		{
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// updatePlayer() updates a player
int updatePlayer()
{
	int playerCode, playerAge, teamCode, updated = 0;
	char playerName[DBLBUFSIZE], playerClub[DBLBUFSIZE];
	player *workingPlayer;
	printf("Enter player code: ");
	if (scanf("%d", &playerCode) != 1 || playerCode < 0)
	{
		while (getchar() != '\n')
			;
		printf("Invalid player code. Player not updated.\n");
	}
	// Check existence of the player
	else if (!isPlayerExist(playerCode))
	{
		while (getchar() != '\n')
			;
		printf("Player not found. Player not updated.\n");
	}
	else
	{
		while (getchar() != '\n')
			;
		workingPlayer = retrievePlayer(playerCode);
		printf("Enter player name (Current: %s): ", workingPlayer->playerName);
		if (!fgets(playerName, DBLBUFSIZE, stdin) || strcspn(playerName, "\n") == DBLBUFSIZE - 1)
		{
			while (getchar() != '\n')
				;
			printf("Invalid player name. Player not updated.\n");
		}
		else
		{
			// Remove blank space at the end of the string
			playerName[strlen(playerName) - 1] = '\0';
			if (isPlayerNamed(playerName) && strcmp(playerName, workingPlayer->playerName))
			{
				printf("Player name is already registered. Please pick another one.\n");
			}
			else
			{
				printf("Enter player age (Current: %d): ", workingPlayer->playerAge);
				// Check player age validity
				if (scanf("%d", &playerAge) != 1 || playerAge < 17 || playerAge > 99)
				{
					while (getchar() != '\n')
						;
					printf("Invalid player age. Player not added.\n");
				}
				else
				{
					while (getchar() != '\n')
						;
					printf("Enter player's professional club affiliation (Current: %s): ", workingPlayer->playerClub);
					// limit playerName to DBLBUFSIZE
					if (!fgets(playerClub, DBLBUFSIZE, stdin) || strcspn(playerName, "\n") == DBLBUFSIZE - 1)
					{
						while (getchar() != '\n')
							;
						printf("Invalid player's professional club affiliation. Player not added.\n");
					}
					else
					{
						playerClub[strlen(playerClub) - 1] = '\0';
						printf("Enter team code (Current: %d): ", workingPlayer->teamCode);
						if (scanf("%d", &teamCode) != 1 || teamCode < 0)
						{
							while (getchar() != '\n')
								;
							printf("Invalid team code. Player not added.\n");
						}
						else if (!isExist(teamCode))
						{
							while (getchar() != '\n')
								;
							printf("Team code does not exist. Player not added.\n");
						}
						else
						{
							while (getchar() != '\n')
								;
							// Check if the player information is different from the existing player
							if (strcmp(workingPlayer->playerName, playerName) || workingPlayer->playerAge != playerAge || strcmp(workingPlayer->playerClub, playerClub) || workingPlayer->teamCode != teamCode)
							{
								strcpy(workingPlayer->playerName, playerName);
								workingPlayer->playerAge = playerAge;
								strcpy(workingPlayer->playerClub, playerClub);
								workingPlayer->teamCode = teamCode;
								updated = 1;
								if (deletePlayer(playerCode) && insertP(playerCode, playerName, playerAge, playerClub, teamCode))
								{
									printf("Player updated.\n");
								}
								else
								{
									printf("Error: We are unable to update the player. Please contact our customer service for help.\n");
								}
							}
							else
							{
								printf("No change is made.\n");
							}
						}
					}
				}
			}
		}
	}
	return updated;
}

// searchPlayer() searches for a player with the given playerCode
int searchPlayer(int playerCode)
{
	player *curr = headP;
	char stripedPlayerName[25], stripedClub[25];
	printf("%-12s%-24s%-12s%-32s%-12s\n", "Player Code", "Player Name", "Player Age", "Professional Club Affiliation", "Team Code");
	while (curr != NULL)
	{
		if (curr->playerCode == playerCode)
		{
			if (strlen(curr->playerName) > 24)
			{
				// Strip the player name to 21 characters
				strncpy(stripedPlayerName, curr->playerName, 21);
				for (int i = 0; i < 3; i++)
				{
					stripedPlayerName[21 + i] = '.';
				}
				stripedPlayerName[24] = '\0';
			}
			else
			{
				strcpy(stripedPlayerName, curr->playerName);
			}
			if (strlen(curr->playerClub) > 24)
			{
				strncpy(stripedClub, curr->playerClub, 21);
				for (int i = 0; i < 3; i++)
				{
					stripedClub[21 + i] = '.';
				}
				stripedClub[24] = '\0';
			}
			else
			{
				strcpy(stripedClub, curr->playerClub);
			}
			printf("%-12d%-24s%-12d%-32s%-12d\n", curr->playerCode, stripedPlayerName, curr->playerAge, stripedClub, curr->teamCode);
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// deletePlayer() removes a player with the given playerCode
int deletePlayer(int playerCode)
{
	player *curr = headP;
	player *prev = NULL;
	while (curr != NULL)
	{
		if (curr->playerCode == playerCode)
		{
			if (prev == NULL)
			{
				headP = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free(curr);
			return 1;
		}
		prev = curr;
		curr = curr->next;
	}
	return 0;
}

int printPlayerList()
{
	player *curr = headP;
	char stripedPlayerName[25], stripedClub[25];
	int empty = 1;
	printf("%-12s%-24s%-12s%-32s%-12s\n", "Player Code", "Player Name", "Player Age", "Professional Club Affiliation", "Team Code");
	while (curr != NULL)
	{
		if (strlen(curr->playerName) > 24)
		{
			// Strip the player name to 22 characters
			strncpy(stripedPlayerName, curr->playerName, 22);
			for (int i = 0; i < 3; i++)
			{
				stripedPlayerName[22 + i] = '.';
			}
			stripedPlayerName[25] = '\0';
		}
		else
		{
			strcpy(stripedPlayerName, curr->playerName);
		}
		if (strlen(curr->playerClub) > 24)
		{
			strncpy(stripedClub, curr->playerClub, 22);
			for (int i = 0; i < 3; i++)
			{
				stripedClub[22 + i] = '.';
			}
			stripedClub[25] = '\0';
		}
		else
		{
			strcpy(stripedClub, curr->playerClub);
		}
		printf("%-12d%-24s%-12d%-32s%-12d\n", curr->playerCode, stripedPlayerName, curr->playerAge, stripedClub, curr->teamCode);

		curr = curr->next;
		empty = 0;
	}
	return empty;
}

int playerFromTeam(int teamCode)
{
	int empty = 1;
	char stripedPlayerName[25], stripedClub[25];
	player *curr = headP;
	printf("%-12s%-24s%-12s%-32s%-12s\n", "Player Code", "Player Name", "Player Age", "Professional Club Affiliation", "Team Code");
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode)
		{
			if (strlen(curr->playerName) > 24)
			{
				// Strip the player name to 21 characters
				strncpy(stripedPlayerName, curr->playerName, 21);
				for (int i = 0; i < 3; i++)
				{
					stripedPlayerName[21 + i] = '.';
				}
				stripedPlayerName[24] = '\0';
			}
			else
			{
				strcpy(stripedPlayerName, curr->playerName);
			}
			if (strlen(curr->playerClub) > 24)
			{
				strncpy(stripedClub, curr->playerClub, 21);
				for (int i = 0; i < 3; i++)
				{
					stripedClub[21 + i] = '.';
				}
				stripedClub[24] = '\0';
			}
			else
			{
				strcpy(stripedClub, curr->playerClub);
			}
			printf("%-12d%-24s%-12d%-32s%-12d\n", curr->playerCode, stripedPlayerName, curr->playerAge, stripedClub, curr->teamCode);
			
			empty = 0;
		}
		curr = curr->next;
	}
	return empty;
}

int isTeamEmpty(int teamCode)
{
	int empty = 1;
	player *curr = headP;
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode)
		{
			empty = 0;
		}
		curr = curr->next;
	}
	return empty;
}

// retrievePlayer() retrieves a player with the given playerCode
player *retrievePlayer(int playerCode)
{
	player *curr = headP;
	while (curr != NULL)
	{
		if (curr->playerCode == playerCode)
		{
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

// playerHelp() prints the help menu for the player module
void playerHelp()
{
	printf("Here is what I can help you with: \n\
i - Insert a player\n\
s - Search for a player\n\
u - Update a player\n\
d - Delete a player\n\
p - Print all players\n\
h - Help menu\n\
q - Go back to the main menu\n");
	return;
}
