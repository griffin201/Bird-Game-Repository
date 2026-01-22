#ifndef ABILITY_HEAVY_LONG_PECK_H
#define ABILITY_HEAVY_LONG_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Shoebill


class heavyLongPeck : public defaultAbilityClass
{
public:

	heavyLongPeck()
		: defaultAbilityClass("Heavy Long Peck", 30, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "High damage and cant miss";
		_description[1] = "";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit

		// Getting values for dmg
		int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
		float critValue = attemptCrit(criticalChance);
		float effectiveness = getEffectiveness(self->_type, target->_type);
		float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
		float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
		float moveAttackStat = _baseAttack;


		// Calculating total damage
		int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



		if (critValue == 1.5f)
			results += "Critical Hit|";



		results += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";





		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
