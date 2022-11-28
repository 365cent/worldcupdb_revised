/*==============================================================
| Name: worldcup_team.c
| Description of parameters:
|   head: the head of the linked list
|   quit: whether to return to the main menu
|   teamCode: the team code
|   teamName: the team name
|   groupSeed: the group seed of the team
|   kitColor: the kit color of the team
|   curr: the current team in the linked list
|   prev: the previous team in the linked list
|   next: the next team in the linked list
|   newTeam: the new team to be inserted
|   empty: whether the team list is empty
|   update: whether to update the team
---------------------------------------------------------------
*/
#include "worldcup_team.h"

team *head = NULL;

int worldcup_team(int mode)
{
	int teamCode, quit = 0;
	char command;
	if (mode == 1)
	{
#ifndef DEBUG
#define DEBUG
#endif
		printf("Hello from worldcup_team\n");
	}
	while (!quit)
	{
		printf("[Team]Enter operation code: ");
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
				insertTeam();
				break;
			case 'S':
				printf("Enter team code: ");
				if (scanf("%d", &teamCode) != 1 || teamCode < 0)
				{
					printf("Invalid team code");
				}
				else
				{
					if (!search(teamCode))
					{
						printf("Team not found. Use \"i\" to insert a team.\n");
					}
				}
				break;
			case 'U':
				updateTeam();
				break;
			case 'D':
				printf("Enter team code: ");
				if (scanf("%d", &teamCode) != 1 || teamCode < 0)
				{
					printf("Invalid team code. Please try again.\n");
				}
				else
				{
					if (!retrieveTeam(teamCode))
					{
						printf("Team not found. Use \"i\" to insert a team.\n");
					}
					else
					{
						printf("You are about to delete team %d[%s]. Are you sure? (y/n): ", teamCode, retrieveTeam(teamCode)->teamName);
						if (scanf(" %c", &command) != 1)
						{
							printf("Invalid command. Please try again.\n");
						}
						else
						{
							if (toupper(command) == 'Y')
							{
								if (!delete (teamCode) && isTeamEmpty(teamCode))
								{
									printf("Error: Failed to delete team %d[%s]. Please contact our customer service for help.\n", teamCode, retrieveTeam(teamCode)->teamName);
								}
								else 
								{
									printf("Team %d[%s] has been deleted.\n", teamCode, retrieveTeam(teamCode)->teamName);
								}
							}
							else
							{
								printf("Team %d[%s] not deleted.\n", teamCode, retrieveTeam(teamCode)->teamName);
							}
						}
					}
				}
				break;
			case 'H':
				teamHelp();
				break;
			case 'P':
				// Print all teams
				if (printTeamList())
				{
					printf("No teams in database. Use \"i\" to insert a new team.\n");
				}
				break;
			case 'R':
				printf("Enter team code: ");
				if (scanf("%d", &teamCode) != 1 || teamCode < 0)
				{
					printf("Invalid team code. Please try again.\n");
				}
				else
				{
					if (!isExist(teamCode))
					{
						printf("Team not found. Use \"i\" to insert a team.\n");
					}
					else
					{
						if (search(teamCode) && playerFromTeam(teamCode))
						{
							printf("This team has no registered players.\n");
						}
					}
				}
				break;
			case 'Q':
				printf("You are now leaving the team menu.\n");
				quit = 1;
				break;
			default:
				// Catch invalid input
				printf("Invalid operation code. Please try again.\n");
				teamHelp();
				break;
			}
		}
	}
}

int insertTeam()
{
	int teamCode;
	char kitColor;
	char teamName[BUFSIZE], groupSeed[3];
	// Insert a team
	printf("Enter team code: ");
	if (scanf("%d", &teamCode) != 1 || teamCode < 0)
	{
		while (getchar() != '\n')
			;
		printf("Invalid team code. Team not added.\n");
	}
	// Check if team code already exists
	else if (isExist(teamCode))
	{
		while (getchar() != '\n')
			;
		printf("Team code already exists. Use \"u\" to update a team.\n");
	}
	else
	{
		while (getchar() != '\n')
			;
		printf("Enter team name: ");
		// limit teamName to BUFSIZE
		if (!fgets(teamName, BUFSIZE, stdin) || strcspn(teamName, "\n") == BUFSIZE - 1)
		{
			while (getchar() != '\n')
				;
			printf("Invalid team name. Team not added.\n");
		}
		else
		{
			// Remove blank space at the end of the string
			teamName[strlen(teamName) - 1] = '\0';
			if (isNamed(teamName))
			{
				printf("Team name is registered. Please pick another one.\n");
			}
			else
			{
				printf("Enter group seed: ");
				// Check group seed validity
				if (!fgets(groupSeed, 3, stdin) || toupper(groupSeed[0]) < 'A' || toupper(groupSeed[0]) > 'H' || groupSeed[1] < '1' || groupSeed[1] > '4')
				{
					while (getchar() != '\n')
						;
					printf("Invalid group seed. Team not added.\n");
				}
				else if (isSeeded(groupSeed))
				{
					while (getchar() != '\n')
						;
					printf("Group seed duplicated. Team not added.\n");
				}
				else
				{
					while (getchar() != '\n')
						;
					groupSeed[0] = toupper(groupSeed[0]);
					groupSeed[2] = '\0';
					printf("Enter kit color: ");
					if (scanf(" %c", &kitColor) != 1)
					{
						printf("Invalid color code.");
					}
					else
					{
						while (getchar() != '\n')
							;
						kitColor = toupper(kitColor);
						// Check color plate
						if (kitColor != 'R' && kitColor != 'O' && kitColor != 'Y' && kitColor != 'G' && kitColor != 'B' && kitColor != 'I' && kitColor != 'V')
						{
							printf("Invalid kit color. Team not added.\n");
						}
						else
						{
							// Insert the team
							if (insert(teamCode, teamName, groupSeed, kitColor))
							{
								printf("Team %d[%s] added.\n", teamCode, teamName);
							}
							else
							{
								printf("Error: Failed to add team %d[%s]. Please contact our customer service for help.\n", teamCode, teamName);
							}
						}
					}
				}
			}
		}
	}
}

// insert() inserts a new team into the linked list
int insert(int teamCode, char teamName[BUFSIZE], char groupSeed[3], char kitColor)
{
	team *curr = head, *prev, *new, newTeam;
	newTeam.teamCode = teamCode;
	strcpy(newTeam.teamName, teamName);
	strcpy(newTeam.groupSeed, groupSeed);
	newTeam.kitColor = kitColor;
	new = (team *)malloc(sizeof(team));
	if (new == NULL)
	{
#ifdef DEBUG
		perror("malloc");
#endif
		printf("Error: It looks like our database is full, please contact our customer service for help.\n");
	}
	else
	{
		// If the list is empty, insert the new team at the head
		if (curr == NULL)
		{
			*new = newTeam;
			new->next = curr;
			head = new;
			return 1;
		}
		// If the new team is smaller than the head, insert it at the head
		else if (curr->teamCode > teamCode)
		{
			*new = newTeam;
			new->next = curr;
			head = new;
			return 1;
		}
		else
		{
			// Find the position to insert the new team
			while (curr != NULL && curr->teamCode < teamCode)
			{
				prev = curr;
				curr = curr->next;
			}
			*new = newTeam;
			new->next = curr;
			prev->next = new;
			return 1;
		}
	}
	return 0;
}

// isExist() checks if a team code already exists
int isExist(int teamCode)
{
	team *curr = head;
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode)
		{
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// updateTeam() updates a team
int updateTeam()
{
	int updated = 0, teamCode;
	char kitColor;
	char teamName[BUFSIZE], groupSeed[3];
	team *workingTeam;
	printf("Enter team code: ");
	if (scanf("%d", &teamCode) != 1 || teamCode < 0)
	{
		while (getchar() != '\n')
			;
		printf("Invalid team code. Team not updated.\n");
	}
	// Check existence of the team
	else if (!isExist(teamCode))
	{
		while (getchar() != '\n')
			;
		printf("Team not found. Team not updated.\n");
	}
	else
	{
		while (getchar() != '\n')
			;
		workingTeam = retrieveTeam(teamCode);
		printf("Enter team name (Current: %s): ", workingTeam->teamName);
		if (!fgets(teamName, BUFSIZE, stdin) || strcspn(teamName, "\n") == BUFSIZE - 1)
		{
			while (getchar() != '\n')
				;
			printf("Invalid team name. Team not updated.\n");
		}
		else
		{
			// Remove blank space at the end of the string
			teamName[strlen(teamName) - 1] = '\0';
			if (isNamed(teamName) && strcmp(teamName, workingTeam->teamName))
			{
				printf("Team name is already registered. Please pick another one.\n");
			}
			else
			{
				printf("Enter group seed (Current: %s): ", workingTeam->groupSeed);
				if (!fgets(groupSeed, 3, stdin) || toupper(groupSeed[0]) < 'A' || toupper(groupSeed[0]) > 'H' || groupSeed[1] < '1' || groupSeed[1] > '4')
				{
					while (getchar() != '\n')
						;
					printf("Invalid group seed. Team not updated.\n");
				}
				else if (isSeeded(groupSeed) && strcmp(groupSeed, workingTeam->groupSeed))
				{
					while (getchar() != '\n')
						;
					printf("Group seed duplicated. Team not updated.\n");
				}
				else
				{
					while (getchar() != '\n')
						;
					groupSeed[0] = toupper(groupSeed[0]);
					groupSeed[2] = '\0';
					printf("Enter kit color (Current: %c): ", workingTeam->kitColor);

					if (scanf(" %c", &kitColor) != 1)
					{
						printf("Invalid color code.");
					}
					else
					{
						kitColor = toupper(kitColor);
						if (kitColor != 'R' && kitColor != 'O' && kitColor != 'Y' && kitColor != 'G' && kitColor != 'B' && kitColor != 'I' && kitColor != 'V')
						{
							printf("Invalid kit color. Team not updated.\n");
						}
						// Check if the team information is different from the existing team
						else if (strcmp(workingTeam->teamName, teamName) || strcmp(workingTeam->groupSeed, groupSeed) || workingTeam->kitColor != kitColor)
						{
							if (delete (teamCode) && insert(teamCode, teamName, groupSeed, kitColor))
							{
								printf("Team updated.\n");
							}
							else
							{
								printf("Error: We are unable to update the team. Please contact our customer service for help.\n");
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
	return updated;
}

// isNamed() checks if a team with the given teamName exists in the list
int isNamed(char teamName[BUFSIZE])
{
	team *curr = head;
	while (curr != NULL)
	{
		if (strcmp(curr->teamName, teamName) == 0)
		{
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// isSeeded() checks if a team with the given groupSeed exists in the list
int isSeeded(char groupSeed[3])
{
	team *curr = head;
	while (curr != NULL)
	{
		if (strcmp(curr->groupSeed, groupSeed) == 0)
		{
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// search() searches for a team with the given teamCode
int search(int teamCode)
{
	team *curr = head;
	printf("%-20s%-24s%-20s%-12s\n", "Team Code", "Team Name", "Group Seed", "Kit Color");
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode)
		{
			printf("%-20d%-24s%-20s", curr->teamCode, curr->teamName, curr->groupSeed);
			printColor(curr->kitColor);
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

// delete() removes a team with the given teamCode
int delete (int teamCode)
{
	int deleted = 0;
	team *curr = head;
	team *prev = NULL;
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode && isTeamEmpty(curr->teamCode))
		{
			if (prev == NULL)
			{
				head = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free(curr);
			deleted = 1;
		}
		prev = curr;
		curr = curr->next;
	}
	if (!deleted)
	{
		printf("There are players registered in this team. Please remove them first.\n");
		if (!playerFromTeam)
		{
			printf("Error: We are unable to delete the team. Please contact our customer service for help.\n");
		}
	}
	return deleted;
}

// printTeamList() prints all the teams in the teamList
int printTeamList()
{
	team *curr = head;
	int empty = 1;
	printf("%-20s%-24s%-20s%-12s\n", "Team Code", "Team Name", "Group Seed", "Kit Color");
	while (curr != NULL)
	{
		printf("%-20d%-24s%-20s", curr->teamCode, curr->teamName, curr->groupSeed);
		printColor(curr->kitColor);
		curr = curr->next;
		empty = 0;
	}
	return empty;
}

// printColor() prints the color of the kit
void printColor(char color)
{
	int error = 0;
	switch (color)
	{
	case 'R':
		printf("%-12s", "Red");
		break;
	case 'O':
		printf("%-12s", "Orange");
		break;
	case 'Y':
		printf("%-12s", "Yellow");
		break;
	case 'G':
		printf("%-12s", "Green");
		break;
	case 'B':
		printf("%-12s", "Blue");
		break;
	case 'I':
		printf("%-12s", "Indigo");
		break;
	case 'V':
		printf("%-12s", "Violet");
		break;
	default:
		printf("%-12s", "NaN");
		break;
	}
	printf("\n");
	return;
}

// retrieveTeam() retrieves a team with the given teamCode
team *retrieveTeam(int teamCode)
{
	team *curr = head;
	while (curr != NULL)
	{
		if (curr->teamCode == teamCode)
		{
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

// teamHelp() prints the help menu for the team module
void teamHelp()
{
	printf("Here is what I can help you with: \n\
i - Insert a team\n\
s - Search for a team\n\
u - Update a team\n\
d - Delete a team\n\
p - Print all teams\n\
R - Print out registed players in a team\n\
h - Help menu\n\
q - Go back to the main menu\n");
	return;
}
