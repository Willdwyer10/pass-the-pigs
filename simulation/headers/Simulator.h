#pragma once

#include "PigRoller.h"

class Simulator {
public:
    // Create a Simluator object taking in a reference to a PigRoller object
    Simulator(PigRoller& pigRoller);

    // Determines the optimal threshold to reach targetPoints points in the fewest number of turns, on average
    int optimalThreshold(int targetPoints);
//private:
    // Determines the average number of rolls it takes to reach the target using the provided threshold
    double averageNumTurns(int targetPoints, int threshold);

    // Simulates a single game of rolling until targetPoints are obtained; returns the number or turns it took
    int singleGameNumTurns(int targetPoints, int threshold);

    // The object that manages getting statistically realistic roll outcomes
    PigRoller& pigRoller;
};
