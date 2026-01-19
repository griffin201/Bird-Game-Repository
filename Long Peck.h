#ifndef ABILITY_LONG_PECK_H
#define ABILITY_LONG_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Ostrich


class longPeck : public defaultAbilityClass
{
public:

	longPeck()
		: defaultAbilityClass("Long Peck", 10, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Base peck that NEVER misses";
		_description[1] = "";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";




		// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit
		// getting values for dmg

		int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
		float critValue = attemptCrit(criticalChance);
		float effectiveness = getEffectiveness(self->_type, target->_type);
		float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
		float defenseStat = target->_attack * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
		float moveAttackStat = _baseAttack;


		// Damaging target
		int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);


		results += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";



		if (critValue == 1.5f)
			results += "Critical Hit|";




		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
