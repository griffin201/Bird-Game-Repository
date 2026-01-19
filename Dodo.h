#ifndef DODO_BIRD_H
#define DODO_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Prehistoric Peck.h"
#include "Ancient Power.h"
#include "Glorious Heal.h"


class DodoBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Dodo";

public:


    DodoBirdClass()
        : DodoBirdClass(defaultBirdName) {
    }

    DodoBirdClass(string birdName)
        : defaultBirdClass(birdName, 35, 35, 20, 2, 10, 10, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "A self boosting bird";
        _description[1] = "All his moves help himself in some way";
        _description[2] = "Buts it requires luck to win";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new prehistoricPeck();
        _abilities[1] = new ancientPower();
        _abilities[2] = new gloriousHeal();
        _abilityCount = 3;
    }



};


#endif