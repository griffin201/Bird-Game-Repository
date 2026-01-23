#ifndef ABILITY_SNOW_DIVE_H
#define ABILITY_SNOW_DIVE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Penguin


class snowDive : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	snowDive()
		: defaultAbilityClass("Snow Dive", 25, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Deals damage while also";
		_description[1] = "increasing attack and dodge";
		_description[2] = "by x0.25";
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


		// Rolls for dodge
		bool dodgeStatus = attemptDodge(target);



		// If atk hit
		if (dodgeStatus == ATK_HIT)
		{

			// getting values for dmg
			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack;


			// Calculating final damage
			int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * critValue);



			// If its crit
			if (critValue == 1.5f)
				results += "Critical Hit|";



			// Deals the damage
			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";


			// Boosts the user
			selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.25f;
			selfParty.statMultipliers[self->_partyIndex].dodgeMultiplier += 0.25f;
			results += self->_name + "gained a boost in attack and dodge";

		}

		// Atk missing
		else
			results += "But it missed";





		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
