#ifndef ABILITY_MYSTERIOUS_REST_H
#define ABILITY_MYSTERIOUS_REST_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Owl

class mysteriousRest : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	mysteriousRest()
		: defaultAbilityClass("Mysterious Rest", 0, 1, STATUS, SELF)
	{
		_description[0] = "Rests and gains a random buff by x0.35";
		_description[1] = "If that random buff is offspring";
		_description[2] = "You regain your lost egg from using this move";
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



		// Randomly buff self
		int randDebuff = rand() % 5;


		// randomly buff a stat
		if (randDebuff == 0)
			selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.35f;

		else if (randDebuff == 1)
			selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.35f;

		else if (randDebuff == 2)
			selfParty.statMultipliers[self->_partyIndex].critkMultiplier += 0.35f;

		else if (randDebuff == 3)
			selfParty.statMultipliers[self->_partyIndex].dodgeMultiplier += 0.35f;

		else if (randDebuff == 4)
			selfParty.statMultipliers[self->_partyIndex].offspringAddon += 1;


		// If the buff is offspring
		if (randDebuff == 4)
			selfParty.amountOfEggs += _baseEggPrice;



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
