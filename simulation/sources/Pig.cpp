#include "Pig.h"

#include <stdexcept>

// Create a pig object using probability data
Pig::Pig(const std::vector<PigData> &probabilityData)
  : probabilityData(probabilityData), 
    generator(std::random_device{}()),
    distribution(0.0, 100.0)
{}

// Simulate a roll of the pig using the probabilities provided to the constructor
char Pig::roll()
{
    // Generate a random number between 0 and 100
    double roll = distribution(generator);

    // Iterate through probabilities and use cumulative probabilities to determine
    // what position this roll double corresponds to
    double cumulativeProbability = 0.0;
    for (const auto& pigData : probabilityData) {
        cumulativeProbability += pigData.probability;
        if (roll <= cumulativeProbability) {
            return pigData.symbol;  // return the character for the rolled position
        }
    }
    
    // In case of rounding issues, throw an error here
    throw std::runtime_error("Failed to roll a valid pig position");
}