#ifndef ESSENTIALS_H
#define ESSENTIALS_H


#include "Ability Class.h"
#include "Bird Class.h"



// Keyboard keys
const int ARROW_KEYS = 224;						// This must be checked before checking for arrow keys
const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;
const int Z_KEY = 122;
const int X_KEY = 120;
const int C_KEY = 99;

// Used for selection moving during combat
const int MOVING_NEXT_CATEGORY = 10;
const int MOVING_PREVIOUS_CATEGORY = -10;
const int RESTING = 67;
const int SELECTED_TARGET = 20;
const int UNDEFINED = -1;

// Max birds per party duh
const int MAX_BIRDS_PER_PARTY = 3;

// Used for selecting or not selecting an enemy bird
const bool NOT_SELECTED = false;
const bool SELECTED = true;

// Used for checking if the bird used a move or not
const bool USED_TURN = true;
const bool FREE_TURN = false;


// Enum for what category the user is in during player turn
enum indexSelection { BIRD_SELECTION, MOVE_SELECTION, ENEMY_SELECTION, ENEMY_INSPECT };

// Enum for deciding the winner
enum teamWinner { NO_WINNERS, PLAYER_WIN, ENEMY_WIN };

// Enum for checking dead or alive birds
enum livingStatus { DEAD, ALIVE };

// Enum for which team
enum teamSide { PLAYER, ENEMY };


// Structure for stat multipliers
struct statMultipliesStruct
{
	float attackMultiplier = 1.0f;
	float defenseMultiplier = 1.0f;
	int offspringAddon = 0;
	float dodgeMultiplier = 1.0f;
	float critkMultiplier = 1.0f;
};


// Structure for player/enemy party, stores birds and combat logic
struct party
{

	// Both are dynamic arrays, their index should be refering to the same bird
	defaultBirdClass** birds = NULL;
	statMultipliesStruct* statMultipliers = NULL;
	livingStatus* livingState = NULL;
	bool usedTurns[MAX_BIRDS_PER_PARTY] = { FREE_TURN,FREE_TURN,FREE_TURN };

	// Amount of available birds
	int amountOfBirds = 0;

	// Eggs = Mana, Mana = Use Move, Use Move = kill enemy, kill enemy = win. More Eggs = Win
	int amountOfEggs = 0;

};


#endif // !ESSENTIALS_H
