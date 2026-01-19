#ifndef EAGLE_BIRD_H
#define EAGLE_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Lighting Dash.h"
#include "Air Strike.h"
#include "Calm Mind.h"

class EagleBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Eagle";

public:


    EagleBirdClass()
        : EagleBirdClass(defaultBirdName) {
    }

    EagleBirdClass(string birdName)
        : defaultBirdClass(birdName, 75, 30, 25, 1, 6, 0, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "Heavy hitter and tank";
        _description[1] = "Cant dodge attacks and garbage offspring/crit";
        _description[2] = "Requires support from aditional birds";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new airStrike();
        _abilities[1] = new calmMind();
        _abilities[2] = new lightingDash();
        _abilityCount = 3;
    }



};


#endif