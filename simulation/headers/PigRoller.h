#pragma once

#include "Pig.h"

class PigRoller {
public:
    // Take in two Pig references, one for each of the pigs being created
    PigRoller(Pig& pig1, Pig& pig2);

    // Performs a roll of the pigs and calculates the score of the roll
    int roll();
private:
    // The two pigs that get rolled
    Pig& pig1, pig2;
};