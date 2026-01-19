#ifndef DEFAULT_ABILITY_CLASS_H
#define DEFAULT_ABILITY_CLASS_H

#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;


enum attackType {OFFENSIVE, STATUS};
enum attackTargetsType {SINGLE_ENEMY, TWO_ENEMIES, ALL_ENEMIES, SINGLE_ALLY, TWO_ALLIES, ALL_ALLIES, SELF};


struct party;

class defaultBirdClass;

class defaultAbilityClass
{
public:

	string _name = "NO NAME";
	int _baseAttack = 0;
	int _baseEggPrice = 1;
	attackType _type = OFFENSIVE;
	attackTargetsType _targetsType= SINGLE_ENEMY;
	string _description[3] = { "NO DESCRIPTION", "SOMETHING IS WRONG IF YOU", "ARE READING THIS"};



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
