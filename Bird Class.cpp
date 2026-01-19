#include "Ability Class.h"
#include "Bird Class.h"




defaultBirdClass::defaultBirdClass(string name, int hp, int atk, int def, int offSpring, int crit, int dodge, birdType type)
	: _name(name), _health(hp), _maxHealth(hp), _attack(atk), _defense(def), _offspringQuantity(offSpring), _critChance(crit), _dodgeChance(dodge) { }


