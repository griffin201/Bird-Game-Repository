#include "Ability Class.h"
#include "Bird Class.h"



/*
* Sets the stats of the bird
* 
* @param name - the name of the bird class
* @param hp - the health stat
* @param atk - the attack stat
* @param def - the defense stat
* @param offSpring - the amount of eggs they produce during rest
* @param crit - the critical chance stat
* @param dodge - the dodge chance stat
*/
defaultBirdClass::defaultBirdClass(string name, int hp, int atk, int def, int offSpring, int crit, int dodge)
	: _name(name), _health(hp), _maxHealth(hp), _attack(atk), _defense(def), _offspringQuantity(offSpring), _critChance(crit), _dodgeChance(dodge) { }


/*
* Deletes the memory for abilities
*/
defaultBirdClass::~defaultBirdClass()
{
	delete _abilities;
}