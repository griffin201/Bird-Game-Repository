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

	lightingDash()
		: defaultAbilityClass("Lighting Dash", 20, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "the bird aims for the target's heart";
		_description[1] = "Resulting in high critical ratio";
		_description[2] = "Small chance to boost critical stat";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		bool dodgeStatus = attemptDodge(target);


		if (dodgeStatus == ATK_HIT)
		{
			int totalDmg = 0;


			// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit
			// getting values for dmg

			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			float effectiveness = getEffectiveness(self->_type, target->_type);
			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_attack * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack;

			totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";



			if (critValue == 1.5f)
				results += "Critical Hit|";

			results += randomlyBuffSelf(selfParty, self->_partyIndex);

		}
		else
			results += "But it missed";



		return results;
	}

	string randomlyBuffSelf(party& selfParty, int targetIndex)
	{
		// 20% chance to buff crit stat
		int chanceToDebuff = rand() % 5;

		if (chanceToDebuff != 0)
			return "";


		selfParty.statMultipliers[targetIndex].critkMultiplier += 0.25f;


		return "Critical Stat Increased";
	}

};



#endif // !ABILITY_PECK_SPAM_H
