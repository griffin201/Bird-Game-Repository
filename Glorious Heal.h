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


	/*
	* Sets up the move's stats and description
	*/
	gloriousHeal()
		: defaultAbilityClass("Glorious Heal", 0, 3, STATUS, SELF)
	{
		_description[0] = "Heals party member with the least health";
		_description[1] = "by 50% of their max hp";
		_description[2] = "";
	}



	/*
	* Uses the ability - Varies depending on the ability being used
	*
	* @return returns a description of the move
	* @param self - The main bird casting the ability
	* @param selfParty - The caster's party
	* @param targetParty - The target's party
	*/
	string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty) override
	{
		// Initializes the description for the move is used
		string results = "";

		
		// Stores the index of the weakest ally in terms of health
		int weakestAllyIndex = 0;


		// For all birds in the party
		for (int i = 0; i < MAX_BIRDS_PER_PARTY; i++)
		{
			// If the birds doesnt exist continue
			if (selfParty.birds[i] == NULL)
				continue;

			// If the current selected bird doesnt exist, set it as i
			if (selfParty.birds[weakestAllyIndex] == NULL)
				weakestAllyIndex = i;

			// If the health of the current selected bird is lower than the weakest bird
			if (selfParty.birds[i]->_health < selfParty.birds[weakestAllyIndex]->_health)
				weakestAllyIndex = i;
		}

		// Save the weakest bird as variable
		defaultBirdClass* weakestAlly = selfParty.birds[weakestAllyIndex];



		//  Updates description for the move is used
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
