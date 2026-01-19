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

	prehistoricPeck()
		: defaultAbilityClass("Prehistoric Peck", 15, 2, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "A peck that boost the user";
		_description[1] = "Increases defense and attack";
		_description[2] = "by x0.35";
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
			float defenseStat = target->_attack * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
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
		results += prehistoricBoost(self, selfParty);



		return results;
	}


	string prehistoricBoost(defaultBirdClass* self, party& selfParty)
	{
		string descriptionOfAction = "";
		descriptionOfAction = "Attack and defense boosted";

		selfParty.statMultipliers[self->_partyIndex].attackMultiplier += 0.35f;
		selfParty.statMultipliers[self->_partyIndex].defenseMultiplier += 0.35f;

		return descriptionOfAction;
	}


};



#endif // !ABILITY_PECK_SPAM_H
