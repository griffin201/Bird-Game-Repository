#ifndef ABILITY_AIR_STRIKE_H
#define ABILITY_AIR_STRIKE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Eagle


class airStrike : public defaultAbilityClass
{
public:

	airStrike()
		: defaultAbilityClass("Air Strike", 35, 3, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "High damage attack";
		_description[1] = "Decreases the bird own defense by x0.3";
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
			int totalDmg = 0;


			// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit
			// getting values for dmg

			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			float effectiveness = getEffectiveness(self->_type, target->_type);
			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack;

			totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



			if (critValue == 1.5f)
				results += "Critical Hit|";


			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")";



			// Decreasing defense stat
			selfParty.statMultipliers[self->_partyIndex].defenseMultiplier -= 0.3f;


		}
		else
			results += "But it missed";



		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
