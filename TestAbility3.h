#ifndef TEST_ABILITY_THREE_H
#define TEST_ABILITY_THREE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"

/// THIS IS OUTDATED, DONT USE


class threeTargetTest : public defaultAbilityClass
{
public:

	threeTargetTest()
		: defaultAbilityClass("Third Ability", 10, 3, OFFENSIVE, ALL_ENEMIES)
	{
		_description[0] = "";
		_description[1] = "Not finished";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		
		// Checking if the targets are valid
		bool target1Exists = true;
		bool target2Exists = true;
		bool target3Exists = true;


		defaultBirdClass* target1 = targetParty.birds[0];
		defaultBirdClass* target2 = targetParty.birds[1];
		defaultBirdClass* target3 = targetParty.birds[2];


		// Make sure they exist
		if (target1 == NULL)
			target1Exists = false;
		if (target2 == NULL)
			target2Exists = false;
		if (target3 == NULL)
			target3Exists = false;



		// Make sure they are able to take dmg
		if (target1Exists)
			if (target1->_health <= 0)
				target1Exists = false;

		if (target2Exists)
			if (target2->_health <= 0)
				target2Exists = false;

		if (target3Exists)
			if (target3->_health <= 0)
				target3Exists = false;







		// Showing the valid targets
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";


		results += "Hits the entire party|";

		
		
		
		results += "Health: ";
		

		bool dodgeStatus1 = attemptDodge(target1);
		bool dodgeStatus2 = attemptDodge(target2);
		bool dodgeStatus3 = attemptDodge(target3);




		// Attacking the targets
		if (dodgeStatus1 == ATK_HIT and target1Exists)
		{
			results += to_string(target1->_health) + " --> ";


			float effectiveness = getEffectiveness(self->_type, target1->_type);

			// damage = baseAttack * (self.attack / target.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target1->_defense))) * effectiveness);
			target1->_health -= finalDamage;


			results += to_string(target1->_health) + " (Dmg: " + to_string(finalDamage) + ")" + "|";
		}
		else if (dodgeStatus1 == ATK_DODGED and target1Exists)
			results += "Dodged|";




		if (target1Exists)
			results += "        ";

		if (dodgeStatus2 == ATK_HIT and target2Exists)
		{
			results += to_string(target2->_health) + " --> ";


			float effectiveness = getEffectiveness(self->_type, target2->_type);

			// damage = baseAttack * (self.attack / target2.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target2->_defense))) * effectiveness);
			target2->_health -= finalDamage;


			results += to_string(target2->_health) + " (Dmg: " + to_string(finalDamage) + ")|";

		}
		else if (dodgeStatus2 == ATK_DODGED and target2Exists)
			results += "Dodged|";




		if (target1Exists or target2Exists)
			results += "        ";

		if (dodgeStatus3 == ATK_HIT and target3Exists)
		{

			results += to_string(target3->_health) + " --> ";


			float effectiveness = getEffectiveness(self->_type, target3->_type);

			// damage = baseAttack * (self.attack / target3.defense) * effectiveness
			int finalDamage = int(((int)((float)_baseAttack * ((float)self->_attack / (float)target3->_defense))) * effectiveness);
			target3->_health -= finalDamage;


			results += to_string(target3->_health) + " (Dmg: " + to_string(finalDamage) + ")";

		}
		else if (dodgeStatus3 == ATK_DODGED and target3Exists)
			results += "Dodged";



		return results;
	}

};



#endif // !TEST_ABILITY_H
