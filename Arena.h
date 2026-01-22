#ifndef ARENA_H
#define ARENA_H

#include <conio.h>
#include <windows.h>
#include "Essentials.h"
#include "allBirds.h"

// Keyboard Characters ASCII Number



int getConsoleWidth();
void printSeparatorLines();
void moveToColumn(int col);
string makeGrayText();
string makeWhiteText();
string makeYellowText();





party createPlayerParty(defaultBirdClass* birdOne, defaultBirdClass* birdTwo = NULL, defaultBirdClass* birdThree = NULL);
party createEnemyParty(defaultBirdClass* birdOne = NULL, defaultBirdClass* birdTwo = NULL, defaultBirdClass* birdThree = NULL);
party* createRandomParty();




class arenaClass
{
public:


	arenaClass(party& playerParty, party& enemyParty);

	~arenaClass();


	teamWinner FIGHT();




private:
	
	party _playerParty;
	party _enemyParty;
	int _round = 1;


	string _selectedDescription[13]; // Try to keep maximum of 30 characters per line
	string _previousTurnSummary[7];	// This one tells the summary of the last used move
	bool _lastInputWasMoveUsed = false;


	indexSelection _currentSelection = BIRD_SELECTION;
	int _birdSelectionIndex = 0;
	int _moveSelectionIndex = 0;
	int _enemiesSelectionIndex = 0;
	bool _enemiesSelected[MAX_BIRDS_PER_PARTY] = {NOT_SELECTED, NOT_SELECTED, NOT_SELECTED};
	bool _alliesSelected[MAX_BIRDS_PER_PARTY] = {NOT_SELECTED, NOT_SELECTED, NOT_SELECTED};
	
	




	void setUpTurn();


	void printArena();





	void playerTurn();


	void enemyTurn();

	



	void restBird(party& mainParty, defaultBirdClass* mainBird, int indexInParty);



	void turnResultsIntoDescription(string results);

	void changeDescription(defaultBirdClass* bird, teamSide team);

	void changeDescription(defaultAbilityClass* ability);



	void checkForDeaths();

	teamWinner checkForDeadTeam();

};


#endif