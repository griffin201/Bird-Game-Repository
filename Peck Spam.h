#ifndef ABILITY_PECK_SPAM_H
#define ABILITY_PECK_SPAM_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Hummingbird


class peckSpam : public defaultAbilityClass
{
public:


	/*
	* Sets up the move's stats and description
	*/
	peckSpam()
		: defaultAbilityClass("Peck Spam", 4, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "                       ";
		_description[1] = "Hits the target 3-5 times";
		_description[2] = "Every Hit has a chance to be dodged and crit";
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


		// Peck spam variables
		int amountOfHits = 3 + rand() % 3;	// Amount of hits the move will use
		int amountOfSuccesfullHits = 0;		// Amount of succesfull hits
		int amountOfCrits = 0;				// Amount of crits
		int totalDmg = 0;					// Total damage dealt



		// For each time this move will hit
		for (int i = 0; i < amountOfHits; i++)
		{
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


				// If crit
				if (critValue == 1.5f)
					amountOfCrits++;
				

				// Calculates damage
				int speckDamage = int((_baseAttack * (attackStat / defenseStat)) * critValue);
				totalDmg += speckDamage;
				amountOfSuccesfullHits++;

			}
		}



		// Describes what happened during the amount of hits
		results += "Hit a total of: " + to_string(amountOfHits) + "|";
		results += "Attacks missed: " + to_string(amountOfHits - amountOfSuccesfullHits) + "|";
		results += "Total Criticals: " + to_string(amountOfCrits) + "|";



		// Deals the total damage at once
		results += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")";



		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
