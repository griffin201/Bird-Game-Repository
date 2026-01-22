#ifndef ABILITY_MORALE_SPEECH_H
#define ABILITY_MORALE_SPEECH_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Kiwi

class moraleSpeech : public defaultAbilityClass
{
public:

	moraleSpeech()
		: defaultAbilityClass("Morale Speech", 0, 3, STATUS, SELF)
	{
		_description[0] = "Boosts team's defense by x0.25";
		_description[1] = "";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += "Team's defense has been increased by x0.25 |";


		selfParty.statMultipliers[0].defenseMultiplier += 0.25f;
		selfParty.statMultipliers[1].defenseMultiplier += 0.25f;
		selfParty.statMultipliers[2].defenseMultiplier += 0.25f;


		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
