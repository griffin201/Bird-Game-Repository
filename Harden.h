#ifndef ABILITY_HARDEN_H
#define ABILITY_HARDEN_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Kiwi

class harden : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	harden()
		: defaultAbilityClass("Harden", 0, 1, STATUS, SELF)
	{
		_description[0] = "Boosts defense by x0.25";
		_description[1] = "";
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
		results += "Defense has been increased by x0.25 |";


		// Boosts defense
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.25f;


		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
