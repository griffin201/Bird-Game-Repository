#ifndef ABILITY_PECK_SLAM_H
#define ABILITY_PECK_SLAM_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Kiwi


class peckSlam : public defaultAbilityClass
{
public:

	peckSlam()
		: defaultAbilityClass("Peck Slam", 10, 2, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Uses the defense stat to calculate damage";
		_description[1] = "";
		_description[2] = "";
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


			// Peck Slam ability
			float attackStat = self->_defense * selfParty.statMultipliers[self->_partyIndex].defenseMultiplier;


			// getting values for dmg
			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			float effectiveness = getEffectiveness(self->_type, target->_type);
			float defenseStat = target->_attack * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack;


			// Calculating total damage
			int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



			if (critValue == 1.5f)
				results += "Critical Hit|";



			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";

		}
		else
			results += "But it missed";





		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
