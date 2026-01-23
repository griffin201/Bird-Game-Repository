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

	/*
	* Sets up the move's stats and description
	*/
	quickRobery()
		: defaultAbilityClass("Quick Robery", 0, 3, STATUS, SELF)
	{
		_description[0] = "Steal the opposing party's egg";
		_description[1] = "If no eggs are found, this move fails";
		_description[2] = "Steal amoung scales on offpring quantity";
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
		results += self->_name + " steals eggs|";


		// Gets the quantinity to steal the eggs
		int quantityToSteal = self->_offspringQuantity + selfParty.statMultipliers[self->_partyIndex].offspringAddon;



		// If the target party has no eggs, it fails
		if (targetParty.amountOfEggs <= 0)
		{
			results += "But it failed";
			return results;
		}



		int amountOfStolenEggs = 0;


		// If they have less eggs than being stolen
		if (targetParty.amountOfEggs < quantityToSteal)
			amountOfStolenEggs = targetParty.amountOfEggs;
		
		// If they have more or equal to the amount of eggs being stolen
		else
			amountOfStolenEggs = quantityToSteal;



		// Steals the eggs
		targetParty.amountOfEggs -= quantityToSteal;
		selfParty.amountOfEggs += amountOfStolenEggs;
		results += "Stole " + to_string(amountOfStolenEggs) + " eggs";



		// Makes sure target party aint on negatives
		if (targetParty.amountOfEggs < 0)
			targetParty.amountOfEggs = 0;



		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
