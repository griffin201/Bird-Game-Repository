#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <time.h>

#include "Town.h"




int main()
{
	// Sets random and make text shiny white
	srand(time(0));
	makeWhiteText();


	// Player creates their party
 	party plrParty = creatingPlayerParty();

	// Initializes the town
	townClass town(plrParty);

	// Game input loop in town
	town.townInputLoop();

}