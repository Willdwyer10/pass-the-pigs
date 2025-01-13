#pragma once

#include <vector>
    
#include "PigData.h"

class GameCoordinator {
public:
    // Create all objects, then run the simulation
    void run();

private:
    // Load pig data and store as a vector of PigData structs
    std::vector<PigData> loadPigData();
};