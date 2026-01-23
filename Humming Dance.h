#ifndef ABILITY_HUMMING_DANCE_H
#define ABILITY_HUMMING_DANCE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Hummingbird

class hummingDance : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	hummingDance()
		: defaultAbilityClass("Humming Dance", 0, 3, STATUS, SELF)
	{
		_description[0] = "Gain 1 offspring";
		_description[1] = "Increases Dodge by x1.25";
		_description[2] = "Increases attack by x1.25";
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
		results += self->_name + " stats increased |";


		// Buffs the user
		selfParty.statMultipliers[self->_partyIndex].dodgeMultiplier += 0.25f;
		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.25f;
		selfParty.statMultipliers[self->_partyIndex].offspringAddon += 1;



		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
