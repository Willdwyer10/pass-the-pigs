#include "GameCoordinator.h"

#include "Pig.h"
#include "PigRoller.h"
#include "Simulator.h"

#include <iostream>

// Create all objects, then run the simulation
void GameCoordinator::run() {
    // Load the data
    auto probabilityData = loadPigData();
    
    // Pig objects to be rolled
    auto pig1 = Pig(probabilityData);
    auto pig2 = Pig(probabilityData);

    // To handle scoring of each roll, etc.
    auto pigRoller = PigRoller(pig1, pig2);

    // For handling all simulations
    auto simulator = Simulator(pigRoller);

    // Determine the optimal threshold for games going to 100 points
    auto numTurns = simulator.optimalThreshold(100);
}

// Load the pig data from file 
std::vector<PigData> GameCoordinator::loadPigData() {
    return {
        {'j', "Leaning Jowler", 0.26666666666666666},
        {'s', "Snout", 2.0666666666666664},
        {'t', "Trotter", 7.3999999999999995},
        {'r', "Razorback", 31.933333333333337},
        {'b', "Black Dot Side", 23.866666666666667},
        {'c', "Clear (no dot) Side", 34.46666666666667}
    };
}