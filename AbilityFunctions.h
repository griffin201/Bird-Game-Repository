#ifndef ABILITY_FUNCTIONS_H
#define ABILITY_FUNCTIONS_H

#include "Bird Class.h"
#include "Ability Class.h"


const bool ATK_DODGED = false;
const bool ATK_HIT = true;



float getEffectiveness(birdType selfType, birdType targetType);

float attemptCrit(int critChance);

bool attemptDodge(defaultBirdClass* target);


#endif // !ABILITY_FUNCTIONS_H