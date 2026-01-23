#ifndef ABILITY_BIGGEST_EGG_H
#define ABILITY_BIGGEST_EGG_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Ostrich

class biggestEgg : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	biggestEgg()
		: defaultAbilityClass("Biggest Egg", 0, 0, STATUS, SELF)
	{
		_description[0] = "Lays twice as many eggs";
		_description[1] = "but decreases Defense by x0.3";
		_description[2] = "";
	}



	/*
	* Uses the ability - Varies depending on the ability being used
	*
	* @return returns a description of the move
	* @param self - The main bird casting the ability
	* @param selfParty - The caster's party
	* @param targetParty - The target's party
	*/
	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		// Initializes the description for the move is used
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " layed the biggest egg |";
		results += "But lost major defense |";



		// Getting eggs
		int quantityObtained = 0;
		quantityObtained = 2 * (self->_offspringQuantity + selfParty.statMultipliers[self->_partyIndex].offspringAddon);
		selfParty.amountOfEggs += quantityObtained;
		results += "Obtained " + to_string(quantityObtained) + " eggs";


		// Decreasing defense
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier -= 0.3f;




		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
