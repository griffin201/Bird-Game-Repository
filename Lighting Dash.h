#ifndef ABILITY_LIGHTING_DASH_H
#define ABILITY_LIGHTING_DASH_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Ostrich
// - Eagle


class lightingDash : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	lightingDash()
		: defaultAbilityClass("Lighting Dash", 20, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "the bird aims for the target's heart";
		_description[1] = "Resulting in high critical ratio";
		_description[2] = "Small chance to boost critical stat";
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
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";



			// Buffs self
			results += randomlyBuffSelf(selfParty, self->_partyIndex);

		}

		// Atk missing
		else
			results += "But it missed";



		return results;
	}



	/*
	* Chance to randomly buff crit multiplier
	*
	* @return returns a description of the move
	* @param selfParty - The caster's party
	* @param targetIndex - The target's party index
	*/
	string randomlyBuffSelf(party& selfParty, int targetIndex)
	{
		// 20% chance to buff crit stat
		int chanceToDebuff = rand() % 5;


		// if no buff
		if (chanceToDebuff != 0)
			return "";


		// If buff, buff
		selfParty.statMultipliers[targetIndex].critkMultiplier += 0.25f;


		return "Critical Stat Increased";
	}

};



#endif // !ABILITY_PECK_SPAM_H
