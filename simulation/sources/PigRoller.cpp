#include "PigRoller.h"

#include <stdexcept>
#include <iostream>

// Take in two Pig references, one for each of the pigs being created
PigRoller::PigRoller(Pig &pig1, Pig &pig2)
  : pig1(pig1),
    pig2(pig2)
{}

// Performs a roll of the pigs and calculates the score of the roll
int PigRoller::roll()
{
    char pig1Res = pig1.roll();
    char pig2Res = pig2.roll();
    // std::cout << "pig1res=" << pig1Res << " pig2res=" << pig2Res << "\t";
    // Check combinations and score accordingly
    if (pig1Res == pig2Res) 
    {
        // Same positions (Doubles)
        if (pig1Res == 'j') return 60; // Leaning Jowler double
        if (pig1Res == 's') return 40; // Snout double
        if (pig1Res == 't') return 20; // Trotter double
        if (pig1Res == 'r') return 20; // Razorback double
        if (pig1Res == 'b') return 1;  // Black Dot Side double
        if (pig1Res == 'c') return 1;  // Clear (no dot) Side double
    }
    else if ((pig1Res == 'b' && pig2Res == 'c') || (pig1Res == 'c' && pig2Res == 'b')) 
    {
        return 0;  // Black Dot Side + Clear Side = Pig Out
    }
    else 
    {
        // Any other combination is just the sum of the two positions
        int totalScore = 0;

        if (pig1Res == 'j') totalScore += 15; // Leaning Jowler
        else if (pig1Res == 's') totalScore += 10; // Snout
        else if (pig1Res == 't') totalScore += 5; // Trotter
        else if (pig1Res == 'r') totalScore += 5; // Razorback
        else if (pig1Res == 'b') totalScore += 0;  // Black Dot Side
        else if (pig1Res == 'c') totalScore += 0;  // Clear (no dot) Side
 
        if (pig2Res == 'j') totalScore += 15; // Leaning Jowler
        else if (pig2Res == 's') totalScore += 10; // Snout
        else if (pig2Res == 't') totalScore += 5; // Trotter
        else if (pig2Res == 'r') totalScore += 5; // Razorback
        else if (pig2Res == 'b') totalScore += 0;  // Black Dot Side
        else if (pig2Res == 'c') totalScore += 0;  // Clear (no dot) Side

        return totalScore;
    }

    // Throw an error here if some random other combination somehow came out
    throw std::runtime_error("A valid combination was not returned; pig1Pos=" + std::string(1, pig1Res) + ", pig2Pos=" + std::string(1, pig2Res));
}
