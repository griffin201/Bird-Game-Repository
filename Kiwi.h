#ifndef KIWI_BIRD_H
#define KIWI_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Peck Slam.h"
#include "Harden.h"
#include "Morale Speech.h"


class KiwiBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Kiwi";

public:

    /*
    * Sets up the bird's stats and description
    */
    KiwiBirdClass()
        : KiwiBirdClass(defaultBirdName) {
    }


    /*
    * Sets up the bird's stats and description
    *
    * @param birdName - The name of the bird, used for enemy mostly
    */
    KiwiBirdClass(string birdName)
        : defaultBirdClass(birdName, 50, 5, 35, 2, 10, 7)
    {
        // If no name was given
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        // Description of bird
        _description[0] = "A tank";
        _description[1] = "Can resist all sorts of attacks";
        _description[2] = "Relies on defense to kill";


        // Alocate memory for abilities
        _abilities = new defaultAbilityClass * [3];

        // Gives the bird abilities
        _abilities[0] = new peckSlam();
        _abilities[1] = new harden();
        _abilities[2] = new moraleSpeech();
        _abilityCount = 3;
    }



};


#endif