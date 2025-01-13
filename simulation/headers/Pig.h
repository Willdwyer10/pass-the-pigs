#pragma once

#include <random>
#include <vector>

#include "PigData.h"

class Pig {
public:
    // Create a pig object using probability data
    Pig(const std::vector<PigData>& probabilityData);

    // Simulate a roll of the pig using the probabilities provided to the constructor
    char roll();

private:
    // Reference to the pig probability data
    const std::vector<PigData>& probabilityData;

    // Random number generator and distribution are member variables to avoid frequent reconstruction
    std::mt19937 generator;
    std::uniform_real_distribution<> distribution;
};