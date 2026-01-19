#include "AbilityFunctions.h"



float getEffectiveness(birdType selfType, birdType targetType)
{
	if (selfType == Mountain)
	{
		if (targetType == Forest)
			return 1.5f;
		else if (targetType == Mountain)
			return 1.0f;
		else if (targetType == Water)
			return 0.75f;
	}
	else if (selfType == Forest)
	{
		if (targetType == Water)
			return 1.5f;
		else if (targetType == Forest)
			return 1.0f;
		else if (targetType == Mountain)
			return 0.75f;
	}
	else if (selfType == Water)
	{
		if (targetType == Mountain)
			return 1.5f;
		else if (targetType == Water)
			return 1.0f;
		else if (targetType == Forest)
			return 0.75f;
	}

	return 1.0f;
}

float attemptCrit(int critChance)
{
	int randomValue = rand() % 100 + 1;


	if (randomValue <= critChance)
		return 1.5f;
	else
		return 1.0f;
}

bool attemptDodge(defaultBirdClass* target)
{
	if (target == NULL)
		return ATK_DODGED;


	int randomValue = rand() % 100 + 1;

	if (randomValue <= target->_dodgeChance)
		return ATK_DODGED;
	else
		return ATK_HIT;

}
