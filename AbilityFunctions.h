#ifndef ABILITY_FUNCTIONS_H
#define ABILITY_FUNCTIONS_H

#include "Bird Class.h"
#include "Ability Class.h"


const bool ATK_DODGED = false;
const bool ATK_HIT = true;



// For attempting to hit a critical attack
float attemptCrit(int critChance);

// For attempting to dodge an attack
bool attemptDodge(defaultBirdClass* target);


#endif // !ABILITY_FUNCTIONS_H