#pragma once
#include "Town.h"
#include <fstream>




townClass::townClass(party& plrParty)
	:plrParty(plrParty) { }

townClass::~townClass()
{
	for (int i = 0; i < amountOfEnemies; i++)
		delete enemiesInTheTournament[i];

	delete enemiesInTheTournament;
}



void townClass::townInputLoop()
{

	printTownInputLoop();


	while (true)
	{

		if (!_kbhit())
			continue;



		int keyInput = _getch();




		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			if (selectedCategory == TOURNAMENT_CATEGORY)
				playRandomTournament();

			if (selectedCategory == RECREATE_PARTY_CATEGORY)
				plrParty = creatingPlayerParty();

			if (selectedCategory == LOAD_FIGHT_CATEGORY)
				loadCustomFightInputLoop();

			if (selectedCategory == MAKE_FIGHT_CATEGORY)
				makeEnemyInputLoop();

		}


		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
				if (selectedCategory <= 0)
					continue;

				selectedCategory--;
			}

			else if (keyInput == DOWN_ARROW)
			{
				if (3 <= selectedCategory)
					continue;

				selectedCategory++;
			}

			else if (keyInput == LEFT_ARROW)
			{
				if (selectedCategory != TOURNAMENT_CATEGORY)
					continue;

				if (amountOfEnemies <= 1)
					continue;

				amountOfEnemies--;
			}

			else if (keyInput == RIGHT_ARROW)
			{
				if (selectedCategory != TOURNAMENT_CATEGORY)
					continue;

				if (30 <= amountOfEnemies)
					continue;

				amountOfEnemies++;
			}

		}




		printTownInputLoop();

	}



}



void townClass::printTownInputLoop()
{
	system("cls");

	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down / increase or decrease enemy count}\n\n";
	cout << " Select your mode:\n";
	cout << "-------------------\n\n";

	

	
	cout << " > ";
	if (selectedCategory == TOURNAMENT_CATEGORY)
		cout << "  ";
	
	cout << "Fight Random Tournament  (Enemies: " << amountOfEnemies << ")\n\n";



	cout << " > ";
	if (selectedCategory == RECREATE_PARTY_CATEGORY)
		cout << "  ";

	cout << "Change Team\n\n";



	cout << " > ";
	if (selectedCategory == LOAD_FIGHT_CATEGORY)
		cout << "  ";

	cout << "Load Custom Fight\n\n";



	cout << " > ";
	if (selectedCategory == MAKE_FIGHT_CATEGORY)
		cout << "  ";

	cout << "Make Custom Fight\n\n";





	cout << "-------------------\n\n";



	if (selectedCategory == TOURNAMENT_CATEGORY)
	{
		cout << "You fight random opponents in a tournament.\n";
		cout << "At the end of each fight, YOUR TEAM GETS WEAKER.\n";
		cout << "You can increase tournament lenght by moving arrow keys.\n";
		cout << "-------------------\n";
		cout << "Changes: Defeated birds are revived at the cost of losing half of their max health.\n";
		cout << "Living birds lose their max hp based on their missing health divided by 2\n";
		cout << "You cannot switch team.\nAnd you gain nothing for winning... Literally.\n";
		cout << "If you defeat the gauntlet of 30 enemies, you truly become the bird champion!\n";

	}

	if (selectedCategory == LOAD_FIGHT_CATEGORY)
	{
		cout << "You load a custom enemy from a .txt file.\n";
		cout << "And you also fight that loaded enemy duh.\n";
	}

	if (selectedCategory == MAKE_FIGHT_CATEGORY)
	{
		cout << "You make a custom enemy in a .txt file.\n";
		cout << "You can choose how many birds what birds the enemy has.\n";
	}

}





#pragma region Tournament Logic


void townClass::playRandomTournament()
{

	makeRandomEnemies();


	for (currentFight = 0; currentFight < amountOfEnemies; currentFight++)
	{
		printTournamentList();
		system("cls");


		party mainEnemy = *enemiesInTheTournament[currentFight];

		
		// make enemy stronger depending on how many wins the player had
		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			if (mainEnemy.birds[i] == NULL)
				continue;

			mainEnemy.birds[i]->_maxHealth *= int((currentFight / 10.0f) + 1.0f);
			mainEnemy.birds[i]->_attack *= int((currentFight / 10.0f) + 1.0f);
			mainEnemy.birds[i]->_defense *= int((currentFight / 10.0f) + 1.0f);
		}



		arenaClass arenaOfThisFight(plrParty, mainEnemy);
		teamWinner winner = arenaOfThisFight.FIGHT();


		if (winner == ENEMY_WIN)
		{
			system("cls");
			cout << "You lost the battle :(\n";
			cout << "You defeated " << currentFight << " enemies\n";
			cout << "Returning to main menu\n\n";
			system("pause");
			return;
		}



		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			if (plrParty.birds[i] == NULL)
				continue;

			defaultBirdClass* mainBird = plrParty.birds[i];


			// Revives dead birds, and gives a takes away half their max health
			if (plrParty.livingState[i] == DEAD)
			{
				plrParty.livingState[i] = ALIVE;
				mainBird->_maxHealth /= 2;
				mainBird->_health = mainBird->_maxHealth;
			}


			// For the birds that didnt die, decrease their max health by damage taken/2
			else
			{
				// Debuffing max health
				mainBird->_maxHealth -= (mainBird->_maxHealth - mainBird->_health) / 2;


				// Buff the team max health after its been nerfed
				mainBird->_maxHealth += 10;


				// heal bird
				mainBird->_health = mainBird->_maxHealth;
			}

		}




	}

}


void townClass::printTournamentList()
{

	system("cls");

	cout << "Tournament Hall\n";
	cout << "-----------------------\n\n";


	for (int i = 0; i < amountOfEnemies; i++)
	{
		cout << i + 1 << ") ";

		if (i < currentFight)
			cout << "- Defeated -";

		else if (i == currentFight)
			cout << "-> Next up <-";

		else if (i > currentFight)
			cout << "- Awaits -";


		cout << "\n\n";
	}



	cout << "-----------------------\n";

	system("pause");
}


void townClass::makeRandomEnemies()
{
	enemiesInTheTournament = new party * [amountOfEnemies];

	for (int i = 0; i < amountOfEnemies; i++)
	{
		party* newParty = createRandomParty();
		enemiesInTheTournament[i] = newParty;
	}
}


#pragma endregion




#pragma region Loading Custom Fight


void townClass::loadCustomFightInputLoop()
{

	printLoadCustomFightInputLoop();

	bool readyToFight = false;


	while (true)
	{

		if (!_kbhit())
			continue;



		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			if (loadFightCategory == NAMING_FILE_CATEGORY)
				getFileName();

			if (loadFightCategory == CONFIRM_LOAD_CATEGORY)
				readyToFight = checkForValidFile();

		}


		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			return;
		}



		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
				if (loadFightCategory <= 0)
					continue;

				loadFightCategory--;
			}

			else if (keyInput == DOWN_ARROW)
			{
				if (1 <= loadFightCategory)
					continue;

				loadFightCategory++;
			}

		}



		// Initianing the fight if ready
		if (readyToFight)
		{
			fightCustomEnemy();
			return;
		}



		printLoadCustomFightInputLoop();

	}
}


void townClass::printLoadCustomFightInputLoop()
{
	system("cls");

	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Load the file (.txt):\n";
	cout << "-----------------------\n\n";



	cout << " > ";
	if (loadFightCategory == NAMING_FILE_CATEGORY)
		cout << "  ";

	cout << "File Directory: " << fileDirectory << "\n\n";




	cout << " > ";
	if (loadFightCategory == CONFIRM_LOAD_CATEGORY)
		cout << "  ";

	cout << "Confirm?\n\n";


	cout << "-----------------------\n\n";
	cout << "Make sure the names match!\n\n";


	if (couldOpenFile == false)
		cout << "!! COULDN'T FIND/LOAD THE FILE !!\n";
		cout << "!! Make sure you typed .txt at the end !!\n";
}

void townClass::getFileName()
{
	system("cls");
	cout << "File Name:\n";
	getline(cin, fileDirectory);

}

bool townClass::checkForValidFile()
{
	ifstream file(fileDirectory);


	if (file.is_open())
	{
		file.close();
		return true;
	}

	couldOpenFile = false;
	return false;

}

defaultBirdClass* townClass::makeBirdBasedOnSymbol(char birdSymbol)
{
	defaultBirdClass* mainBird = NULL;

	switch (birdSymbol)
	{
	case 'c':
		 mainBird = new ChickenBirdClass();
		 break;
		 
	case 'd':
		mainBird = new DodoBirdClass();
		break;

	case 'e':
		mainBird = new EagleBirdClass();
		break;

	case 'h':
		mainBird = new HummingbirdClass();
		break;

	case 'k':
		mainBird = new KiwiBirdClass();
		break;

	case 'o':
		mainBird = new OstrichBirdClass();
		break;

	case 'O':
		mainBird = new OwlBirdClass();
		break;

	case 'p':
		mainBird = new PenguinBirdClass();
		break;

	case 's':
		mainBird = new ShoebillBirdClass();
		break;

	default:
		makeYellowText();
		break;
	}

	return mainBird;

}

void townClass::fightCustomEnemy()
{

	ifstream file(fileDirectory);


	defaultBirdClass* bird1 = NULL;
	defaultBirdClass* bird2 = NULL;
	defaultBirdClass* bird3 = NULL;



	if (file.is_open())
	{
		string line = "";
		int lineNum = 1;

		while (getline(file, line))
		{
			if (lineNum == 1)
				bird1 = makeBirdBasedOnSymbol(line[0]);
			
			if (lineNum == 2)
				bird2 = makeBirdBasedOnSymbol(line[0]);

			if (lineNum == 3)
				bird3 = makeBirdBasedOnSymbol(line[0]);


			lineNum++;
		}

		file.close();
	}

	else
		makeYellowText();




	party loadedEnemy = createEnemyParty(bird1, bird2, bird3);

	system("cls");
	system("pause");

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		if (loadedEnemy.birds[i] != NULL)
			cout << i + 1 << ") " << loadedEnemy.birds[i]->_name << "\n";

	system("pause");


	arenaClass fightingCustom(plrParty, loadedEnemy);

	fightingCustom.FIGHT();



	// heals player team
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		if (plrParty.birds[i] == NULL)
			continue;

		if (plrParty.livingState[i] == DEAD)
			plrParty.livingState[i] = ALIVE;

		plrParty.birds[i]->_health = plrParty.birds[i]->_maxHealth;


	}


}


#pragma endregion




#pragma region Making Custom Fight


void townClass::makeEnemyInputLoop()
{

	printMakeEnemyInputLoop();



	while (true)
	{

		if (!_kbhit())
			continue;



		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			if (makeFightCategory == NAMING_FILE_CATEGORY)
				getFileName();


			if (makeFightCategory == BIRD_ONE_CATEGORY)
				selectingBirdToAddToParty(0);

			if (makeFightCategory == BIRD_TWO_CATEGORY)
				if (selectedBirdsName[0] != ' ')
					selectingBirdToAddToParty(1);

			if (makeFightCategory == BIRD_THREE_CATEGORY)
				if (selectedBirdsName[1] != ' ')
					selectingBirdToAddToParty(2);


			if (makeFightCategory == CONFIRM_SAVE_CATEGORY)
				if (selectedBirdsName[0] != ' ')
					if (exportCustomFight() == true)
						savedFile = true;

		}


		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			return;
		}



		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
				if (makeFightCategory <= 0)
					continue;

				makeFightCategory--;
			}

			else if (keyInput == DOWN_ARROW)
			{
				if (4 <= makeFightCategory)
					continue;

				makeFightCategory++;
			}

		}



		printMakeEnemyInputLoop();


	}
}


void townClass::printMakeEnemyInputLoop()
{
	system("cls");

	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Load the file (.txt):\n";
	cout << "-----------------------\n\n";



	cout << " > ";
	if (makeFightCategory == NAMING_FILE_CATEGORY)
		cout << "  ";

	cout << "File Directory: " << fileDirectory << "\n\n";



	cout << " > ";
	if (makeFightCategory == BIRD_ONE_CATEGORY)
		cout << "  ";

	cout << "Bird One: " << selectedBirdsName[0] << "\n\n";



	cout << " > ";
	if (makeFightCategory == BIRD_TWO_CATEGORY)
		cout << "  ";

	cout << "Bird Two: " << selectedBirdsName[1] << "\n\n";



	cout << " > ";
	if (makeFightCategory == BIRD_THREE_CATEGORY)
		cout << "  ";

	cout << "Bird Three: " << selectedBirdsName[2] << "\n\n";



	cout << " > ";
	if (makeFightCategory == CONFIRM_SAVE_CATEGORY)
		cout << "  ";

	cout << "Confirm?\n\n";





	cout << "-----------------------\n\n";
	cout << "Your exported file can be found in the project files!\n\n";
	cout << "Also make sure that the first bird exists and dont leave any gaps\n\n";


	if (savedFile == true)
		cout << "!! File Created and Saved !!\n";
}

void townClass::selectingBirdToAddToParty(int index)
{

	printingSelectingBirdToParty();

	while (true)
	{

		if (!_kbhit())
			continue;



		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			if (selectingBirdToMakeCategory == 0)
				selectedBirdsName[index] = 'h';

			else if (selectingBirdToMakeCategory == 1)
				selectedBirdsName[index] = 'k';

			else if (selectingBirdToMakeCategory == 2)
				selectedBirdsName[index] = 'c';

			else if (selectingBirdToMakeCategory == 3)
				selectedBirdsName[index] = 'd';

			else if (selectingBirdToMakeCategory == 4)
				selectedBirdsName[index] = 'e';

			else if (selectingBirdToMakeCategory == 5)
				selectedBirdsName[index] = 'o';

			else if (selectingBirdToMakeCategory == 6)
				selectedBirdsName[index] = 'O';

			else if (selectingBirdToMakeCategory == 7)
				selectedBirdsName[index] = 'p';

			else if (selectingBirdToMakeCategory == 8)
				selectedBirdsName[index] = 's';

			return;
		}


		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			return;
		}



		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
				if (selectingBirdToMakeCategory <= 0)
					continue;

				selectingBirdToMakeCategory--;
			}

			else if (keyInput == DOWN_ARROW)
			{
				if (8 <= selectingBirdToMakeCategory)
					continue;

				selectingBirdToMakeCategory++;
			}

		}



		printingSelectingBirdToParty();


	}


}

void townClass::printingSelectingBirdToParty()
{

	system("cls");

	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Selected your birds:\n";
	cout << "----------------------\n\n";


	for (int i = 0; i < 9; i++)
	{
		cout << "-> ";

		if (selectingBirdToMakeCategory == i)
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

	if (selectingBirdToMakeCategory == 0)
		usedForDescription = new HummingbirdClass();

	else if (selectingBirdToMakeCategory == 1)
		usedForDescription = new KiwiBirdClass();

	else if (selectingBirdToMakeCategory == 2)
		usedForDescription = new ChickenBirdClass();

	else if (selectingBirdToMakeCategory == 3)
		usedForDescription = new DodoBirdClass();

	else if (selectingBirdToMakeCategory == 4)
		usedForDescription = new EagleBirdClass();

	else if (selectingBirdToMakeCategory == 5)
		usedForDescription = new OstrichBirdClass();

	else if (selectingBirdToMakeCategory == 6)
		usedForDescription = new OwlBirdClass();

	else if (selectingBirdToMakeCategory == 7)
		usedForDescription = new PenguinBirdClass();

	else if (selectingBirdToMakeCategory == 8)
		usedForDescription = new ShoebillBirdClass();


	for (int i = 0; i < 3; i++)
		if (usedForDescription != NULL)
			cout << usedForDescription->_description[i] << "\n";

}

bool townClass::exportCustomFight()
{
	fileDirectory += ".txt";


	ofstream file(fileDirectory);

	if (file.is_open())
	{
		file << selectedBirdsName[0] << "\n";
		file << selectedBirdsName[1] << "\n";
		file << selectedBirdsName[2] << "\n";


		file.close();
		return true;
	}
	else
		makeYellowText();



	cout << "SOMETHING HAPPENED!";
	system("pause");
	return false;


}


#pragma endregion