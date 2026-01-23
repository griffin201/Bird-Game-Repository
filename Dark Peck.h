#ifndef ABILITY_DARK_PECK_H
#define ABILITY_DARK_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Owl


class darkPeck : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	darkPeck()
		: defaultAbilityClass("Dark Peck", 10, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		// Description of bird
		_description[0] = "Attack scales on how many unique debuffs target has";
		_description[1] = "it becomes weaker if target has buffs";
		_description[2] = "Chance to randomly debuff target";
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

			// Exclussives to dark peck
			float darkPeckMultiplier = getDarkPeckMultiplier(targetParty, target->_partyIndex);



			// getting values for dmg
			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);

			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack * darkPeckMultiplier;



			// Calculates final damage
			int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * critValue);



			// If its crit
			if (critValue == 1.5f)
				results += "Critical Hit|";



			// Deals the damage
			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";


			results += randomlyDebuffTarget(targetParty, target->_partyIndex);

		}

		// Atk missing
		else
			results += "But it missed";



		// Returning the description
		return results;
	}



	/*
	* calculates the total multiplier depending the target's stat multipliers
	*
	* @return returns the multiplier for the ability
	* @param targetParty - The target's party
	* @param targetIndex - The target's party index
	*/
	float getDarkPeckMultiplier(party& targetParty, int targetIndex)
	{
		float totalMultiplier = 1.0f;


		// Attack stat
		if (targetParty.statMultipliers[targetIndex].attackMultiplier < 1.0f)
			totalMultiplier += 0.5f;
		else if (targetParty.statMultipliers[targetIndex].attackMultiplier > 1.0f)
			totalMultiplier -= 0.5f;

		// Defense stat
		if (targetParty.statMultipliers[targetIndex].defenseMultiplier < 1.0f)
			totalMultiplier += 0.5f;
		else if (targetParty.statMultipliers[targetIndex].defenseMultiplier > 1.0f)
			totalMultiplier -= 0.5f;


		// Crit stat
		if (targetParty.statMultipliers[targetIndex].critkMultiplier < 1.0f)
			totalMultiplier += 0.5f;
		else if (targetParty.statMultipliers[targetIndex].critkMultiplier > 1.0f)
			totalMultiplier -= 0.5f;

		// Dodge stat
		if (targetParty.statMultipliers[targetIndex].dodgeMultiplier < 1.0f)
			totalMultiplier += 0.5f;
		else if (targetParty.statMultipliers[targetIndex].dodgeMultiplier > 1.0f)
			totalMultiplier -= 0.5f;


		// makes sure the attack doesnt go to negatives, or else the target is healed
		if (totalMultiplier < 0.1f)
			totalMultiplier = 0.1f;


		return totalMultiplier;
	}



	/*
	* Rolls for decreasing debuff, if not debuff, then no debuff
	*
	* @return returns a text wether or not the debuff was true
	* @param targetParty - The target's party
	* @param targetIndex - The target's party index
	*/
	string randomlyDebuffTarget(party& targetParty, int targetIndex)
	{
		// 25% to debuff a random stat from target
		int chanceToDebuff = rand() % 4;

		if (chanceToDebuff != 0)
			return "";

		// Atk, def, crit, dodge
		int randStatToDebuff = rand() % 4;

		
		// atk Stat reduction
		if (randStatToDebuff == 0)
			targetParty.statMultipliers[targetIndex].attackMultiplier -= 0.15f;

		// def Stat reduction
		else if (randStatToDebuff == 2)
			targetParty.statMultipliers[targetIndex].defenseMultiplier -= 0.15f;

		// crit Stat reduction
		else if (randStatToDebuff == 3)
			targetParty.statMultipliers[targetIndex].critkMultiplier -= 0.15f;

		// dodge Stat reduction
		else if (randStatToDebuff == 4)
			targetParty.statMultipliers[targetIndex].dodgeMultiplier -= 0.15f;


		return "Target's stats decreased";
	}

};



#endif // !ABILITY_PECK_SPAM_H
