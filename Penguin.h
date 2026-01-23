#ifndef PENGUIN_BIRD_H
#define PENGUIN_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Peck.h"
#include "Ice Age.h"
#include "Snow Dive.h"


class PenguinBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Penguin";

public:

    /*
    * Sets up the bird's stats and description
    */
    PenguinBirdClass()
        : PenguinBirdClass(defaultBirdName) {
    }



    /*
    * Sets up the bird's stats and description
    *
    * @param birdName - The name of the bird, used for enemy mostly
    */
    PenguinBirdClass(string birdName)
        : defaultBirdClass(birdName, 35, 30, 15, 2, 10, 10)
    {
        // If no name was given
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        // Description of bird
        _description[0] = "Heavy Hitter but easy to take down";
        _description[1] = "Penguin holds 0 supportive moves";
        _description[2] = "Its able to destroy the entire team";


        // Alocate memory for abilities
        _abilities = new defaultAbilityClass * [3];

        // Gives the bird abilities
        _abilities[0] = new peck();
        _abilities[1] = new iceAge();
        _abilities[2] = new snowDive();
        _abilityCount = 3;
    }



};


#endif