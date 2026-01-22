#pragma once
#include "Start Journey.h"


party& creatingPlayerParty()
{
	SGS.optionSelected = 1;

	printPlayerSelectionAndStuffIDK();


	while (true)
	{

		if (!_kbhit())
			continue;



		int keyInput = _getch();




		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{
			if (SGS.optionSelected == 4)
			{
				if (SGS.birdSelectedIndex[0] == UNDEFINED)
					continue;



				bool emptyParty = true;

				for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
					if (SGS.birdSelectedIndex[i] != UNDEFINED)
						emptyParty = false;

				if (!emptyParty)
					break;

				continue;
			}


			if (SGS.choosingBird == true)
			{
				SGS.choosingBird = false;
				SGS.birdSelectedIndex[SGS.optionSelected - 1] = SGS.birdListSelected;
			}

			else if (SGS.choosingBird == false)
			{
				SGS.choosingBird = true;
				SGS.birdListSelected = 0;
			}


		}


		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			if (SGS.choosingBird == true)
				SGS.choosingBird = false;
			
			SGS.birdSelectedIndex[SGS.optionSelected - 1] = UNDEFINED;
		}


		// Going up or down
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{

				if (SGS.choosingBird == true)
				{
					SGS.birdListSelected--;

					if (SGS.birdListSelected < 0)
						SGS.birdListSelected = 0;
				}



				if (SGS.choosingBird == false)
				{
					SGS.optionSelected--;

					if (SGS.optionSelected < 1)
						SGS.optionSelected = 1;
				}

			}

			else if (keyInput == DOWN_ARROW)
			{

				if (SGS.choosingBird == true)
				{
					SGS.birdListSelected++;

					if (8 < SGS.birdListSelected)
						SGS.birdListSelected = 8;
				}



				if (SGS.choosingBird == false)
				{
					SGS.optionSelected++;

					if (4 < SGS.optionSelected)
						SGS.optionSelected = 4;
				}
			}

		}

		printPlayerSelectionAndStuffIDK();

	}



	party plrParty = makePartyBasedOnChoices();


	return plrParty;
}


void printPlayerSelectionAndStuffIDK()
{
	system("cls");

	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Selected your birds:\n";
	cout << "----------------------\n\n";


	if (SGS.choosingBird)
		printChoosingBird();

	else
		printChoosingSlot();



}



void printChoosingSlot()
{
	for (int i = 1; i < 4; i++)
	{
		cout << "-> ";

		if (SGS.optionSelected == i)
			cout << "  ";




		int birdIndex = SGS.birdSelectedIndex[i - 1];


		if (birdIndex == UNDEFINED)
			cout << "~~~~~~~~";

		else if (birdIndex == 0)
			cout << "Hummingbird";

		else if (birdIndex == 1)
			cout << "Kiwi";

		else if (birdIndex == 2)
			cout << "Chicken";

		else if (birdIndex == 3)
			cout << "Dodo";

		else if (birdIndex == 4)
			cout << "Eagle";

		else if (birdIndex == 5)
			cout << "Ostrich";

		else if (birdIndex == 6)
			cout << "Owl";

		else if (birdIndex == 7)
			cout << "Penguin";

		else if (birdIndex == 8)
			cout << "Shoebill";




		cout << "\n\n";
	}


	cout << "-> ";
	if (SGS.optionSelected == 4)
		cout << "  ";

	cout << "Confirm?\n";
}


void printChoosingBird()
{

	for (int i = 0; i < 9; i++)
	{
		cout << "-> ";

		if (SGS.birdListSelected == i)
			cout << "  ";





		if (i == 0)
			cout << "Hummingbird";

		else if (i == 1)
			cout << "Kiwi";

		else if (i == 2)
			cout << "Chicken";

		else if (i == 3)
			cout << "Dodo";

		else if (i == 4)
			cout << "Eagle";

		else if (i == 5)
			cout << "Ostrich";

		else if (i == 6)
			cout << "Owl";

		else if (i == 7)
			cout << "Penguin";

		else if (i == 8)
			cout << "Shoebill";


		cout << "\n";
	}


	cout << "\n----------------------\n";





	defaultBirdClass* usedForDescription = NULL;

	if (SGS.birdListSelected == 0)
		usedForDescription = new HummingbirdClass();

	else if (SGS.birdListSelected== 1)
		usedForDescription = new KiwiBirdClass();

	else if (SGS.birdListSelected== 2)
		usedForDescription = new ChickenBirdClass();

	else if (SGS.birdListSelected== 3)
		usedForDescription = new DodoBirdClass();

	else if (SGS.birdListSelected== 4)
		usedForDescription = new EagleBirdClass();

	else if (SGS.birdListSelected== 5)
		usedForDescription = new OstrichBirdClass();

	else if (SGS.birdListSelected== 6)
		usedForDescription = new OwlBirdClass();

	else if (SGS.birdListSelected== 7)
		usedForDescription = new PenguinBirdClass();

	else if (SGS.birdListSelected== 8)
		usedForDescription = new ShoebillBirdClass();


	for (int i = 0; i < 3; i++)
		if (usedForDescription != NULL)
			cout << usedForDescription->_description[i] << "\n";



}


party& makePartyBasedOnChoices()
{

	party plrParty;

	plrParty.birds = new defaultBirdClass * [MAX_BIRDS_PER_PARTY];
	plrParty.livingState = new livingStatus[MAX_BIRDS_PER_PARTY];
	plrParty.statMultipliers = new statMultipliesStruct[MAX_BIRDS_PER_PARTY];


	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		plrParty.birds[i] = NULL;

	
	defaultBirdClass* mainBird = NULL;

	
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{

		if (SGS.birdSelectedIndex[i] == UNDEFINED)
			continue;



		if (SGS.birdSelectedIndex[i] == 0)
			mainBird = new HummingbirdClass();

		else if (SGS.birdSelectedIndex[i] == 1)
			mainBird = new KiwiBirdClass();

		else if (SGS.birdSelectedIndex[i] == 2)
			mainBird = new ChickenBirdClass();

		else if (SGS.birdSelectedIndex[i] == 3)
			mainBird = new DodoBirdClass();

		else if (SGS.birdSelectedIndex[i] == 4)
			mainBird = new EagleBirdClass();

		else if (SGS.birdSelectedIndex[i] == 5)
			mainBird = new OstrichBirdClass();

		else if (SGS.birdSelectedIndex[i] == 6)
			mainBird = new OwlBirdClass();

		else if (SGS.birdSelectedIndex[i] == 7)
			mainBird = new PenguinBirdClass();

		else if (SGS.birdSelectedIndex[i] == 8)
			mainBird = new ShoebillBirdClass();



		plrParty.birds[i] = mainBird;

	}




	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		if (plrParty.birds[i] != NULL)
			plrParty.amountOfBirds++;




	return plrParty;

}