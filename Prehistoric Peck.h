#ifndef ABILITY_PREHISTORIC_PECK_H
#define ABILITY_PREHISTORIC_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Dodo


class prehistoricPeck : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	prehistoricPeck()
		: defaultAbilityClass("Prehistoric Peck", 15, 2, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "A peck that boost the user";
		_description[1] = "Increases defense and attack";
		_description[2] = "by x0.35";
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


			// Dealing damage and updating decription
			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";



		}


		// Atk missing
		else
			results += "But it missed|";



		// Boosting attack
		results += prehistoricBoost(self, selfParty);



		return results;
	}



	/*
	* Gives the bird the boost
	*
	* @return returns the description of what the boost did
	* @param self - The main bird casting the ability
	* @param selfParty - The caster's party
	*/
	string prehistoricBoost(defaultBirdClass* self, party& selfParty)
	{
		// Boosts the atk and def
		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.35f;

		return "Attack and defense boosted";
	}


};



#endif // !ABILITY_PECK_SPAM_H
