#ifndef HUMMING_BIRD_H
#define HUMMING_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Peck Spam.h"
#include "Quick Robery.h"
#include "Humming Dance.h"


class HummingbirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Hummingbird";

public:

    /*
    * Sets up the bird's stats and description
    */
    HummingbirdClass()
        : HummingbirdClass(defaultBirdName) {}



    /*
    * Sets up the bird's stats and description
    *
    * @param birdName - The name of the bird, used for enemy mostly
    */
    HummingbirdClass(string birdName)
        : defaultBirdClass(birdName, 40, 10, 10, 2, 15, 40)
    {
        // If no name was given
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;


        // Description of bird
        _description[0] = "A fast and hard to kill bird.";
        _description[1] = "With enough setup time Hummingbird";
        _description[2] = "is practically impossible to hit";


        // Alocate memory for abilities
        _abilities = new defaultAbilityClass * [3];


        // Gives the bird abilities
        _abilities[0] = new peckSpam();
        _abilities[1] = new quickRobery();
        _abilities[2] = new hummingDance();
        _abilityCount = 3;
    }


};


#endif