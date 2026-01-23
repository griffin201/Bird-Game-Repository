#ifndef ARENA_H
#define ARENA_H

#include <conio.h>
#include <windows.h>
#include "Essentials.h"
#include "allBirds.h"

// Keyboard Characters ASCII Number



// Declaring functions involving the console window
int getConsoleWidth();
void printSeparatorLines();
void moveToColumn(int col);
string makeGrayText();
string makeWhiteText();
string makeYellowText();



// Functions for creating enemy and player party set or random
party createPlayerParty(defaultBirdClass* birdOne, defaultBirdClass* birdTwo = NULL, defaultBirdClass* birdThree = NULL);
party createEnemyParty(defaultBirdClass* birdOne = NULL, defaultBirdClass* birdTwo = NULL, defaultBirdClass* birdThree = NULL);
party* createRandomParty();




class arenaClass
{
public:


	// Main contructor for arena, intializes variables and allocates used memory
	arenaClass(party& playerParty, party& enemyParty);

	// Deletes the allocated memory
	~arenaClass();

	// Fights the enemy, returns who won the battle
	teamWinner FIGHT();



private:
	

	// The parties in the match
	party _playerParty;
	party _enemyParty;


	// Displaying information in the screen stuff
	int _round = 1;
	string _selectedDescription[13];		// Try to keep maximum of 30 characters per line
	string _previousTurnSummary[7];			// This one tells the summary of the last used move
	bool _lastInputWasMoveUsed = false;		// True if last input was a move used


	// Indexes for selecting birds, moves and enemies
	indexSelection _currentSelection = BIRD_SELECTION;
	int _birdSelectionIndex = 0;
	int _moveSelectionIndex = 0;
	int _enemiesSelectionIndex = 0;
	bool _enemiesSelected[MAX_BIRDS_PER_PARTY] = {NOT_SELECTED, NOT_SELECTED, NOT_SELECTED};
	bool _alliesSelected[MAX_BIRDS_PER_PARTY] = {NOT_SELECTED, NOT_SELECTED, NOT_SELECTED};
	
	



	// Sets up the round
	void setUpRound();


	// Prints the arena
	void printArena();




	// Logic for player turn
	void playerTurn();

	// Logic for enemy turn and AI
	void enemyTurn();

	


	// Action for resting bird
	void restBird(party& mainParty, defaultBirdClass* mainBird, int indexInParty);


	// Turn the results into description format
	void turnResultsIntoDescription(string results);

	// Changes the description array based on the bird
	void changeDescription(defaultBirdClass* bird, teamSide team);

	// Changes the description array based on the move
	void changeDescription(defaultAbilityClass* ability);


	// Makes enemies "Dead" if their hp is less than 0
	void checkForDeaths();

	// Checks for winner basically
	teamWinner checkForDeadTeam();

};


#endif