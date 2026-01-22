#ifndef ESSENTIALS_H
#define ESSENTIALS_H


#include "Ability Class.h"
#include "Bird Class.h"




const int TAB = 9;
const int SPACEBAR = 32;
const int BACKSPACE = 8;
const int ENTER = 13;
const int UP_ARROW = 72;
const int DOWN_ARROW = 80;
const int LEFT_ARROW = 75;
const int RIGHT_ARROW = 77;
const int ARROW_KEYS = 224;		// This must be checked before checking for arrow keys
const int Z_KEY = 122;
const int X_KEY = 120;
const int C_KEY = 99;
const int MOVING_NEXT_CATEGORY = 10;
const int MOVING_PREVIOUS_CATEGORY = -10;
const int RESTING = 67;
const int SELECTED_TARGET = 20;
const int UNDEFINED = -1;


const int MAX_BIRDS_PER_PARTY = 3;

const bool NOT_SELECTED = false;
const bool SELECTED = true;

const bool USED_TURN = true;
const bool FREE_TURN = false;


enum indexSelection { BIRD_SELECTION, MOVE_SELECTION, ENEMY_SELECTION, ENEMY_INSPECT };
enum teamWinner { NO_WINNERS, PLAYER_WIN, ENEMY_WIN };


enum livingStatus { DEAD, ALIVE };
enum teamSide { PLAYER, ENEMY };
enum difficulty {EASY, MEDIUM, HARD};


struct statMultipliesStruct
{
	float attackMultiplier = 1.0f;
	float defenseMultiplier = 1.0f;
	int offspringAddon = 0;
	float dodgeMultiplier = 1.0f;
	float critkMultiplier = 1.0f;
};


struct party
{

	// Both are dynamic arrays, their index should be refering to the same bird
	defaultBirdClass** birds = NULL;
	statMultipliesStruct* statMultipliers = NULL;
	livingStatus* livingState = NULL;
	bool usedTurns[MAX_BIRDS_PER_PARTY] = { FREE_TURN,FREE_TURN,FREE_TURN };

	int amountOfBirds = 0;


	// Eggs = Mana, Mana = Use Move, Use Move = kill enemy, kill enemy = win. More Eggs = Win
	int amountOfEggs = 0;

};


#endif // !ESSENTIALS_H
