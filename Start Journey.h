#pragma once
#include <conio.h>		// For keyboard input
#include "allBirds.h"
#include "Essentials.h"




// Structure for selecting player birds
struct
{

	int birdSelectedIndex[3] = { UNDEFINED, UNDEFINED, UNDEFINED };

	int optionSelected = 1;
	int birdListSelected = 0;

	bool choosingBird = false;

} SGS; // Start Game Struct 




// Creating the player party input loop
party& creatingPlayerParty();

// Gets all the selected birds numbers and makes them into birds then packets them into a party
party& makePartyBasedOnChoices();


// Prints the input loop for creating player party
void printTeamSelection();

// Prints when selecting slot for bird
void printChoosingSlot();

// Prints when selecting bird
void printChoosingBird();
