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

    /*
    * Sets up the bird's stats and description
    */
    OwlBirdClass()
        : OwlBirdClass(defaultBirdName) { }



    /*
    * Sets up the bird's stats and description
    *
    * @param birdName - The name of the bird, used for enemy mostly
    */
    OwlBirdClass(string birdName)
        : defaultBirdClass(birdName, 65, 20, 15, 3, 15, 8)
    {
        // If no name was given
        if (birdName == "")
            _name = defaultBirdName;
        else
            _name += " " + defaultBirdName;

        // Description of bird
        _description[0] = "A support bird that focus on debuffs";
        _description[1] = "Its main gimmick is to weaken the enemy team";
        _description[2] = "One enemy team is weaken, owl shows its true colors";


        // Alocate memory for abilities
        _abilities = new defaultAbilityClass * [3];

        // Gives the bird abilities
        _abilities[0] = new darkPeck();
        _abilities[1] = new darkDomain();
        _abilities[2] = new mysteriousRest();
        _abilityCount = 3;
    }



};


#endif