#ifndef ABILITY_ICE_AGE_H
#define ABILITY_ICE_AGE_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"


// This ability is present in:
// - Penguin


class iceAge : public defaultAbilityClass
{
public:

	iceAge()
		: defaultAbilityClass("Ice Age", 45, 14, OFFENSIVE, SINGLE_ENEMY)
	{
		_description[0] = "A devastating heavy hitter";
		_description[1] = "Hits the entire enemy party";
		_description[2] = "Cant miss and destroys 2 eggs";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "It hit the entire party|";



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




		// Hits the targets
		if (target1Exists)
			results += iceAgeSingle(self, selfParty, targetParty, target1);

		if (target2Exists)
			results += iceAgeSingle(self, selfParty, targetParty, target2);

		if (target3Exists)
			results += iceAgeSingle(self, selfParty, targetParty, target3);


		
		// Destroys the eggs
		results += iceAgeDestroyEggs(targetParty);




		return results;
	}


	string iceAgeSingle(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target)
	{
		string descriptionOfAction = "";


		// damage = baseAttack * (self.attack / target.defense) * effectiveness * crit
		// getting values for dmg

		int criticalChance = self->_critChance * selfParty.statMultipliers[self->_partyIndex].critkMultiplier;
		float critValue = attemptCrit(criticalChance);
		float effectiveness = getEffectiveness(self->_type, target->_type);
		float attackStat = self->_attack * selfParty.statMultipliers[self->_partyIndex].attackMultiplier;
		float defenseStat = target->_defense * targetParty.statMultipliers[target->_partyIndex].defenseMultiplier;
		float moveAttackStat = _baseAttack;


		// Calculating final damage
		int totalDmg = int((moveAttackStat * (attackStat / defenseStat)) * effectiveness * critValue);





		// Description stuff and dealling the damage
		descriptionOfAction += "Health: " + to_string(target->_health) + " --> ";
		target->_health -= totalDmg;
		descriptionOfAction += to_string(target->_health) + " (Dmg: " + to_string(totalDmg) + ")";

		if (critValue == 1.5f)
			descriptionOfAction += " (Crit)";

		descriptionOfAction += "|";

		return descriptionOfAction;

	}


	string iceAgeDestroyEggs(party& targetParty)
	{

		targetParty.amountOfEggs -= 2;

		return "Enemy lost 2 eggs during the attack";

	}

};



#endif // !ABILITY_PECK_SPAM_H
