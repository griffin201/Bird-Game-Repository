#ifndef ABILITY_MORALE_SPEECH_H
#define ABILITY_MORALE_SPEECH_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Kiwi

class moraleSpeech : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	moraleSpeech()
		: defaultAbilityClass("Morale Speech", 0, 3, STATUS, SELF)
	{
		_description[0] = "Boosts team's defense by x0.25";
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
		results += "Team's defense has been increased by x0.25 |";


		// Buffs all of the party's defense
		selfParty.statMultipliers[0].defenseMultiplier += 0.25f;
		selfParty.statMultipliers[1].defenseMultiplier += 0.25f;
		selfParty.statMultipliers[2].defenseMultiplier += 0.25f;


		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
