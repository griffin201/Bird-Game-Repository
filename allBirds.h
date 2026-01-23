#ifndef ALL_BIRDS_H
#define ALL_BIRDS_H


// Simply includes all birds in the game
#include "HummingBird.h"
#include "Owl.h"
#include "Ostrich.h"
#include "Eagle.h"
#include "Penguin.h"
#include "Dodo.h"
#include "Kiwi.h"
#include "Shoebill.h"
#include "Chicken.h"



// Also has some names and stuff ig, not really important, just names the enemies
const int NUMBER_OF_RANDOM_NAMES = 54;
const string RANDOM_NAMES_FOR_AI_BIRDS[NUMBER_OF_RANDOM_NAMES] =
{
    "Aren", "Brax", "Cira", "Drex", "Elya", "Fenn", "Garo", "Hila",
    "Irex", "Jora", "Kyn",  "Luma", "Miro", "Nash", "Orin", "Pyra",
    "Quin", "Rhea", "Soren","Tavi", "Ulric","Veya", "Wren", "Xano",
    "Yori", "Zane", "Asha", "Belo", "Cato", "Dina", "Eron", "Faye",
    "Glen", "Haro", "Iris", "Jett", "Kara", "Lior", "Mila", "Nero",
    "Olin", "Pax",  "Riko", "Syra", "Theo", "Una",  "Vito", "Wyra",
    "Xavi", "Yara", "Zeno", "Aiko", "Brin", "Cleo"
};


#endif