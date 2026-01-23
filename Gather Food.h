#ifndef ABILITY_GATHER_FOOD_H
#define ABILITY_GATHER_FOOD_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Chicken

class gatherFood : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	gatherFood()
		: defaultAbilityClass("Gather Food", 0, 1, STATUS, SELF)
	{
		_description[0] = "Increases offspring quantity";
		_description[1] = "by 1-2 (random)";
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


		// Increasing offspring
		int offspringBuff = rand() % 2 + 1;
		selfParty.statMultipliers[self->_partyIndex].offspringAddon += offspringBuff;
		results += "Offspring quantity increased by " + to_string(offspringBuff) + "|";



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
