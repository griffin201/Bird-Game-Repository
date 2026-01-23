#pragma once
#include "Town.h"
#include <fstream>



// Constructor for town, assigns plr party as variable
townClass::townClass(party& plrParty)
	:plrParty(plrParty) { }


// Deletes memory allocated for enemies in the tournament
townClass::~townClass()
{
	for (int i = 0; i < amountOfEnemies; i++)
		delete enemiesInTheTournament[i];

	delete enemiesInTheTournament;
}



/*
* Begins the input loop for town
*/
void townClass::townInputLoop()
{

	// Prints the town
	printTownInputLoop();


	// Continues forever no matter what
	while (true)
	{

		// If no input continue
		if (!_kbhit())
			continue;


		// Get keyboard input key
		int keyInput = _getch();




		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			// Confirming tournament category
			if (selectedCategory == TOURNAMENT_CATEGORY)
				playRandomTournament();

			// Confirming switching team category
			if (selectedCategory == RECREATE_PARTY_CATEGORY)
				plrParty = creatingPlayerParty();

			// Confirming loading fight from file category
			if (selectedCategory == LOAD_FIGHT_CATEGORY)
				loadCustomFightInputLoop();

			// Confirming making custom enemy
			if (selectedCategory == MAKE_FIGHT_CATEGORY)
				makeEnemyInputLoop();

		}


		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			// Get arrow key input key
			keyInput = _getch();


			// If arrow key up
			if (keyInput == UP_ARROW)
			{
				// Move the selector up, also checks for bounds
				if (selectedCategory <= 0)
					continue;

				selectedCategory--;
			}

			// If arrow key down
			else if (keyInput == DOWN_ARROW)
			{
				// Move the selector down, also checks for bounds
				if (3 <= selectedCategory)
					continue;

				selectedCategory++;
			}

			// If arrow key left
			else if (keyInput == LEFT_ARROW)
			{
				// Decrease enemy count if selector is in tournament category
				if (selectedCategory != TOURNAMENT_CATEGORY)
					continue;

				if (amountOfEnemies <= 1)
					continue;

				amountOfEnemies--;
			}

			// If arrow key right
			else if (keyInput == RIGHT_ARROW)
			{
				// Increase enemy count if selector is in tournament category
				if (selectedCategory != TOURNAMENT_CATEGORY)
					continue;

				if (30 <= amountOfEnemies)
					continue;

				amountOfEnemies++;
			}

		}




		// Prints the town
		printTownInputLoop();

	}



}



/*
* Prints the town, gets called whenever an input is received
*/
void townClass::printTownInputLoop()
{
	system("cls");

	// Printing headers
	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down / increase or decrease enemy count}\n\n";
	cout << " Select your mode:\n";
	cout << "-------------------\n\n";

	

	// Printing categories, if they are selected, a small space will be made, indicating the selected option
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




	// Prints description for each category
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


/*
* Starts the tournament gamemode
*/
void townClass::playRandomTournament()
{
	// Makes all the enemy parties for the tournament
	makeEnemiesForTournament();


	// For each enemy in the tournament, fight him
	for (currentFight = 0; currentFight < amountOfEnemies; currentFight++)
	{
		// Prints the tournament list before beginning battle
		printTournamentList();
		system("cls");


		// Selects the main party that will fight
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


		// Start up the arena to fight
		arenaClass arenaOfThisFight(plrParty, mainEnemy);
		teamWinner winner = arenaOfThisFight.FIGHT();


		// If the enemy won, end the tournament
		if (winner == ENEMY_WIN)
		{
			system("cls");
			cout << "You lost the battle :(\n";
			cout << "You defeated " << currentFight << " enemies\n";
			cout << "Returning to main menu\n\n";
			system("pause");
			return;
		}



		// Buffs the player party
		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			// Makes sure bird exists
			if (plrParty.birds[i] == NULL)
				continue;


			// Selects the main bird to be buffed
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


/*
* Prints the list of enemies in the tournament
*/
void townClass::printTournamentList()
{
	system("cls");

	// Prints header
	cout << "Tournament Hall\n";
	cout << "-----------------------\n\n";

	
	// Prints the list of all enemies in the tournament
	for (int i = 0; i < amountOfEnemies; i++)
	{
		cout << i + 1 << ") ";

		// Prints their status, if they lost or won
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


/*
* Makes the enemies in the tournament
*/
void townClass::makeEnemiesForTournament()
{
	// Allocates memory depending on the amount of enemies to be fought
	enemiesInTheTournament = new party * [amountOfEnemies];


	// Creates a random party and assigns for every enemy
	for (int i = 0; i < amountOfEnemies; i++)
	{
		party* newParty = createRandomParty();
		enemiesInTheTournament[i] = newParty;
	}
}


#pragma endregion




#pragma region Loading Custom Fight


/*
* Main input loop for loading enemies from file
*/
void townClass::loadCustomFightInputLoop()
{

	// Prints the options
	printLoadCustomFightInputLoop();

	// Turns true when there if the file is valid and pressed confirm
	bool readyToFight = false;


	// Continues until a winner is found or returned by pressing X
	while (true)
	{


		// If no input continue
		if (!_kbhit())
			continue;


		// Get keyboard input
		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			// Confirming to input the file name
			if (loadFightCategory == NAMING_FILE_CATEGORY)
				getFileName();

			// Confirming to fight the enemy in the inputed file
			if (loadFightCategory == CONFIRM_LOAD_CATEGORY)
				readyToFight = checkForValidFile();

		}


		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			// Simply returns to the main town input loop
			return;
		}



		// Going up or down / left or right
		if (keyInput == ARROW_KEYS)
		{
			// Gets arrow keys input
			keyInput = _getch();


			// If input was up key
			if (keyInput == UP_ARROW)
			{
				// Move the selector up
				if (loadFightCategory <= 0)
					continue;

				loadFightCategory--;
			}

			// If input was down key
			else if (keyInput == DOWN_ARROW)
			{
				// Move the selector down
				if (1 <= loadFightCategory)
					continue;

				loadFightCategory++;
			}

		}



		// Initianing the fight if ready
		if (readyToFight)
		{
			// Calls to load enemy party and begin fight, after so, returns to main town input loop
			fightCustomEnemy();
			return;
		}


		// Prints the options
		printLoadCustomFightInputLoop();

	}
}


/*
* Prints the Load Custom Fight options for the input loop
*/
void townClass::printLoadCustomFightInputLoop()
{
	system("cls");

	// Header
	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Load the file (.txt):\n";
	cout << "-----------------------\n\n";


	
	// Depending on the selected category there will be an empty space, indincating the selected option
	cout << " > ";
	if (loadFightCategory == NAMING_FILE_CATEGORY)
		cout << "  ";

	cout << "File Directory: " << fileDirectory << "\n\n";


	cout << " > ";
	if (loadFightCategory == CONFIRM_LOAD_CATEGORY)
		cout << "  ";

	cout << "Confirm?\n\n";



	// Extra info at the bottom
	cout << "-----------------------\n\n";
	cout << "Make sure the names match!\n\n";


	// If file could not be opened
	if (couldOpenFile == false)
		cout << "!! COULDN'T FIND/LOAD THE FILE !!\n";
		cout << "!! Make sure you typed .txt at the end !!\n";
}

/*
* Gets user input to get the file name
*/
void townClass::getFileName()
{
	system("cls");
	cout << "File Name:\n";
	getline(cin, fileDirectory);

}

/*
* Check if the main file directory is valid
*/
bool townClass::checkForValidFile()
{
	// Loads the file
	ifstream file(fileDirectory);


	// If file exists and was opened
	if (file.is_open())
	{
		// Close and return true to indicate there is a file
		file.close();
		return true;
	}


	// Otherwise say that file couldnt be found
	couldOpenFile = false;
	return false;

}

/*
* Transforms the main given symbol for a bird into a bird
* 
* @return returns the bird class assotiated with the given symbol
* @param birdSymbol - The main character symbol for the bird
*/
defaultBirdClass* townClass::makeBirdBasedOnSymbol(char birdSymbol)
{
	// Declares the main bird
	defaultBirdClass* mainBird = NULL;


	// depending on the symbol create a new bird and assign it to main bird
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


	// Return the main bird created
	return mainBird;

}

/*
* Loads the enemy from the file and begins the fight
*/
void townClass::fightCustomEnemy()
{

	// Opens the file
	ifstream file(fileDirectory);


	defaultBirdClass* bird1 = NULL;
	defaultBirdClass* bird2 = NULL;
	defaultBirdClass* bird3 = NULL;



	// If file was opened
	if (file.is_open())
	{
		string line = "";
		int lineNum = 1;

		// Load each bird in the file
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

	// If couldnt open file, make text yellow to indicate error
	else
		makeYellowText();



	// Loads the enemy
	party loadedEnemy = createEnemyParty(bird1, bird2, bird3);

	system("cls");
	system("pause");

	// Tells what birds you will be fighting
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		if (loadedEnemy.birds[i] != NULL)
			cout << i + 1 << ") " << loadedEnemy.birds[i]->_name << "\n";

	system("pause");


	// Begins fight
	arenaClass fightingCustom(plrParty, loadedEnemy);
	fightingCustom.FIGHT();



	// heals player team after battle
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


/*
* Main input loop for making an enemy
*/
void townClass::makeEnemyInputLoop()
{

	// Prints the options
	printMakeEnemyInputLoop();



	// Input loop until X is pressed
	while (true)
	{

		// If no input return
		if (!_kbhit())
			continue;


		// Get keyboard input
		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			// Confirming to name the file
			if (makeFightCategory == NAMING_FILE_CATEGORY)
				getFileName();

			// Confirming to select a bird for slot 1
			if (makeFightCategory == BIRD_ONE_CATEGORY)
				selectingBirdToAddToParty(0);

			// Confirming to select a bird for slot 2
			if (makeFightCategory == BIRD_TWO_CATEGORY)
				if (selectedBirdsName[0] != ' ')
					selectingBirdToAddToParty(1);

			// Confirming to select a bird for slot 3
			if (makeFightCategory == BIRD_THREE_CATEGORY)
				if (selectedBirdsName[1] != ' ')
					selectingBirdToAddToParty(2);

			// Confirming to export the file
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
			// Get arrow keys input
			keyInput = _getch();


			// if up arrow pressed
			if (keyInput == UP_ARROW)
			{
				// Move selector up
				if (makeFightCategory <= 0)
					continue;

				makeFightCategory--;
			}

			// if down arrow pressed
			else if (keyInput == DOWN_ARROW)
			{
				// Move selector down
				if (4 <= makeFightCategory)
					continue;

				makeFightCategory++;
			}

		}



		printMakeEnemyInputLoop();


	}
}


/*
* Prints options and information for making the enemy
*/
void townClass::printMakeEnemyInputLoop()
{
	system("cls");

	// Header
	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Load the file (.txt):\n";
	cout << "-----------------------\n\n";



	// Depending on the selected category there will be an empty space, indincating the selected option
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




	// Extra info at the bottom

	cout << "-----------------------\n\n";
	cout << "Your exported file can be found in the project files!\n\n";
	cout << "Also make sure that the first bird exists and dont leave any gaps\n\n";


	if (savedFile == true)
		cout << "!! File Created and Saved !!\n";
}

/*
* Selects the bird to add to party
* 
* @param index - used the index of the bird to modify in the party
*/
void townClass::selectingBirdToAddToParty(int index)
{

	// Prints the bird options
	printingSelectingBirdToParty();


	// Forever input loop until X or a bird is selected
	while (true)
	{

		// Check for input
		if (!_kbhit())
			continue;


		// Get keyboard input
		int keyInput = _getch();



		// // - Getting Input - // //


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{

			// Confirming what bird they want to add to their party
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
			// Get arrow keys input
			keyInput = _getch();

			
			// Moving the selector up
			if (keyInput == UP_ARROW)
			{
				if (selectingBirdToMakeCategory <= 0)
					continue;

				selectingBirdToMakeCategory--;
			}

			// Moving the selector odnw
			else if (keyInput == DOWN_ARROW)
			{
				if (8 <= selectingBirdToMakeCategory)
					continue;

				selectingBirdToMakeCategory++;
			}

		}



		// Prints the bird options
		printingSelectingBirdToParty();


	}


}

/*
* prints the list of birds to select from
*/
void townClass::printingSelectingBirdToParty()
{

	system("cls");

	// Header
	cout << "{Z - confirm | X - cancell | Arrow Keys - move up or down}\n\n";
	cout << " Selected your birds:\n";
	cout << "----------------------\n\n";


	// Printing the list of all birds
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




	// Printing the description depending on the bird
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

/*
* Exports the custom fight duh
*/
bool townClass::exportCustomFight()
{
	// Automatically adds .txt at the end
	fileDirectory += ".txt";


	// Makes the file
	ofstream file(fileDirectory);

	if (file.is_open())
	{
		// Then adds the birds selected
		file << selectedBirdsName[0] << "\n";
		file << selectedBirdsName[1] << "\n";
		file << selectedBirdsName[2] << "\n";


		file.close();
		return true;
	}

	// This should basically never run
	makeYellowText();
	cout << "SOMETHING HAPPENED!";
	system("pause");
	return false;


}


#pragma endregion