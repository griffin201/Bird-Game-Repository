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

	gatherFood()
		: defaultAbilityClass("Gather Food", 0, 1, STATUS, SELF)
	{
		_description[0] = "Increases offspring quantity";
		_description[1] = "by 1-2 (random)";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Offspring quantity increased by 1|";


		selfParty.statMultipliers[self->_partyIndex].offspringAddon += rand() % 2 + 1;



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
