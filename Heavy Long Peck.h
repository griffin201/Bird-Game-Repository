#ifndef ABILITY_HEAVY_LONG_PECK_H
#define ABILITY_HEAVY_LONG_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Shoebill


class heavyLongPeck : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	heavyLongPeck()
		: defaultAbilityClass("Heavy Long Peck", 25, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "High damage and cant miss";
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
	* @param target - The main target getting hit by the ability
	*/
	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		// Initializes the description for the move is used
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";



		// Getting values for dmg
		int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
		float critValue = attemptCrit(criticalChance);
		float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
		float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
		float moveAttackStat = _baseAttack;


		// Calculating total damage
		int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * critValue);



		// If crit
		if (critValue == 1.5f)
			results += "Critical Hit|";


		// Deal the damage
		results += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";





		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
