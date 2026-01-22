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

	peckSpam()
		: defaultAbilityClass("Peck Spam", 3, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "                       ";
		_description[1] = " Hits the target 3-5 times";
		_description[2] = "Every Hit has a chance to be dodged";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		int randHits = rand() % 3; // 0/1/2
		int amountOfHits = 3 + randHits; // Generates 3-5 hits
		int amountOfSuccesfullHits = 0;
		int amountOfDodges = 0;
		int amountOfCrits = 0;
		int totalDmg = 0;



		for (int i = 0; i < amountOfHits; i++)
		{
			bool dodgeStatus = attemptDodge(target);

			if (dodgeStatus == ATK_HIT)
			{
				float effectiveness = getEffectiveness(self->_type, target->_type);
				int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
				float critValue = attemptCrit(criticalChance);


				if (critValue == 1.5f)
					amountOfCrits++;
				

				// damage = baseAttack * (self.attack / target.defense) * effectiveness
				float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
				float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;

				int finalDamage = int((_baseAttack * (attackStat / defenseStat)) * effectiveness * critValue);
				totalDmg += finalDamage;

				amountOfSuccesfullHits++;
			}



		}



		results += "Hit a total of: " + to_string(amountOfHits) + "|";
		results += "Attacks missed: " + to_string(amountOfHits - amountOfSuccesfullHits) + "|";
		results += "Total Criticals: " + to_string(amountOfCrits) + "|";



		results += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		results += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")";




		return results;
	}

};



#endif // !ABILITY_PECK_SPAM_H
