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

	snowDive()
		: defaultAbilityClass("Snow Dive", 25, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Deals damage while also";
		_description[1] = "increasing attack and dodge";
		_description[2] = "by x0.25";
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



			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";

			results += self->_name + " gained a boost in attack and dodge";

		}
		else
			results += "But it missed";





		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
