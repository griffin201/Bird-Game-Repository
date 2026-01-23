#include "Bird Class.h"
#include "Ability Class.h"


/*
* Sets the abilit's stats
* 
* @param name - The name of the move
* @param baseAtk - The base atk of the move
* @param baseEgg - the price
* @param moveType - The type of the move (offensive or status)
* @param targetsType - The amount of targets the move hits
*/
defaultAbilityClass::defaultAbilityClass(string name, int baseAtk, int baseEgg, attackType moveType, attackTargetsType targetsType)
	: _name(name), _baseAttack(baseAtk), _baseEggPrice(baseEgg), _type(moveType), _targetsType(targetsType) { }




// Definition for default functions of ability class

/*
* THIS IS THE DEFAULT FUNCTION, IF YOU ARE READING THIS, SOMETHING IS WRONG!!!
*/
string defaultAbilityClass::useAbility(defaultBirdClass* self, party& selfParty, party& targetParty)
{
	// Printing some information to help solve the bug
	cout << "\nTHIS SHOULDNT PRINT!!!\n";
	cout << "THIS ATTACK WAS USED BY: " << self->_name << "\n";
	cout << "ATTACK NAME: " << _name << "\n\n";

	// Making sure this is read
	system("pause");
	system("pause");
	system("pause");
	system("pause");

	return "";
}

/*
* THIS IS THE DEFAULT FUNCTION, IF YOU ARE READING THIS, SOMETHING IS WRONG!!!
*/
string defaultAbilityClass::useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target)
{
	// Printing some information to help solve the bug
	cout << "\nTHIS SHOULDNT PRINT!!!\n";
	cout << "THIS ATTACK WAS USED BY: " << self->_name << "\n";
	cout << "THE TARGET WAS USED BY: " << target->_name << "\n";
	cout << "ATTACK NAME: " << _name << "\n\n";

	// Making sure this is read
	system("pause");
	system("pause");
	system("pause");
	system("pause");

	return "";

}

/*
* THIS IS THE DEFAULT FUNCTION, IF YOU ARE READING THIS, SOMETHING IS WRONG!!!
*/
string defaultAbilityClass::useAbility(defaultBirdClass* self, party& selfParty, party& targetParty, defaultBirdClass* target1, defaultBirdClass* target2)
{
	// Printing some information to help solve the bug
	cout << "\nTHIS SHOULDNT PRINT!!!\n";
	cout << "THIS ATTACK WAS USED BY: " << self->_name << "\n";
	cout << "THE FIRST TARGET WAS USED BY: " << target1->_name << "\n";
	cout << "THE SECOND TARGET WAS USED BY: " << target2->_name << "\n";
	cout << "ATTACK NAME: " << _name << "\n\n";

	// Making sure this is read
	system("pause");
	system("pause");
	system("pause");
	system("pause");

	return "";
}
