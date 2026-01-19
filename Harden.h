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

	harden()
		: defaultAbilityClass("Harden", 0, 1, STATUS, SINGLE_ALLY)
	{
		_description[0] = "Boosts defense by x0.25";
		_description[1] = "";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Defense has been increased by x0.25 |";


		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.25f;


		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
