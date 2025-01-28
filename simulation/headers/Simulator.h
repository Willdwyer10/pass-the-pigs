#pragma once

#include <vector>

#include "PigRoller.h"
#include "Player.h"

class Simulator {
public:
    // Create a Simluator object taking in a reference to a PigRoller object
    //Simulator(PigRoller& pigRoller);

    // Determines the optimal threshold to reach targetPoints points in the fewest number of turns, on average
    //int optimalThreshold(int targetPoints);
//private:
    // Determines the average number of rolls it takes to reach the target using the provided threshold
    //double averageNumTurns(int targetPoints, int threshold);

    // Simulates a single game of rolling until targetPoints are obtained; returns the number or turns it took
    //int singleGameNumTurns(int targetPoints, int threshold);

    // Create a Simulator object using a vector of all Player objects besides the one to be optimized
    Simulator(std::vector<Player>& otherPlayers);

    // Determine the optimal threshold for the playerToOptimze given the other players of the game
    std::pair<double, int> optimalThresholdForPlayer(Player& playerToOptimize);

//private:
    // Simulate a batch of games, determine the average percent of times the playerToOptimize won
    double simulateBatchOfGames(Player& playerToOptimize);

    // Simulate a single game starting from the current state, return True if the playerToOptimize, false otherwise
    bool simulateSingleGame(Player& playerToOptimze);

    // Determine if the game is over by checking if any player has won
    bool gameIsOver(Player& playerToOptimize);

    // Reset all "other players"
    void resetOtherPlayers();

    // The object that manages getting statistically realistic roll outcomes
    //PigRoller& pigRoller;
    std::vector<Player>& otherPlayers;
};
