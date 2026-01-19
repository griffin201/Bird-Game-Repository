#ifndef ABILITY_GLORIOUIS_HEAL_H
#define ABILITY_GLORIOUIS_HEAL_H

#include "Ability Class.h"
#include "Bird Class.h"
#include "AbilityFunctions.h"
#include "Essentials.h"



// This ability is present in:
// - Dodo

class gloriousHeal : public defaultAbilityClass
{
public:

	gloriousHeal()
		: defaultAbilityClass("Glorious Heal", 0, 3, STATUS, SINGLE_ALLY)
	{
		_description[0] = "Heals chosen party member by 50%";
		_description[1] = "of their current max hp";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target) override
	{
		string results = "";

		results += self->_name + " --USED-> " + _name + "|";
		results += target->_name + " has been healed|";
		results += target->_health + " -> ";
		


		// Gives healling
		int halfOfMax = target->_maxHealth / 2;
		target->_health += halfOfMax;

		
		// Makes sure its not above max health
		if (target->_maxHealth < target->_health)
			target->_health = target->_maxHealth;




		results += target->_health;
		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
