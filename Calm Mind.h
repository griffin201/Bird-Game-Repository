#ifndef ABILITY_CALM_MIND_H
#define ABILITY_CALM_MIND_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Ostrich

class calmMind : public defaultAbilityClass
{
public:

	/*
	* Sets up the move's stats and description
	*/
	calmMind()
		: defaultAbilityClass("Calm Mind", 0, 1, STATUS, SELF)
	{
		_description[0] = "Increases Defense and Attack by x0.35";
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
		results += self->_name + " found peace in it's mind |";
		results += "Defense and Attack drastically increased | ";


		// Boosts atk and defense
		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.35f;



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
