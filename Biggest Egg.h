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

	biggestEgg()
		: defaultAbilityClass("Biggest Egg", 0, 0, STATUS, SELF)
	{
		_description[0] = "Decreases Defense by x0.15";
		_description[1] = "But lays twice as many eggs";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " layed the biggest egg |";
		results += "But lost some defense | ";



		// Getting eggs
		int quantityObtained = 0;
		quantityObtained = 2 * (self->_offspringQuantity + selfParty.statMultipliers[self->_partyIndex].offspringAddon);
		selfParty.amountOfEggs += quantityObtained;


		// Decreasing defense
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier -= 0.15f;



		results += "Obtained " + to_string(quantityObtained) + " eggs";

		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
