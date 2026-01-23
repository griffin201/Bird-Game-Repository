#ifndef TEST_ABILITY_H
#define TEST_ABILITY_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"



/// THIS IS OUTDATED, DONT USE



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
		// Initializes the description for the move is used
		string results = "";
		
		results += self->_name + " --USED-> " + _name + "|";
		results += "Target: " + target->_name + "|";


		// Rolls for dodge
		bool dodgeStatus = attemptDodge(target);



		// If atk hit
		if (dodgeStatus == ATK_HIT)
		{
			results += "Target was successfully hit!|";
			results += "Health: " + to_string(target->_health) + " --> ";


			// damage = baseAttack * (self.attack / target.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target->_defense))));
			target->_health -= finalDamage;

			results += to_string(target->_health) + " (Dmg: " + to_string(finalDamage) + ")";
		}

		// Atk missing
		else
			results += "Attack was missed!!!";

		return results;
	}

};



#endif // !TEST_ABILITY_H
