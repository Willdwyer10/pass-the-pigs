#include "Simulator.h"

#include <algorithm>
#include <iostream>
#include <limits>

/*
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
*/

Simulator::Simulator(std::vector<Player> &otherPlayers)
  : otherPlayers(otherPlayers)
{}

std::pair<double, int> Simulator::optimalThresholdForPlayer(Player &playerToOptimize)
{
    int optimalThreshold = 0;
    double maxWinPercentage = 0.0;
    for(int threshold = 1; threshold <= playerToOptimize.getTargetPoints(); threshold++)
    {
        auto playerThisThreshold = Player(playerToOptimize, threshold);
        double winPercentage = simulateBatchOfGames(playerThisThreshold);
        //std::cout << "At a threshold of " << threshold << " player won " << winPercentage << "% of the time\n";
        if(winPercentage > maxWinPercentage)
        {
            //std::cout << "optimal threshold being updated\n";
            maxWinPercentage = winPercentage;
            optimalThreshold = threshold;
        }
    }

    return std::pair<double, int>(maxWinPercentage, optimalThreshold);
}

double Simulator::simulateBatchOfGames(Player &playerToOptimize)
{
    const int numTrials = 1000;
    int numWon = 0;
    for(int i = 0; i < numTrials; i++)
    {
        if(simulateSingleGame(playerToOptimize))
        {
            numWon += 1;
        }
        playerToOptimize.reset();
        resetOtherPlayers();
    }
    return 100.0 * numWon / numTrials;
}

bool Simulator::simulateSingleGame(Player &playerToOptimize)
{
    while(!gameIsOver(playerToOptimize))
    {
        //std::cout << "Round starting\n";
        //std::cout << "\t(" << playerToOptimize.getName() << ") threshold " << playerToOptimize.getThreshold() << " start with: " << playerToOptimize.getCurrentScore();
        playerToOptimize.rollPigs();
        //std::cout << " now has: " << playerToOptimize.getCurrentScore() << std::endl;
        for(auto& player : otherPlayers) {
            //std::cout << "\t("<< player.getName() << ") threshold " << player.getThreshold() << " start with: " << player.getCurrentScore();
            player.rollPigs();
            //std::cout << " now has: " << player.getCurrentScore() << std::endl;
        }
    }

    // Note: It is possible that another player from otherPlayers has also won this round;
    // however, we simulate the game starting from the playerToOptimize's turn, so if
    // the playerToOptimize has won, they won before any other player's turn
    return playerToOptimize.hasWon();
}

bool Simulator::gameIsOver(Player &playerToOptimize)
{
    bool anyPlayerHasWon = std::any_of(otherPlayers.begin(), otherPlayers.end(), [](auto& player) {
        return player.hasWon();
    });

    return playerToOptimize.hasWon() || anyPlayerHasWon;
}

void Simulator::resetOtherPlayers()
{
    for(auto& player : otherPlayers) {
        player.reset();
    }
}
