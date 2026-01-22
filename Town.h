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


	townClass(party& plrParty);

	~townClass();


	void townInputLoop();


	
private:


	// Main Variables
	party& plrParty;





	// Main Input Loop
	int selectedCategory = 0;

	void printTownInputLoop();




	// Playing Tournament Logic
	party** enemiesInTheTournament = NULL;
	int amountOfEnemies = 1;
	int currentFight = 0;

	void playRandomTournament();

	void printTournamentList();

	void makeRandomEnemies();







	// File variables

	string fileDirectory = "";



	// Loading File Logic

	bool couldOpenFile = true;
	int loadFightCategory = 0;

	void loadCustomFightInputLoop();

	void printLoadCustomFightInputLoop();

	void getFileName();

	bool checkForValidFile();

	defaultBirdClass* makeBirdBasedOnSymbol(char birdSymbol);

	void fightCustomEnemy();





	// Creating File Logic
	int makeFightCategory = 0;
	int selectingBirdToMakeCategory = 0;

	char selectedBirdsName[3] = { ' ',' ',' '};
	bool savedFile = false;

		
	void makeEnemyInputLoop();

	void printMakeEnemyInputLoop();

	void selectingBirdToAddToParty(int index);

	void printingSelectingBirdToParty();

	bool exportCustomFight();




};


#endif