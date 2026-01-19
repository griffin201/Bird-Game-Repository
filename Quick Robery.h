#ifndef ABILITY_QUICK_ROBERY_H
#define ABILITY_QUICK_ROBERY_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Hummingbird


class quickRobery : public defaultAbilityClass
{
public:

	quickRobery()
		: defaultAbilityClass("Quick Robery", 0, 3, STATUS, SELF)
	{
		_description[0] = "Steal the opposing party's egg";
		_description[1] = "If no eggs are found, this move fails";
		_description[2] = "Steal amoung scales on offpring quantity";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " steals eggs|";


		int quantityToSteal = self->_offspringQuantity + selfParty.statMultipliers[self->_partyIndex].offspringAddon;



		if (targetParty.amountOfEggs <= 0)
		{
			results += "But it failed";
			return results;
		}


		
		int amountOfStolenEggs = 0;


		if (targetParty.amountOfEggs < quantityToSteal)
			amountOfStolenEggs = targetParty.amountOfEggs;
		else
			amountOfStolenEggs = quantityToSteal;


		targetParty.amountOfEggs -= quantityToSteal;

		selfParty.amountOfEggs += amountOfStolenEggs;

		results += "Stole " + to_string(amountOfStolenEggs) + " eggs";


		if (targetParty.amountOfEggs < 0)
			targetParty.amountOfEggs = 0;


		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
