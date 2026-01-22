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
		: defaultAbilityClass("Glorious Heal", 0, 3, STATUS, SELF)
	{
		_description[0] = "Heals party member with the least health";
		_description[1] = "by 50% of their max hp";
		_description[2] = "";
	}



	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		string results = "";


		int weakestAllyIndex = 0;


		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			if (selfParty.birds[i] == NULL)
				continue;


			if (selfParty.birds[i]->_health < selfParty.birds[weakestAllyIndex]->_health)
				weakestAllyIndex = i;
		}

		defaultBirdClass* weakestAlly = selfParty.birds[weakestAllyIndex];



		results += self->_name + " --USED-> " + _name + "|";
		results += weakestAlly->_name + " has been healed|";
		results += weakestAlly->_health + " -> ";
		


		// Gives healling
		int halfOfMax = weakestAlly->_maxHealth / 2;
		weakestAlly->_health += halfOfMax;

		
		// Makes sure its not above max health
		if (weakestAlly->_maxHealth < weakestAlly->_health)
			weakestAlly->_health = weakestAlly->_maxHealth;




		results += weakestAlly->_health;
		return results;
	}


};



#endif // !ABILITY_PECK_SPAM_H
