#ifndef ABILITY_DARK_PECK_H
#define ABILITY_DARK_PECK_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Owl


class darkPeck : public defaultAbilityClass
{
public:

	darkPeck()
		: defaultAbilityClass("Dark Peck", 10, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "Attack scales on how many unique debuffs target has";
		_description[1] = "it becomes weaker if target has buffs";
		_description[2] = "Chance to randomly debuff target";
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


			// Exclussives to dark peck
			float darkPeckMultiplier = getDarkPeckMultiplier(targetParty, target->_partyIndex);



			// getting values for dmg
			float effectiveness = getEffectiveness(self->_type, target->_type);
			int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
			float critValue = attemptCrit(criticalChance);
			bool isCrit = false;


			if (critValue == 1.5f)
				isCrit = true;


			// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit
			float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
			float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
			float moveAttackStat = _baseAttack * darkPeckMultiplier;

			totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);



			results += "Health: " + to_string(target->_health) + " --> ";
			target->_health -= totalDmg;
			results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")|";


			results += randomlyDebuffTarget(targetParty, target->_partyIndex);

		}
		else
			results += "But it missed";



		return results;
	}


	float getDarkPeckMultiplier(party& targetParty, int targetIndex)
	{
		float totalMultiplier = 1.0f;


		// Attack stat
		if (targetParty.statMultipliers[targetIndex].attackMultiplier < 1.0f)
			totalMultiplier += 1.0f;
		else if (targetParty.statMultipliers[targetIndex].attackMultiplier > 1.0f)
			totalMultiplier -= 1.0f;

		// Defense stat
		if (targetParty.statMultipliers[targetIndex].defenseMultiplier < 1.0f)
			totalMultiplier += 1.0f;
		else if (targetParty.statMultipliers[targetIndex].defenseMultiplier > 1.0f)
			totalMultiplier -= 1.0f;


		// Crit stat
		if (targetParty.statMultipliers[targetIndex].critkMultiplier < 1.0f)
			totalMultiplier += 1.0f;
		else if (targetParty.statMultipliers[targetIndex].critkMultiplier > 1.0f)
			totalMultiplier -= 1.0f;

		// Dodge stat
		if (targetParty.statMultipliers[targetIndex].dodgeMultiplier < 1.0f)
			totalMultiplier += 1.0f;
		else if (targetParty.statMultipliers[targetIndex].dodgeMultiplier > 1.0f)
			totalMultiplier -= 1.0f;



		if (totalMultiplier < 1.0f)
			totalMultiplier = 1.0f;


		return totalMultiplier;
	}

	string randomlyDebuffTarget(party& targetParty, int targetIndex)
	{
		// 25% to debuff a random stat from target
		int chanceToDebuff = rand() % 4;

		if (chanceToDebuff != 0)
			return "";

		// Atk, def, crit, dodge
		int randStatToDebuff = rand() % 4;

		
		// atk Stat reduction
		if (randStatToDebuff == 0)
			targetParty.statMultipliers[targetIndex].attackMultiplier -= 0.15f;

		// def Stat reduction
		else if (randStatToDebuff == 2)
			targetParty.statMultipliers[targetIndex].defenseMultiplier -= 0.15f;

		// crit Stat reduction
		else if (randStatToDebuff == 3)
			targetParty.statMultipliers[targetIndex].critkMultiplier -= 0.15f;

		// dodge Stat reduction
		else if (randStatToDebuff == 4)
			targetParty.statMultipliers[targetIndex].dodgeMultiplier -= 0.15f;


		return "Target's stats decreased";
	}

};



#endif // !ABILITY_PECK_SPAM_H
