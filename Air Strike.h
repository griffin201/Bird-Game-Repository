#ifndef ABILITY_AIR_STRIKE_H
#define ABILITY_AIR_STRIKE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Eagle


class airStrike : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	airStrike()
		: defaultAbilityClass("Air Strike", 35, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "High damage attack";
		_description[1] = "Decreases the bird own defense by x0.25";
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


			// Calculates final damage
			int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * critValue);


			// If its crit
			if (critValue == 1.5f)
				results += "Critical Hit|";


			// Deals the damage
			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")";



			// Decreasing defense stat
			selfParty.statMultipliers[self->_partyIndex].defenseMultiplier -= 0.25f;


		}

		// Atk missing
		else
			results += "But it missed";



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
