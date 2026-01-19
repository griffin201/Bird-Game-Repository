#ifndef DEFAULT_BIRD_CLASS_H
#define DEFAULT_BIRD_CLASS_H

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


enum birdType { Water, Forest, Mountain };

class defaultAbilityClass;

class defaultBirdClass
{
public:

	string _name = "imaginary bird";
	string _description[3] = { "", "", "" };
	int _partyIndex = 0;

	int _health = 100;
	int _maxHealth = 100;
	int _attack = 20;
	int _defense = 20;
	int _offspringQuantity = 1;
	int _critChance = 8;
	int _dodgeChance = 5;

	birdType _type = Forest; // Mountain -> Forest -> Water -> Mountain

	defaultAbilityClass** _abilities = NULL;
	int _abilityCount = 0;


	defaultBirdClass(string name , int hp, int atk, int def, int offSpring, int crit, int dodge, birdType type);

};




#endif