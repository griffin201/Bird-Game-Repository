#ifndef OWL_BIRD_H
#define OWL_BIRD_H

#include "Bird Class.h"
#include "Ability Class.h"
#include "Essentials.h"
#include "Dark Peck.h"
#include "Dark Domain.h"
#include "Mysterious Rest.h"


class OwlBirdClass : public defaultBirdClass
{
private:
    string defaultBirdName = "Owl";

public:


    OwlBirdClass()
        : OwlBirdClass(defaultBirdName) {
    }

    OwlBirdClass(string birdName)
        : defaultBirdClass(birdName, 65, 20, 15, 3, 15, 8, Forest)
    {
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        _description[0] = "A support bird that focus on debuffs";
        _description[1] = "Its main gimmick is to weaken the enemy team";
        _description[2] = "One enemy team is weaken, owl shows its true colors";


        _abilities = new defaultAbilityClass * [3];

        _abilities[0] = new darkPeck();
        _abilities[1] = new darkDomain();
        _abilities[2] = new mysteriousRest();
        _abilityCount = 3;
    }



};


#endif