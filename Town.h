#ifndef TOWN_H
#define TOWN_H
#include "Arena.h"
#include "Start Journey.h"



// For main town input loop
const int TOURNAMENT_CATEGORY = 0;
const int RECREATE_PARTY_CATEGORY = 1;
const int LOAD_FIGHT_CATEGORY = 2;
const int MAKE_FIGHT_CATEGORY = 3;


// For loading custom fights
const int NAMING_FILE_CATEGORY = 0;
const int CONFIRM_LOAD_CATEGORY = 1;


// For making custom fight
// reuses naming file category
const int BIRD_ONE_CATEGORY = 1;
const int BIRD_TWO_CATEGORY = 2;
const int BIRD_THREE_CATEGORY = 3;
const int CONFIRM_SAVE_CATEGORY = 4;





class townClass
{
public:


	// Constructor, just stores the player party
	townClass(party& plrParty);

	// Deconstructor, eliminates memory leak problems
	~townClass();


	// Main input loop for the game
	void townInputLoop();


	
private:


	// Main Variables
	party& plrParty;





	// // Main Input Loop

	int selectedCategory = 0;

	// Prints stuff for the townInputLoop
	void printTownInputLoop();





	// // Playing Tournament Logic

	party** enemiesInTheTournament = NULL;
	int amountOfEnemies = 1;
	int currentFight = 0;

	// Starts and sets up the tournament, cause the player to face off against enemies
	void playRandomTournament();

	// Prints the list of enemies for the tournament
	void printTournamentList();

	// Makes the enemies parties for the tournament
	void makeEnemiesForTournament();







	// // File variables

	string fileDirectory = "";





	// // Loading File Logic

	bool couldOpenFile = true;
	int loadFightCategory = 0;


	// Input loop for loading a file
	void loadCustomFightInputLoop();

	// Prints stuff for the input loop for loading a file
	void printLoadCustomFightInputLoop();

	// Gets user input for the file name
	void getFileName();

	// Checks if the valid exists
	bool checkForValidFile();

	// Makes a bird based on the symbol read from the file
	defaultBirdClass* makeBirdBasedOnSymbol(char birdSymbol);

	// Begin fight against custom enemy
	void fightCustomEnemy();





	// // Creating File Logic

	int makeFightCategory = 0;
	int selectingBirdToMakeCategory = 0;

	char selectedBirdsName[3] = { ' ',' ',' '};
	bool savedFile = false;

	
	// Input loop for making an enemy
	void makeEnemyInputLoop();

	// Prints stuff for the input loop of making enemy
	void printMakeEnemyInputLoop();

	// Input loop AGAIN for selecting a bird to add to the party
	void selectingBirdToAddToParty(int index);
	
	// Prints the birds for the input loop of selecting a bird
	void printingSelectingBirdToParty();

	// Exports the file/saves the enemy made
	bool exportCustomFight();




};


#endif