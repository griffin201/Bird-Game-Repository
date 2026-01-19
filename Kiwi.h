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


    KiwiBirdClass()
        : KiwiBirdClass(defaultBirdName) {
    }

    KiwiBirdClass(string birdName)
        : defaultBirdClass(birdName, 50, 5, 35, 2, 10, 7, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "A tank";
        _description[1] = "Can resist all sorts of attacks";
        _description[2] = "Relies on defense to kill";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new peckSlam();
        _abilities[1] = new harden();
        _abilities[2] = new moraleSpeech();
        _abilityCount = 3;
    }



};


#endif