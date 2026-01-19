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

	hummingDance()
		: defaultAbilityClass("Humming Dance", 0, 3, STATUS, SELF)
	{
		_description[0] = "Gain 1 offspring";
		_description[1] = "Increases Dodge by x1.25";
		_description[2] = "Increases attack by x1.25";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " stats increased |";


		selfParty.statMultipliers[self->_partyIndex].dodgeMultiplier += 0.25f;
		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.25f;
		selfParty.statMultipliers[self->_partyIndex].offspringAddon += 1;



		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
