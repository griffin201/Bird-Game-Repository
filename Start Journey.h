#include <conio.h>
#include "allBirds.h"
#include "Essentials.h"
#include "ICS_ConsoleHelper.h"




struct
{

	int birdSelectedIndex[3] = { UNDEFINED, UNDEFINED, UNDEFINED };

	int optionSelected = 1;
	int birdListSelected = 0;

	bool choosingBird = false;

} SGS; // Start Game Struct 





party& creatingPlayerParty()
{
	while (true)
	{

		if (!_kbhit())
			continue;

		int keyInput = _getch();




		// // - Getting Input - // //

		// Pressing z (confirm)
		if (keyInput == Z_KEY)
		{
			if (SGS.choosingBird == true)
			{

			}

			awdadawdwadadadwdawdawdawda


			SGS.birdListSelected = 0;
			choosingBird = true;
		}

		// Pressing x (return)
		if (keyInput == X_KEY)
		{
		}

		// Going up or down
		if (keyInput == ARROW_KEYS)
		{
			keyInput = _getch();

			if (keyInput == UP_ARROW)
			{
			}

			else if (keyInput == DOWN_ARROW)
			{
			}

		}






	}


}


void printPlayerSelectionAndStuffIDK()
{
	system("cls");

	cout << "Selected your birds:\n\n";

	

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

	cout << "Confirm?";
	
}