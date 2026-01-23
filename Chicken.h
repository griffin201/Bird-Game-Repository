#ifndef CHICKEN_BIRD_H
#define CHICKEN_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Peck.h"
#include "Biggest Egg.h"
#include "Gather Food.h"

class ChickenBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Chicken";

public:

    /*
    * Sets up the bird's stats and description
    */
    ChickenBirdClass()
        : ChickenBirdClass(defaultBirdName) {
    }



    /*
    * Sets up the bird's stats and description
    *
    * @param birdName - The name of the bird, used for enemy mostly
    */
    ChickenBirdClass(string birdName)
        : defaultBirdClass(birdName, 40, 15, 15, 3, 5, 5)
    {
        // If no name was given
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;


        // Description of bird
        _description[0] = "A bird who focuses on laying eggs";
        _description[1] = "Contains normal stats";
        _description[2] = "Dont expect this birt to kill everyone";


        // Alocate memory for abilities
        _abilities = new defaultAbilityClass * [3];

        // Gives the bird abilities
        _abilities[0] = new peck();
        _abilities[1] = new biggestEgg();
        _abilities[2] = new gatherFood();
        _abilityCount = 3;
    }



};


#endif