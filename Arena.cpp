#pragma once
#include "Arena.h"
#include "ICS_ConsoleHelper.h"




arenaClass::arenaClass(party& playerParty, party& enemyParty)
	: _playerParty(playerParty), _enemyParty(enemyParty)
{
	statMultipliesStruct resetedMultipliers; // All multiplier values are X1.0


	_playerParty.amountOfEggs = 0;

	// Prepares both parties for battle
	for (int i = 0; i < _playerParty.amountOfBirds; i++)
	{
		if (_playerParty.birds[i] == NULL)
			continue;

		_playerParty.birds[i]->_health = _playerParty.birds[i]->_maxHealth;
		_playerParty.birds[i]->_partyIndex = i;
		_playerParty.statMultipliers[i] = resetedMultipliers;
		_playerParty.usedTurns[i] = FREE_TURN;
		_playerParty.livingState[i] = ALIVE;
	}

	for (int i = 0; i < _enemyParty.amountOfBirds; i++)
	{
		if (_enemyParty.birds[i] == NULL)
			continue;

		_enemyParty.birds[i]->_health = _enemyParty.birds[i]->_maxHealth;
		_enemyParty.birds[i]->_partyIndex = i;
		_enemyParty.statMultipliers[i] = resetedMultipliers;
		_enemyParty.livingState[i] = ALIVE;
	}

}

arenaClass::~arenaClass()
{

	// Deleting enemy party
	delete _enemyParty.birds;
	delete _enemyParty.statMultipliers;
	delete _enemyParty.livingState;
}


teamWinner arenaClass::FIGHT()
{
	bool someoneLost = false;

	while (!someoneLost)
	{
		// Setup
		setUpRound();
		printArena();



		// Player Turn
		playerTurn();

		checkForDeaths();
		if (checkForDeadTeam() != NO_WINNERS)
			break;



		// Enemy Turn
		system("pause");

		enemyTurn();

		checkForDeaths();
		if (checkForDeadTeam() != NO_WINNERS)
			break;



		// Increase round count
		_round++;
		system("cls");

	}


	// Finalizing
	system("cls");
	printArena();
	system("pause");

	system("cls");
	return checkForDeadTeam();
}








void arenaClass::setUpRound()
{
	for (int i = 0; i < _playerParty.amountOfBirds; i++)
		_playerParty.usedTurns[i] = FREE_TURN;

	for (int i = 0; i < _enemyParty.amountOfBirds; i++)
		_enemyParty.usedTurns[i] = FREE_TURN;

}


void arenaClass::printArena()
{

	// Initialize some values
	// Get values that will be used in printing
	// Print the values in an order



	// // Initializers / Variables


	// Variables

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	defaultBirdClass* plrBirdSelected = NULL;
	defaultAbilityClass* plrMoveSelected = NULL;
	defaultBirdClass* enemyBirdSelected = NULL;

	string overviewOfPlrBirds[MAX_BIRDS_PER_PARTY] = { "","","" };
	string overviewOfMoves[3] = { "","","" };
	string overviewOfEnemyBirds[MAX_BIRDS_PER_PARTY] = { "","","" };



	// Getting current Bird, Move, and EnemyBird as variables
	if (_playerParty.birds[_birdSelectionIndex] != NULL)

		plrBirdSelected = _playerParty.birds[_birdSelectionIndex];

	if (plrBirdSelected != NULL)
		if (plrBirdSelected->_abilities[_moveSelectionIndex] != NULL)
			plrMoveSelected = plrBirdSelected->_abilities[_moveSelectionIndex];

	if (_enemyParty.birds[_enemiesSelectionIndex] != NULL)
		enemyBirdSelected = _enemyParty.birds[_enemiesSelectionIndex];










	// // Getting values to print // //


	// - Description - //


	// Resetting the values for description
	for (int i = 0; i < 13; i++)
		_selectedDescription[i] = "";
	_selectedDescription[1] = "> Select Something For Info <";


	// Getting description for: Player Bird
	if (plrBirdSelected != NULL and _currentSelection == BIRD_SELECTION)
		changeDescription(plrBirdSelected, PLAYER);

	// Getting description for: Moves
	if (plrBirdSelected != NULL and _currentSelection == MOVE_SELECTION)
		if (plrMoveSelected != NULL)
			changeDescription(plrMoveSelected);

	// Getting description for: Enemy Bird -> inspecting or attacking
	if (enemyBirdSelected != NULL and (_currentSelection == ENEMY_INSPECT or _currentSelection == ENEMY_SELECTION))
		changeDescription(enemyBirdSelected, ENEMY);




	// - Player birds - //
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		cout << makeWhiteText();

		if (_playerParty.birds[i] == NULL)
		{
			overviewOfPlrBirds[i] += makeGrayText() + "        - ";

			if (i == _birdSelectionIndex and _currentSelection == BIRD_SELECTION)
				overviewOfPlrBirds[i] += "  ";

			overviewOfPlrBirds[i] += "~~~~~~~~~~~" + makeWhiteText();
			continue;
		}



		overviewOfPlrBirds[i] = "(" + to_string(_playerParty.birds[i]->_health) + "/" + to_string(_playerParty.birds[i]->_maxHealth) + ")";
		overviewOfPlrBirds[i] += " > ";


		if (i == _birdSelectionIndex and _currentSelection != ENEMY_INSPECT)
			overviewOfPlrBirds[i] += "  ";



		// Check if the bird is available to be used
		if (_playerParty.usedTurns[i] == USED_TURN)
			overviewOfPlrBirds[i] += makeYellowText();
		else if (_playerParty.livingState[i] == DEAD)
			overviewOfPlrBirds[i] += makeGrayText();



		overviewOfPlrBirds[i] += _playerParty.birds[i]->_name + makeWhiteText();

	}

	// - Player Moves - //
	if (plrBirdSelected != NULL) for (int i = 0; i < 3; i++)
	{
		cout << makeWhiteText();


		if (plrBirdSelected->_abilities[i] == NULL)
		{
			overviewOfMoves[i] += makeGrayText() + " - ~~~~~~~~~~~" + makeWhiteText();
			continue;
		}


		overviewOfMoves[i] = "(" + to_string(plrBirdSelected->_abilities[i]->_baseEggPrice) + ")";

		overviewOfMoves[i] += " > ";



		if (i == _moveSelectionIndex)
			overviewOfMoves[i] += "  ";

		if (_playerParty.amountOfEggs < plrBirdSelected->_abilities[i]->_baseEggPrice)
			overviewOfMoves[i] += makeGrayText();

		overviewOfMoves[i] += plrBirdSelected->_abilities[i]->_name + makeWhiteText();

	}

	// - Enemy Birds - //
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		cout << makeWhiteText();

		if (_enemyParty.birds[i] == NULL)
		{
			overviewOfEnemyBirds[i] = makeGrayText() + "        - ";

			if (i == _enemiesSelectionIndex and _currentSelection == ENEMY_SELECTION)
				overviewOfEnemyBirds[i] += "  ";

			overviewOfEnemyBirds[i] += makeGrayText() + " ~~~~~~~~~~~" + makeWhiteText();
			continue;
		}




		overviewOfEnemyBirds[i] = "(" + to_string(_enemyParty.birds[i]->_health) + "/" + to_string(_enemyParty.birds[i]->_maxHealth) + ")";
		overviewOfEnemyBirds[i] += " > ";


		if (_enemiesSelected[i] == SELECTED)
			overviewOfEnemyBirds[i] += "-> ";

		if (_currentSelection == ENEMY_INSPECT and i == _enemiesSelectionIndex)
			overviewOfEnemyBirds[i] += "  ";

		if (_currentSelection == ENEMY_SELECTION and i == _enemiesSelectionIndex)
			overviewOfEnemyBirds[i] += "  ";



		if (_enemyParty.livingState[i] == DEAD)
			overviewOfEnemyBirds[i] += makeGrayText();

		if (_enemyParty.usedTurns[i] == USED_TURN)
			overviewOfEnemyBirds[i] += makeYellowText();

		overviewOfEnemyBirds[i] += _enemyParty.birds[i]->_name + makeWhiteText();

	}





	// // Printing Values // //


	// - Printing Header - //
	cout << "\tYour Team:";
	moveToColumn(54);
	cout << "ROUND: " << _round;
	moveToColumn(94);
	cout << "Enemy Team : \n";
	printSeparatorLines();
	cout << "\n";




	// - Printing Description - //

	// If the last move was a used move, tell description of what happened instead
	if (_lastInputWasMoveUsed == true) for (int i = 0; i < 13; i++)
	{
		moveToColumn(40);

		if (2 <= i and i <= 8)
			cout << _previousTurnSummary[i - 2];

		cout << "\n";

		_lastInputWasMoveUsed = false;
	}


	// If the last move WASNT a used move, tell regular descriptions
	else for (int i = 0; i < 13; i++)
	{

		if (_currentSelection == BIRD_SELECTION)
			cout << " ";

		else if (_currentSelection == MOVE_SELECTION)
			moveToColumn(45);

		else if (_currentSelection == ENEMY_SELECTION or _currentSelection == ENEMY_INSPECT)
			moveToColumn(85);

		cout << _selectedDescription[i];


		cout << "\n";
	}




	// - Printing plr/enemy eggs Header - //
	if (_playerParty.amountOfEggs == 0)
		cout << ICS_INTENSE_RED_TEXT;

	cout << "\n\tYour Eggs: " << _playerParty.amountOfEggs << ICS_INTENSE_WHITE_TEXT;
	moveToColumn(94);
	cout << "Enemy Eggs : " << _enemyParty.amountOfEggs << "\n\n\n";




	// - Printing player birds, moves, and enemy birds - //



	for (int i = 0; i < 3; i++)
	{

		// Plr birds
		moveToColumn(2);
		cout << overviewOfPlrBirds[i];


		// Plr moves
		moveToColumn(48); /// ADDING DESCRIPTION FOR BIRD HERE
		if (_currentSelection == MOVE_SELECTION or _currentSelection == ENEMY_SELECTION or _currentSelection == BIRD_SELECTION)
			cout << overviewOfMoves[i];


		// Enemy birds
		moveToColumn(84);
		cout << overviewOfEnemyBirds[i];


		cout << "\n\n\n";

	}



	printSeparatorLines();
	cout << "{ Z - confirm, X - return, C - Rest Bird, Arrow Keys - Move Cursor }  ";



	// Clear description
	for (int i = 0; i < 7; i++)
		_previousTurnSummary[i] = "";


}





void arenaClass::playerTurn()
{

	bool playerTurn = true;

	bool validInput = false;

	int indexMoving = 0;


	while (playerTurn)
	{
		if (!_kbhit())
			continue;

		int keyInput = _getch();



		// // - Getting Input - // //

		// Pressing x (return)
		if (keyInput == X_KEY)
		{
			indexMoving = MOVING_PREVIOUS_CATEGORY;
			validInput = true;
		}


		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{
			indexMoving = MOVING_NEXT_CATEGORY;
			validInput = true;
		}


		// Pressing c (rest bird)
		if (keyInput == C_KEY)
		{
			indexMoving = RESTING;
			validInput = true;
		}

		// Going up or down, left or right
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
				indexMoving = -1;
				validInput = true;
			}
			else if (keyInput == DOWN_ARROW)
			{
				indexMoving = 1;
				validInput = true;
			}
			else if (keyInput == LEFT_ARROW)
			{
				indexMoving = -2;
				validInput = true;
			}
			else if (keyInput == RIGHT_ARROW)
			{
				indexMoving = 2;
				validInput = true;
			}

		}


		defaultBirdClass* mainBird = _playerParty.birds[_birdSelectionIndex];
		defaultAbilityClass* mainMove = NULL;


		if (mainBird != NULL)
			mainMove = mainBird->_abilities[_moveSelectionIndex];



		// // - Processing Input - // //

		if (_currentSelection == BIRD_SELECTION)
		{

			if (indexMoving == MOVING_NEXT_CATEGORY)
			{
				if (mainBird == NULL)
					continue;

				if (_playerParty.usedTurns[_birdSelectionIndex] == USED_TURN)
					continue;

				if (_playerParty.livingState[_birdSelectionIndex] == DEAD)
					continue;


				_moveSelectionIndex = 0;
				_currentSelection = MOVE_SELECTION;
			}
			else if (indexMoving == MOVING_PREVIOUS_CATEGORY)
			{
				indexMoving = 0;
			}
			else if (indexMoving != RESTING)
			{


				if (indexMoving == 2)
				{
					_currentSelection = ENEMY_INSPECT;
					indexMoving = 0;
					_enemiesSelectionIndex = _birdSelectionIndex;
				}
				else if (indexMoving == -2)
				{
					indexMoving = 0;
					validInput = false;
				}

				_birdSelectionIndex += indexMoving;

				if (_birdSelectionIndex < 0)
					_birdSelectionIndex = 0;
				else if (MAX_BIRDS_PER_PARTY <= _birdSelectionIndex)
					_birdSelectionIndex = MAX_BIRDS_PER_PARTY - 1;

				indexMoving = 0;
			}

		}
		else if (_currentSelection == MOVE_SELECTION)
		{

			if (indexMoving == MOVING_NEXT_CATEGORY)
			{

				// If enough eggs to use move
				if (mainMove->_baseEggPrice <= _playerParty.amountOfEggs)
				{
					_enemiesSelectionIndex = 0;

					for (int i = 0; i < _enemyParty.amountOfBirds; i++)
						_enemiesSelected[i] = NOT_SELECTED;

					_currentSelection = ENEMY_SELECTION;
					indexMoving = 0;
				}

				// if selected move is self
				attackTargetsType type = mainMove->_targetsType;
				if (type == SELF or type == ALL_ALLIES or type == ALL_ENEMIES)
					indexMoving = SELECTED_TARGET;

			}
			else if (indexMoving == MOVING_PREVIOUS_CATEGORY)
			{
				_currentSelection = BIRD_SELECTION;
				indexMoving = 0;
			}
			else
			{
				_moveSelectionIndex += indexMoving;

				if (_moveSelectionIndex < 0)
					_moveSelectionIndex = 0;
				else if (mainBird->_abilityCount <= _moveSelectionIndex)
					_moveSelectionIndex = mainBird->_abilityCount - 1;

				indexMoving = 0;
			}


		}
		else if (_currentSelection == ENEMY_SELECTION)
		{

			if (indexMoving == MOVING_NEXT_CATEGORY)
			{
				if (_enemyParty.birds[_enemiesSelectionIndex] == NULL)
					continue;

				if (_enemyParty.livingState[_enemiesSelectionIndex] == DEAD)
					continue;



				indexMoving = SELECTED_TARGET;
			}
			else if (indexMoving == MOVING_PREVIOUS_CATEGORY)
			{
				if (_enemiesSelected[_enemiesSelectionIndex] == SELECTED)
					_enemiesSelected[_enemiesSelectionIndex] = NOT_SELECTED;

				else
				{
					for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
						_enemiesSelected[j] = NOT_SELECTED;

					_enemiesSelectionIndex = 0;
					_currentSelection = MOVE_SELECTION;
				}

			}
			else
			{
				_enemiesSelectionIndex += indexMoving;



				if (_enemiesSelectionIndex < 0)
					_enemiesSelectionIndex = 0;
				else if (MAX_BIRDS_PER_PARTY <= _enemiesSelectionIndex)
					_enemiesSelectionIndex = MAX_BIRDS_PER_PARTY - 1;
			}


		}
		else if (_currentSelection == ENEMY_INSPECT)
		{

			if (indexMoving == 2)
			{
				indexMoving = 0;
				validInput = false;
			}
			else if (indexMoving == -2)
			{
				_currentSelection = BIRD_SELECTION;
				_birdSelectionIndex = _enemiesSelectionIndex;
				indexMoving = 0;
			}
			else if (indexMoving == MOVING_NEXT_CATEGORY)
				indexMoving = 0;
			else if (indexMoving == MOVING_PREVIOUS_CATEGORY)
				indexMoving = 0;



			_enemiesSelectionIndex += indexMoving;


			if (_enemiesSelectionIndex < 0)
				_enemiesSelectionIndex = 0;
			else if (MAX_BIRDS_PER_PARTY <= _enemiesSelectionIndex)
				_enemiesSelectionIndex = MAX_BIRDS_PER_PARTY - 1;
		}

		else
		{
			cout << "\n\n\n\nA BUG HAPPENED\n\n\n\n\n\n" << ICS_RED_BACKGROUND;
		}





		// // - Resting Move - // //
		if (indexMoving == RESTING)
		{

			if (mainBird == NULL)
				continue;
			if (_playerParty.livingState[_birdSelectionIndex] == DEAD)
				continue;
			if (_playerParty.usedTurns[_birdSelectionIndex] == USED_TURN)
				continue;



			// Rests Bird
			restBird(_playerParty, mainBird, _birdSelectionIndex);


			// Setup for next input
			_moveSelectionIndex = 0;
			_enemiesSelectionIndex = 0;

			_currentSelection = BIRD_SELECTION;

			for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
				_enemiesSelected[i] = NOT_SELECTED;
		}



		// // - Using Move - // //

		// Confirm Using an ability
		if (indexMoving == SELECTED_TARGET)
		{

			// First checking if can use move due to price
			if (_playerParty.amountOfEggs < mainMove->_baseEggPrice)
				continue;




			// Selecting the enemy
			if (_enemiesSelected[_enemiesSelectionIndex] == NOT_SELECTED)
				_enemiesSelected[_enemiesSelectionIndex] = SELECTED;

			// Diselecting the enemy
			else if (_enemiesSelected[_enemiesSelectionIndex] == SELECTED)
				_enemiesSelected[_enemiesSelectionIndex] = NOT_SELECTED;



			int amountOfTargetsMoveCanHit = 0;
			int amountOfSelectedTargets = 0;



			// Getting amount of targets move can hit
			if (mainMove->_targetsType == SELF)
				amountOfTargetsMoveCanHit = 0;

			else if (mainMove->_targetsType == SINGLE_ALLY or mainMove->_targetsType == SINGLE_ENEMY)
				amountOfTargetsMoveCanHit = 1;

			else if (mainMove->_targetsType == TWO_ALLIES or mainMove->_targetsType == TWO_ENEMIES)
				amountOfTargetsMoveCanHit = 2;

			else if (mainMove->_targetsType == ALL_ALLIES or mainMove->_targetsType == ALL_ENEMIES)
				amountOfTargetsMoveCanHit = 0;



			// Getting amount of selected targets
			for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
				if (_enemiesSelected[i] == SELECTED)
					amountOfSelectedTargets++;






			// Checking if player selected enough targets
			if (amountOfTargetsMoveCanHit <= amountOfSelectedTargets)
			{
				// Variable for storing results from move
				string results;


				int indexOfSelected = 0;
				defaultBirdClass* selectedTargets[MAX_BIRDS_PER_PARTY];


				for (int i = 0; i < 3; i++)
				{

					if (_enemiesSelected[i] == SELECTED)
					{
						selectedTargets[indexOfSelected] = _enemyParty.birds[i];
						indexOfSelected++;
					}
					else if (_alliesSelected[i] == SELECTED)
					{
						selectedTargets[indexOfSelected] = _playerParty.birds[i];
						indexOfSelected++;
					}
				}




				// Uses the move
				switch (mainMove->_targetsType)
				{
				case SELF:
				case ALL_ALLIES:
				case ALL_ENEMIES:
					results = mainMove->useAbility(mainBird, _playerParty, _enemyParty);
					break;

				case SINGLE_ENEMY:
				case SINGLE_ALLY:
					results = mainMove->useAbility(mainBird, _playerParty, _enemyParty, selectedTargets[0]);
					break;

				case TWO_ALLIES:
				case TWO_ENEMIES:
					results = mainMove->useAbility(mainBird, _playerParty, _enemyParty, selectedTargets[0], selectedTargets[1]);
					break;

				default:
					cout << ICS_RED_BACKGROUND;
					break;
				}



				// Check if anyone died
				checkForDeaths();




				// Turns "results" into description
				turnResultsIntoDescription(results);




				// Setup for next input
				_lastInputWasMoveUsed = true;
				_playerParty.amountOfEggs -= mainMove->_baseEggPrice;

				_playerParty.usedTurns[_birdSelectionIndex] = USED_TURN;
				_moveSelectionIndex = 0;
				_enemiesSelectionIndex = 0;

				_currentSelection = BIRD_SELECTION;

				for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
					_enemiesSelected[i] = NOT_SELECTED;

			}



		}







		// // - Checking if turn ended - // //

		// Check if all birds have played
		bool allBirdsPlayed = true;

		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			if (_playerParty.birds[i] == NULL)
				continue;

			if (_playerParty.livingState[i] == DEAD)
				continue;

			if (_playerParty.usedTurns[i] == USED_TURN)
				continue;

			allBirdsPlayed = false;
		}

		if (allBirdsPlayed)
			playerTurn = false;



		// Check if enemy team is dead
		checkForDeaths();
		teamWinner winnerOfBattle = checkForDeadTeam();

		if (winnerOfBattle != NO_WINNERS)
			break;








		// Prevents the screen from blinking every time you press something
		if (validInput)
		{
			validInput = false;
			system("cls");
			printArena();
			continue;
		}


	}


}


void arenaClass::enemyTurn()
{
	// Enemy AI Here

	/*
	* First Step is to check egg count
	*		if 0 then use the best bird for resting, and rest
	*
	*
	* for each bird (the order in which they go will be random)
	*
	*
	* 1. Check egg count
	*		if 0 or cant use any move then rest
	*
	*
	* 2. Use a random affordable move
	*
	*/


	// Check egg count
	if (_enemyParty.amountOfEggs <= 0)
	{
		// Check best bird for resting
		int bestBirdForRestingIndex = 0;



		for (int i = 0; i < _enemyParty.amountOfBirds; i++)
		{
			if (_enemyParty.birds[i] == NULL)
				continue;

			if (_enemyParty.livingState[i] == DEAD)
				continue;

			if (_enemyParty.usedTurns[i] == USED_TURN)
				continue;



			int potentialOfRandomBird = _enemyParty.birds[i]->_offspringQuantity + _enemyParty.statMultipliers[i].offspringAddon;
			int potentialOfSelected = _enemyParty.birds[bestBirdForRestingIndex]->_offspringQuantity + _enemyParty.statMultipliers[i].offspringAddon;

			// If there is a better bird at producing eggs, select it
			if (potentialOfSelected < potentialOfRandomBird)
				bestBirdForRestingIndex = i;

			// If they are the same at producing, select a random one
			else if (potentialOfSelected == potentialOfRandomBird and rand() % 2 == 1)
				bestBirdForRestingIndex = i;

			// If this bird is worst at producin eggs, do nothin
		}





		// Resting
		
		if (_enemyParty.livingState[bestBirdForRestingIndex] != DEAD)
		{
			defaultBirdClass* mainBird = _enemyParty.birds[bestBirdForRestingIndex];
			restBird(_enemyParty, mainBird, bestBirdForRestingIndex);

			system("cls");
			printArena();
			system("pause");
		}
	}



	// Random Order The Enemy will use their birds
	int orderOfPlay[MAX_BIRDS_PER_PARTY] = { UNDEFINED, UNDEFINED, UNDEFINED };

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		int randIndex = rand() % 3;

		if (orderOfPlay[randIndex] == UNDEFINED)
			orderOfPlay[randIndex] = i;
		else
			i--;
	}

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		if (orderOfPlay[i] == UNDEFINED)
			orderOfPlay[i] = 0;




	// Plays the birds in the chosen random order
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		int indexOfMainBird = orderOfPlay[i];


		// Check if the bird is real
		if (_enemyParty.birds[indexOfMainBird] == NULL)
			continue;

		// Check if the bird hasn't used any moves
		if (_enemyParty.usedTurns[indexOfMainBird] == USED_TURN)
			continue;

		// Check if the bird isnt dead
		if (_enemyParty.livingState[indexOfMainBird] == DEAD)
			continue;



		defaultBirdClass* mainBird = _enemyParty.birds[indexOfMainBird];



		// Check if can use any move
		bool canUseAnyMove = false;

		for (int j = 0; j < mainBird->_abilityCount; j++)
		{
			if (mainBird->_abilities[j]->_baseEggPrice <= _enemyParty.amountOfEggs)
			{
				canUseAnyMove = true;
				break;
			}
		}


		// Rest if unable to use any moves
		if (canUseAnyMove == false)
		{
			// This time we dont check for the best bird to rest, because he may not be available

			// Resting
			restBird(_enemyParty, mainBird, indexOfMainBird);

			system("cls");
			printArena();
			system("pause");

			_enemyParty.usedTurns[indexOfMainBird] = USED_TURN;

			continue;
		}







		// // - USING MOVE - // //

		// Pick a random move that is affordable
		defaultAbilityClass* mainMove = NULL;

		do
		{
			mainMove = mainBird->_abilities[rand() % 3];
		} while (_enemyParty.amountOfEggs < mainMove->_baseEggPrice);





		string results = "";


		// Using SELF ability
		if (mainMove->_targetsType == SELF)
		{
			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty);
		}



		// Uing SINGLE ALLY ability
		else if (mainMove->_targetsType == SINGLE_ALLY)
		{
			// Get random bird from party
			int target = UNDEFINED;

			do
			{
				target = rand() % 3;
			} while (_playerParty.livingState[target] == DEAD or _playerParty.birds[target] == NULL);


			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty, _playerParty.birds[target]);
		}


		// Using TWO ALLIES ability
		else if (mainMove->_targetsType == TWO_ALLIES)
		{
			// Target indexes
			int target1 = UNDEFINED;
			int target2 = UNDEFINED;



			// Get how many temates are alive
			int amountOfAlliesAlive = 0;
			for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
				if (_enemyParty.livingState[j] == ALIVE and _enemyParty.birds[j] != NULL)
					amountOfAlliesAlive++;



			// Depending on how many teamates are alive, do different stuff...
			if (amountOfAlliesAlive == 1)
			{
				// Set self as the target
				target1 = indexOfMainBird;
				target2 = target1;
			}

			else if (amountOfAlliesAlive == 2)
			{
				// Set one as self, and the other livin bird
				target1 = indexOfMainBird;

				for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
					if (_enemyParty.livingState[j] == ALIVE and _enemyParty.birds[j] != NULL and target1 != j)
						target2 = j;

			}

			else if (amountOfAlliesAlive == 3)
			{
				// Get any random targets
				int target1 = rand() % MAX_BIRDS_PER_PARTY;
				int target2 = rand() % MAX_BIRDS_PER_PARTY;

				// Make sure they are not the same
				while (target1 == target2)
					target2 = rand() % MAX_BIRDS_PER_PARTY;
			}




			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty, _playerParty.birds[target1], _playerParty.birds[target2]);
		}


		// Using ALL ALLIES ability
		else if (mainMove->_targetsType == ALL_ALLIES)
		{
			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty);
		}



		// Using SINGLE ENEMY ability
		else if (mainMove->_targetsType == SINGLE_ENEMY)
		{
			// Pick the target that will take the most dmg
			int weakestPlrBirdIndex = 0;
			int highestDmgForATarget = 0;

			for (int z = 0; z < _playerParty.amountOfBirds; z++)
			{
				if (_playerParty.birds[z] == NULL)
					continue;

				if (_playerParty.livingState[z] == DEAD)
					continue;



				defaultBirdClass* mainTarget = _playerParty.birds[z];

				int finalDamage = int(((float)mainMove->_baseAttack * ((float)mainBird->_attack / (float)mainTarget->_defense)));


				if (highestDmgForATarget < finalDamage)
				{
					weakestPlrBirdIndex = z;
					highestDmgForATarget = finalDamage;
				}

				// Prevents enemy from always picking the first bird
				else if (highestDmgForATarget == finalDamage)
				{

					int randChanceToSwapTargets = rand() % 2;

					if (randChanceToSwapTargets == 1)
					{
						weakestPlrBirdIndex = z;
						highestDmgForATarget = finalDamage;
					}
				}

			}


			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty, _playerParty.birds[weakestPlrBirdIndex]);

		}


		// Using TWO ENEMIES ability
		else if (mainMove->_targetsType == TWO_ENEMIES)
		{

			// Pick random targets
			int target1 = UNDEFINED;
			int target2 = UNDEFINED;


			int amountOfPlrPartyMembersAlive = 0;

			for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
				if (_playerParty.livingState[j] == ALIVE and _playerParty.birds[j] != NULL)
					amountOfPlrPartyMembersAlive++;



			if (amountOfPlrPartyMembersAlive == 1)
			{
				// Get the first target available
				for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
					if (_playerParty.livingState[j] == ALIVE and _playerParty.birds[j] != NULL)
						target1 = j;


				target2 = target1;
			}

			else if (amountOfPlrPartyMembersAlive == 2)
			{
				// Get the first two targets available
				for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
					if (_playerParty.livingState[j] == ALIVE and _playerParty.birds[j] != NULL)
						target1 = j;

				for (int j = 0; j < MAX_BIRDS_PER_PARTY; j++)
					if (_playerParty.livingState[j] == ALIVE and _playerParty.birds[j] != NULL and target1 != j)
						target2 = j;

			}

			else if (amountOfPlrPartyMembersAlive == 3)
			{
				// Get any random targets
				int target1 = rand() % MAX_BIRDS_PER_PARTY;
				int target2 = rand() % MAX_BIRDS_PER_PARTY;

				// Make sure they are not the same
				while (target1 == target2)
					target2 = rand() % MAX_BIRDS_PER_PARTY;
			}




			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty, _playerParty.birds[target1], _playerParty.birds[target2]);

		}


		// Using ALL ENEMIES ability
		else if (mainMove->_targetsType == ALL_ENEMIES)
		{

			// Use the move
			results = mainMove->useAbility(mainBird, _enemyParty, _playerParty);

		}




		// Stuff that happens after using the move
		turnResultsIntoDescription(results);

		_enemyParty.amountOfEggs -= mainMove->_baseEggPrice;
		_lastInputWasMoveUsed = true;
		_enemyParty.usedTurns[indexOfMainBird] = USED_TURN;



		// Check if a team is dead
		checkForDeaths();
		teamWinner winnerOfBattle = checkForDeadTeam();


		if (winnerOfBattle != NO_WINNERS)
			break;


		system("cls");
		printArena();
		system("pause");

	}


}






void arenaClass::restBird(party& mainParty, defaultBirdClass* mainBird, int indexInParty)
{
	// Resting Variables
	int totalGained = mainBird->_offspringQuantity + mainParty.statMultipliers[indexInParty].offspringAddon;



	// Setting description up
	_previousTurnSummary[0] = mainBird->_name + " Rested!";
	_previousTurnSummary[1] = "Layed " + to_string(totalGained) + " Eggs";
	_previousTurnSummary[2] = to_string(mainParty.amountOfEggs) + " --> " + to_string(mainParty.amountOfEggs + totalGained);



	// Getting eggs from resting
	mainParty.amountOfEggs += totalGained;



	// Setup for next enemy action
	_lastInputWasMoveUsed = true;
	mainParty.usedTurns[indexInParty] = USED_TURN;

}



void arenaClass::turnResultsIntoDescription(string results)
{
	for (int i = 0; i < 6; i++)
	{
		int indexToBend = results.find_first_of("|");

		_previousTurnSummary[i] = results.substr(0, indexToBend);
		results.erase(0, indexToBend);

		if (results[0] == '|')
			results.erase(0, 1);

		_previousTurnSummary[i + 1] = results;

	}
}

void arenaClass::changeDescription(defaultBirdClass* bird, teamSide team)
{
	for (int i = 0; i < 13; i++)
		_selectedDescription[i] = "";

	// Setup
	string eggsMultiplier, atkMultipler, defMultiplier, critMultiplier, dodgeMultiplier = "";

	party* mainParty = NULL;

	if (team == PLAYER)
		mainParty = &_playerParty;
	else if (team == ENEMY)
		mainParty = &_enemyParty;

	statMultipliesStruct& stats = mainParty->statMultipliers[bird->_partyIndex];

	if (stats.offspringAddon != 0)
		eggsMultiplier = " + " + to_string(stats.offspringAddon);

	if (stats.attackMultiplier != 1.0f)
		atkMultipler = " x " + to_string(stats.attackMultiplier).substr(0, 3);

	if (stats.defenseMultiplier != 1.0f)
		defMultiplier = " x " + to_string(stats.defenseMultiplier).substr(0, 3);

	if (stats.critkMultiplier != 1.0f)
		critMultiplier = " x " + to_string(stats.critkMultiplier).substr(0, 3);

	if (stats.dodgeMultiplier != 1.0f)
		dodgeMultiplier = " x " + to_string(stats.dodgeMultiplier).substr(0, 3);






	_selectedDescription[1] = "      " + bird->_name;


	_selectedDescription[3] = "   HP: " + to_string(bird->_health) + "/" + to_string(bird->_maxHealth);

	_selectedDescription[4] = " Eggs: " + to_string(bird->_offspringQuantity) + eggsMultiplier;

	_selectedDescription[5] = "  Atk: " + to_string(bird->_attack) + atkMultipler;

	_selectedDescription[6] = "  Def: " + to_string(bird->_defense) + defMultiplier;

	_selectedDescription[7] = " Crit: " + to_string(bird->_critChance) + "%" + critMultiplier;

	_selectedDescription[8] = "Dodge: " + to_string(bird->_dodgeChance) + "%" + dodgeMultiplier;




	//_selectedDescription[11] = bird->_description[0];
	//_selectedDescription[12] = bird->_description[1];
	//_selectedDescription[13] = bird->_description[2];
}

void arenaClass::changeDescription(defaultAbilityClass* ability)
{

	for (int i = 0; i < 13; i++)
		_selectedDescription[i] = "";

	string atkType = "";
	string amountOfTargets = "";


	if (ability->_type == OFFENSIVE)
		atkType = "Offensive";
	else
		atkType = "Status";


	if (ability->_targetsType == SINGLE_ENEMY)
		amountOfTargets = "1 Enemy";
	else if (ability->_targetsType == SINGLE_ALLY)
		amountOfTargets = "1 Ally";
	else if (ability->_targetsType == TWO_ENEMIES)
		amountOfTargets = "2 Enemy";
	else if (ability->_targetsType == TWO_ALLIES)
		amountOfTargets = "2 Ally";
	else if (ability->_targetsType == ALL_ENEMIES)
		amountOfTargets = "3 Enemy";
	else if (ability->_targetsType == ALL_ALLIES)
		amountOfTargets = "3 Ally";
	else if (ability->_targetsType == SELF)
		amountOfTargets = "Self";



	_selectedDescription[1] = "  ---- " + ability->_name + " ----";


	_selectedDescription[3] = "  Power: " + to_string(ability->_baseAttack);

	_selectedDescription[4] = "   Type: " + atkType;

	_selectedDescription[5] = "Targets: " + amountOfTargets;


	_selectedDescription[7] = ability->_description[0];
	_selectedDescription[8] = ability->_description[1];
	_selectedDescription[9] = ability->_description[2];
}




void arenaClass::checkForDeaths()
{
	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		if (_enemyParty.birds[i] != NULL)
		{
			// Awarding for knocking out enemy bird
			if (_enemyParty.birds[i]->_health <= 0 and _enemyParty.livingState[i] == ALIVE)
				_playerParty.amountOfEggs++;



			if (_enemyParty.birds[i]->_health <= 0 or _enemyParty.livingState[i] == DEAD)
			{
				_enemyParty.livingState[i] = DEAD;
				_enemyParty.birds[i]->_health = 0;
			}
		}


		if (_playerParty.birds[i] != NULL)
		{
			// Awarding for knocking out plr bird
			if (_playerParty.birds[i]->_health <= 0 and _playerParty.livingState[i] == ALIVE)
				_enemyParty.amountOfEggs++;



			if (_playerParty.birds[i]->_health <= 0 or _playerParty.livingState[i] == DEAD)
			{
				_playerParty.livingState[i] = DEAD;
				_playerParty.birds[i]->_health = 0;
			}
		}


	}
}

teamWinner arenaClass::checkForDeadTeam()
{
	bool allOfPlrTeamDead = true;
	bool allOfAiTeamDead = true;

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
	{
		if (_playerParty.livingState[i] == ALIVE)
			allOfPlrTeamDead = false;

		if (_enemyParty.livingState[i] == ALIVE)
			allOfAiTeamDead = false;
	}


	if (allOfPlrTeamDead == true)
		return ENEMY_WIN;

	if (allOfAiTeamDead == true)
		return PLAYER_WIN;

	return NO_WINNERS;
}











defaultBirdClass* getRandomBirdForEnemyParty(string birdName)
{
	int randBird = rand() % 9;
	defaultBirdClass* mainBird = NULL;


	switch (randBird)
	{
	case 0:
		mainBird = new HummingbirdClass(birdName);
		break;

	case 1:
		mainBird = new OwlBirdClass(birdName);
		break;

	case 2:
		mainBird = new OstrichBirdClass(birdName);
		break;

	case 3:
		mainBird = new EagleBirdClass(birdName);
		break;

	case 4:
		mainBird = new PenguinBirdClass(birdName);
		break;

	case 5:
		mainBird = new DodoBirdClass(birdName);
		break;

	case 6:
		mainBird = new KiwiBirdClass(birdName);
		break;

	case 7:
		mainBird = new ShoebillBirdClass(birdName);
		break;

	case 8:
		mainBird = new ChickenBirdClass(birdName);
		break;

	default:
		cout << ICS_RED_BACKGROUND;
		break;
	}

	return mainBird;
}


party createPlayerParty(defaultBirdClass* birdOne, defaultBirdClass* birdTwo, defaultBirdClass* birdThree)
{
	party plrParty;

	if (birdOne != NULL and birdTwo != NULL and birdThree != NULL)
		plrParty.amountOfBirds = 3;
	else if (birdOne != NULL and birdTwo != NULL)
		plrParty.amountOfBirds = 2;
	else if (birdOne != NULL)
		plrParty.amountOfBirds = 1;
	else
		cout << "BIRDONE DOESNT EXIST?????";


	plrParty.birds = new defaultBirdClass * [MAX_BIRDS_PER_PARTY];
	plrParty.livingState = new livingStatus[MAX_BIRDS_PER_PARTY];
	plrParty.statMultipliers = new statMultipliesStruct[MAX_BIRDS_PER_PARTY];


	plrParty.birds[0] = birdOne;
	plrParty.birds[1] = birdTwo;
	plrParty.birds[2] = birdThree;

	return plrParty;
}

party createEnemyParty(defaultBirdClass* birdOne, defaultBirdClass* birdTwo, defaultBirdClass* birdThree)
{
	party enemyParty;
	statMultipliesStruct resetedStats;



	// Allocate memory for the arrays
	enemyParty.birds = new defaultBirdClass * [MAX_BIRDS_PER_PARTY];
	enemyParty.livingState = new livingStatus[MAX_BIRDS_PER_PARTY];
	enemyParty.statMultipliers = new statMultipliesStruct[MAX_BIRDS_PER_PARTY];

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		enemyParty.birds[i] = NULL;




	// If birds were provided, use them //

	if (birdOne != NULL)
	{
		enemyParty.amountOfBirds = 1;
		enemyParty.birds[0] = birdOne;
	}
	if (birdTwo != NULL)
	{
		enemyParty.amountOfBirds = 2;
		enemyParty.birds[1] = birdTwo;
	}
	if (birdThree != NULL)
	{
		enemyParty.amountOfBirds = 3;
		enemyParty.birds[2] = birdThree;
	}


	for (int i = 0; i < enemyParty.amountOfBirds; i++)
	{
		enemyParty.birds[i]->_health = enemyParty.birds[i]->_maxHealth;
		enemyParty.statMultipliers[i] = resetedStats;
		enemyParty.livingState[i] = ALIVE;
	}


	if (enemyParty.amountOfBirds != 0)
		return enemyParty;




	cout << makeYellowText();
	return enemyParty;
}

party* createRandomParty()
{

	party* randomParty = new party;
	statMultipliesStruct resetedStats;


	// Allocate memory for the arrays
	randomParty->birds = new defaultBirdClass * [MAX_BIRDS_PER_PARTY];
	randomParty->livingState = new livingStatus[MAX_BIRDS_PER_PARTY];
	randomParty->statMultipliers = new statMultipliesStruct[MAX_BIRDS_PER_PARTY];

	for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		randomParty->birds[i] = NULL;


	

	randomParty->amountOfBirds = rand() % 3 + 1;

	for (int i = 0; i < randomParty->amountOfBirds; i++)
	{
		randomParty->birds[i] = getRandomBirdForEnemyParty(RANDOM_NAMES_FOR_AI_BIRDS[rand() % NUMBER_OF_RANDOM_NAMES]);

		randomParty->birds[i]->_health = randomParty->birds[i]->_maxHealth;
		randomParty->statMultipliers[i] = resetedStats;
		randomParty->livingState[i] = ALIVE;
	}

	return randomParty;
}


void printSeparatorLines()
{
	for (int i = 0; i < 30; i++)
		cout << "-";
	for (int i = 0; i < 20; i++)
		cout << " ";
	for (int i = 0; i < 15; i++)
		cout << "-";
	for (int i = 0; i < 20; i++)
		cout << " ";
	for (int i = 0; i < 35; i++)
		cout << "-";
}

int getConsoleWidth() {
	// Returns the console window size in character.
	// "I CAN HANDLE 67 CHARACTERS BEFORE I NEED TO WRAP THE TEXT"

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void moveToColumn(int col)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		for (int i = 0, end = csbi.dwCursorPosition.X; i < col - end; i++)
			cout << " ";
}


string makeGrayText()
{
	return ICS_textColor(100, 100, 100);
}

string makeYellowText()
{
	return ICS_textColor(200, 200, 10);
}

string makeWhiteText()
{
	return ICS_INTENSE_WHITE_TEXT;
}

