#pragma once
#include <conio.h>
#include "allBirds.h"
#include "Essentials.h"




struct
{

	int birdSelectedIndex[3] = { UNDEFINED, UNDEFINED, UNDEFINED };

	int optionSelected = 1;
	int birdListSelected = 0;

	bool choosingBird = false;

} SGS; // Start Game Struct 





party& creatingPlayerParty();


void printPlayerSelectionAndStuffIDK();




void printChoosingSlot();


void printChoosingBird();


party& makePartyBasedOnChoices();