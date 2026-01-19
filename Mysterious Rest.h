#ifndef ABILITY_MYSTERIOUS_REST_H
#define ABILITY_MYSTERIOUS_REST_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Owl

class mysteriousRest : public defaultAbilityClass
{
public:

	mysteriousRest()
		: defaultAbilityClass("Mysterious Rest", 0, 1, STATUS, SELF)
	{
		_description[0] = "Rests and gains a random buff by x0.35";
		_description[1] = "If that random buff is offspring";
		_description[2] = "You regain your lost egg from using this move";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += self->_name + " stats increased |";



		mysteriousRestBuff(selfParty, self->_partyIndex);



		return results;
	}

	
	void mysteriousRestBuff(party& selfParty, int indexOfMainBird)
	{


		int randDebuff = rand() % 5;


		if (randDebuff == 0)
			selfParty.statMultipliers[indexOfMainBird].attackMultiplier += 0.35f;

		else if (randDebuff == 1)
			selfParty.statMultipliers[indexOfMainBird].defenseMultiplier += 0.35f;

		else if (randDebuff == 2)
			selfParty.statMultipliers[indexOfMainBird].critkMultiplier += 0.35f;

		else if (randDebuff == 3)
			selfParty.statMultipliers[indexOfMainBird].dodgeMultiplier += 0.35f;

		else if (randDebuff == 4)
			selfParty.statMultipliers[indexOfMainBird].offspringAddon += 1;


		if (randDebuff == 4)
			selfParty.amountOfEggs += _baseEggPrice;


	}

};



#endif // !ABILITY_PECK_SPAM_H
