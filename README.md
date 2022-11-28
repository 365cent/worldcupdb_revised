# WorldcupDB 2.0 with linked list
> The 2211 World Cup is fast approaching. Your work on building worldCupDB.c (Assignment 4) was a great start but it's time to build version 2.0. The old version was missing a few important features:

You need to keep track of an arbitrary number of teams, not just the 32 who qualified for the tournament
* There is no way to delete teams
* You need to keep a database of players as well
* The program is a little large. It's time to break it up into individual files
* There is very little code from Assignment 4 which will be applicable for Assignment 5. You should consider this to be a fresh assignment. Don't try to back stitch Assignment 5 into your existing Assignment 4.

## Purpose
This assignment will ask you to apply the following concepts from class:

## Basic programming concepts
* Intermediate concepts added in Assignment 4
* Linked Lists and memory management
* Makefiles
* Program organization

## Design
* As before, each election team will be stored as a structure with the following attributes:

### Team
* Team code (eg. 0, 1, 2, 3, 4, etc.)
* Each team code must be unique. There is no limit to the number of teams but each code will be greater than or equal to 0
* Team name (eg. "Australia", "Cameroon", "Canada", "Argentina", "Belgium", etc.)
* Only team names up to 25 characters in length are acceptable (including the null character - So think of this as 24+1). Each team name must be unique
* Group seeding (eg. "A1", "B3", "F2", etc.)
* Only groups A-H and seeds 1-4 are acceptable. (So only A1, A2, A3, A4, B1, B2, ..., H3, H4). Each group seeding must be unique
* Primary kit (uniform) colours (eg. "Red", "Orange", "Yellow", "Green", "Blue", "Indigo", and "Violet")
* Only the values "R", "O", "Y", "G", "B", "I", "V" are acceptable.
Now, you will also need to store each team's player as a structure with the following attributes:

### Player
* Player code (eg. 0, 1, 2, 3, 4, etc.)
* Each player code must be unique. There is no limit to the number of players but each code will be greater than or equal to 0
* Player name (eg. "John Smith", "Jane Doe", etc.)
* Only names up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
* Player age (eg. 17, 18, 19, 20, etc.)
* Only integers 17-99 are acceptable
* Professional club affiliation (eg. "Manchester City", "Los Angeles FC", "Toronto FC", "AFC Ajax", etc.)
* Only names up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
Your program will then use a linked list of structures to represent all teams and a linked list of structures to represent all players.
