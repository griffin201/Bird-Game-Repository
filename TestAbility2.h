#ifndef TEST_ABILITY_TWO_H
#define TEST_ABILITY_TWO_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"

/// THIS IS OUTDATED, DONT USE


class twoTargetTest : public defaultAbilityClass
{
public:

	twoTargetTest()
		: defaultAbilityClass("Secondary Test", 10, 2, OFFENSIVE, TWO_ENEMIES)
	{
		_description[0] = "    ---- TEST  MOVE ----";
		_description[1] = "      Does base damage";
		_description[2] = "       To 2 targets";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target1, defaultBirdClass* target2) override
	{

		
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Targets: " + target1->_name + "|";
		results += "         " + target2->_name + "|";

		results += "Health: ";


		bool dodgeStatus1 = attemptDodge(target1);
		bool dodgeStatus2 = attemptDodge(target2);
		
		bool target1Exists = false;
		bool target2Exists = false;


		if (0 < target1->_health)
			target1Exists = true;

		if (0 < target2->_health)
			target2Exists = true;



		if (dodgeStatus1 == ATK_HIT and target1Exists)
		{
			results += to_string(target1->_health) + " --> ";

			float effectiveness = getEffectiveness(self->_type, target1->_type);


			// damage = baseAttack * (self.attack / target.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target1->_defense))) * effectiveness);
			target1->_health -= finalDamage;

			results += to_string(target1->_health) + " (Dmg: " + to_string(finalDamage) + ")" + "|";
		}
		else if (dodgeStatus1 == ATK_DODGED)
			results += "Dodged|";
		


		if (dodgeStatus2 == ATK_HIT and target2Exists)
		{
			// This is mostly triggered when the target's team only has 1 available bird to take the damage
			if (target1 == target2)
				return results;



			if (target1Exists)
				results += "        ";

			results += to_string(target2->_health) + " --> ";

			float effectiveness = getEffectiveness(self->_type, target2->_type);


			// damage = baseAttack * (self.attack / target2.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target2->_defense))) * effectiveness);
			target2->_health -= finalDamage;

			results += to_string(target2->_health) + " (Dmg: " + to_string(finalDamage) + ")";

		}
		else if (dodgeStatus2 == ATK_DODGED)
			results += "Dodged";





		return results;
	}

};



#endif // !TEST_ABILITY_H
