#ifndef DEFAULT_BIRD_CLASS_H
#define DEFAULT_BIRD_CLASS_H

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


// Early declares ability class
class defaultAbilityClass;


// The main class for making birds
class defaultBirdClass
{
public:


	// Main attributes of a bird
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

	defaultAbilityClass** _abilities = NULL;
	int _abilityCount = 0;


	// Constructor for the bird
	defaultBirdClass(string name, int hp, int atk, int def, int offSpring, int crit, int dodge);


	// Desconstructor for the bird
	~defaultBirdClass();

};




#endif