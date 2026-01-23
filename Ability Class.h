#ifndef DEFAULT_ABILITY_CLASS_H
#define DEFAULT_ABILITY_CLASS_H

#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;


// The attack type enum
enum attackType {OFFENSIVE, STATUS};

// The amount of targets the attack hits
enum attackTargetsType {SINGLE_ENEMY, TWO_ENEMIES, ALL_ENEMIES, SINGLE_ALLY, TWO_ALLIES, ALL_ALLIES, SELF};


// Early declaring party and defaultBirdClass
struct party;
class defaultBirdClass;



// The main class for making an ability
class defaultAbilityClass
{
public:

	// Attributes of ability
	string _name = "NO NAME";
	int _baseAttack = 0;
	int _baseEggPrice = 1;
	attackType _type = OFFENSIVE;
	attackTargetsType _targetsType= SINGLE_ENEMY;
	string _description[3] = { "NO DESCRIPTION", "SOMETHING IS WRONG IF YOU", "ARE READING THIS IN GAME"};



	// constructor for an attack
	defaultAbilityClass(string name, int baseAtk, int baseEgg, attackType moveType, attackTargetsType targetsType);



	// Used for Self, All Enemies, or All Allies
	virtual string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty);

	// Used for Single_Enemy or Single_Ally
	virtual string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target);

	// Used for Two_Enemies or Two_Allies
	virtual string useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target1, defaultBirdClass* target2);


};


#endif
