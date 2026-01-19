#ifndef ABILITY_DARK_DOMAIN_H
#define ABILITY_DARK_DOMAIN_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Owl

class darkDomain : public defaultAbilityClass
{
public:

	darkDomain()
		: defaultAbilityClass("Dark Domain", 0, 3, STATUS, SELF)
	{
		_description[0] = "Decreases target's party defense";
		_description[1] = "and a random stat by x0.15";
		_description[2] = "Does not debuff offspring";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " debuffed enemy team |";


		// Debuff team's defense
		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
			targetParty.statMultipliers[i].defenseMultiplier -= 0.15f;
		

		// Debuff a random stat for each bird
		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
			darkDomainDebuff(targetParty, i);



		return results;
	}


	void darkDomainDebuff(party& targetParty, int indexOfBird)
	{
		int randDebuff = rand() % 4;


		if (randDebuff == 0)
			targetParty.statMultipliers[indexOfBird].attackMultiplier -= 0.15f;

		else if (randDebuff == 1)
			targetParty.statMultipliers[indexOfBird].defenseMultiplier -= 0.15f;

		else if (randDebuff == 2)
			targetParty.statMultipliers[indexOfBird].critkMultiplier -= 0.15f;

		else if (randDebuff == 3)
			targetParty.statMultipliers[indexOfBird].dodgeMultiplier -= 0.15f;


	}

};



#endif // !ABILITY_PECK_SPAM_H
