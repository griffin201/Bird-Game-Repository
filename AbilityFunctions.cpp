#include "AbilityFunctions.h"


/*
* Rolls for crit
* 
* @return returns the multiplier for landing the crit
* @param critChance - The chance of the bird landing a crit
*/
float attemptCrit(int critChance)
{
	int randomValue = rand() % 100 + 1;


	if (randomValue <= critChance)
		return 1.5f;
	else
		return 1.0f;
}


/*
* Rolls for dodging an attack
*
* @return returns wether the bird dodged or not
* @param target - The bird being targeted and the one dodging
*/
bool attemptDodge(defaultBirdClass* target)
{

	// if the target doesnt exist
	if (target == NULL)
		return ATK_DODGED;


	// Picks a random number
	int randomValue = rand() % 100 + 1;


	// If that number is less than target's dodge stat, they dodge
	if (randomValue <= target->_dodgeChance)
		return ATK_DODGED;

	// Otherwise its a hit
	else
		return ATK_HIT;

}
