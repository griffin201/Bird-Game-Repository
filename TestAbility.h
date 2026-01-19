#ifndef TEST_ABILITY_H
#define TEST_ABILITY_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"



class singleTargetTest : public defaultAbilityClass
{
public:

	singleTargetTest()
		: defaultAbilityClass("Test Ability", 10, 1, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "";
		_description[1] = "      Does base damage";
		_description[2] = "        To 1 target";	
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";
		
		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		bool dodgeStatus = attemptDodge(target);

		if (dodgeStatus == ATK_HIT)
		{
			results += "Target was successfully hit!|";
			results += "Health: " + to_string(target->_health) + " --> ";

			float effectiveness = getEffectiveness(self->_type, target->_type);


			// damage = baseAttack * (self.attack / target.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target->_defense))) * effectiveness);
			target->_health -= finalDamage;

			results += to_string(target->_health) + " (Dmg: " + to_string(finalDamage) + ")";
		}
		else
			results += "Attack was missed!!!";

		return results;
	}

};



#endif // !TEST_ABILITY_H
