#ifndef SHOEBILL_BIRD_H
#define SHOEBILL_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Laserbeam.h"
#include "Heavy Long Peck.h"
#include "Dark Domain.h"


class ShoebillBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Shoebill";

public:


    ShoebillBirdClass()
        : ShoebillBirdClass(defaultBirdName) {
    }

    ShoebillBirdClass(string birdName)
        : defaultBirdClass(birdName, 60, 30, 35, 2, 10, 7, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "A fat heavy hitter";
        _description[1] = "Lazerbeam realy gud fr";
        _description[2] = "";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new laserbeam();
        _abilities[1] = new heavyLongPeck();
        _abilities[2] = new darkDomain();
        _abilityCount = 3;
    }



};


#endif