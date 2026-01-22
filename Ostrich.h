#ifndef OSTRICH_BIRD_H
#define OSTRICH_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Lighting Dash.h"
#include "Long Peck.h"
#include "Biggest Egg.h"


class OstrichBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Ostrich";

public:


    OstrichBirdClass()
        : OstrichBirdClass(defaultBirdName) {
    }

    OstrichBirdClass(string birdName)
        : defaultBirdClass(birdName, 65, 20, 20, 3, 15, 8, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "A self sustainable killing machine";
        _description[1] = "Ostrich doesn't rely on buffs/debuffs to hit hard";
        _description[2] = "It just hits hard because it can";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new lightingDash();
        _abilities[1] = new longPeck();
        _abilities[2] = new biggestEgg();
        _abilityCount = 3;
    }



};


#endif