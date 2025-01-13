#include "Simulator.h"

#include <iostream>
#include <limits>

// Create a Simluator object taking in a reference to a PigRoller object
Simulator::Simulator(PigRoller& pigRoller)
  : pigRoller(pigRoller)
{}

// Determines the optimal threshold to reach targetPoints points in the fewest number of turns, on average
int Simulator::optimalThreshold(int targetPoints)
{
    // What it needs to do is go through each possible threshold value, which means go from 1 to targetPoints,
    // and see how many rolls, on average, it takes to reach the targetPoints value
    double minNumTurns = std::numeric_limits<double>::max();
    int minThreshold = 0;

    // Check each possible threshold value, values ranging from 1 to the targetPoints
    for(int threshold = 1; threshold <= targetPoints; threshold++) {
        auto averageNumberTurns = averageNumTurns(targetPoints, threshold);
        if(averageNumberTurns < minNumTurns) {
            minNumTurns = averageNumberTurns;
            minThreshold = threshold;
        }
        std::cout << "average number of turns for threshold " << threshold << " was " << averageNumberTurns << std::endl;
    }

    std::cout << "Min threshold is " << minThreshold << " with an average of " << minNumTurns << " turns." << std::endl;

    return minThreshold;
}

// Determines the average number of rolls it takes to reach the target using the provided threshold
double Simulator::averageNumTurns(int targetPoints, int threshold)
{
    // Simulate 100 games of getting to targetPoints 
    const int numGames = 10000;

    // Number of total turns that have occurred
    int totalNumTurns = 0;

    for(int i = 0; i < numGames; i++) {
        // std::cout << "************************************************************************************************\n";
        // std::cout << "ITERATION " << i << std::endl;
        totalNumTurns += singleGameNumTurns(targetPoints, threshold);
    }

    return double(totalNumTurns) / numGames;
}

// Simulates a single game of rolling until targetPoints are obtained; returns the number or turns it took
int Simulator::singleGameNumTurns(int targetPoints, int threshold)
{
    // The number of points obtained in this single game's simulation
    int totalPointsThisGame = 0;

    // The number of turns it took to reach the targetPoints
    int numTurns = 0;

    // We need to simulate turns until we reach the target number of points
    while(totalPointsThisGame < targetPoints) {
        numTurns += 1;
        int rollResult = pigRoller.roll();
        int currentTurnNumPoints = 0;
        while(rollResult != 0 && currentTurnNumPoints < threshold) {
            currentTurnNumPoints += rollResult;
            rollResult = pigRoller.roll();
        }
        
        if(rollResult != 0) {
            totalPointsThisGame += currentTurnNumPoints;
        } else {
        //    std::cout << "pig out occurred!" << std::endl;
        }
        // std::cout << "total points are " << totalPointsThisGame << " after " << numTurns << " turns. " << (rollResult != 0 ? currentTurnNumPoints : 0) << " added this game." << std::endl << std::endl;;
    }

    return numTurns;
}
