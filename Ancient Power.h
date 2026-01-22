#ifndef ABILITY_ANCIENT_POWER_H
#define ABILITY_ANCIENT_POWER_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Dodo


class ancientPower : public defaultAbilityClass
{
public:

	ancientPower()
		: defaultAbilityClass("Ancient Power", 15, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Deals damage while having a 25%";
		_description[1] = "To boost all stats by x0.35";
		_description[2] = "and offspring by +1";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		bool dodgeStatus = attemptDodge(target);



		if (dodgeStatus == ATK_HIT)
		{
			// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit

			// getting values for dmg
			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			float effectiveness = getEffectiveness(self->_type, target->_type);
			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack;


			// Calculating final damage
			int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



			if (critValue == 1.5f)
				results += "Critical Hit|";


			// Dealing damage and updating decription
			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";



		}
		else
			results += "But it missed|";



		// Boosting attack
		results += ancientPowerBoost(self, selfParty);



		return results;
	}


	string ancientPowerBoost(defaultBirdClass* self, party& selfParty)
	{
		// If it doesnt land of the 25% to boost, leave the function
		int chanceToBoost = rand() % 4;

		if (chanceToBoost != 0)
			return "";


		// Give the boost
		string descriptionOfAction = "";
		descriptionOfAction = "All stats have been raised";

		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].critkMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].dodgeMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].offspringAddon += 1;

		return descriptionOfAction;
	}


};



#endif // !ABILITY_PECK_SPAM_H
