#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <time.h>

#include "Town.h"




int main()
{
	srand(time(0));
	makeWhiteText();


 	party plrParty = creatingPlayerParty();



	townClass town(plrParty);

	town.townInputLoop();






	/*
	party enemyParty = createEnemyParty();


	arenaClass arena(plrParty, enemyParty);


	arena.FIGHT();
	*/

	system("cls");

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		if (plrParty.birds[i] != NULL)
			cout << i+1 << ") " << plrParty.birds[i]->_name << "\n";



	cout << "\n\n";
	system("pause");
	system("cls");

}