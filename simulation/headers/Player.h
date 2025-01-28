#pragma once

#include "PigRoller.h"

#include <string>

class Player {
public:
    // Create a player object using a PigRoller object, the game's targetPoints, the turn threshold, and the score they start at
    Player(PigRoller& pigRoller, int targetPoints, int threshold, int startingPoints, std::string name);

    // Create a new player object that's a copy of a different one but with a different threshold
    Player(const Player& other, int newThreshold);

    // Rolls the pigs until either the threshold is reached or a pig out occurs; returns the score acquired
    int rollPigs();

    // Reset this player's score to their starting score
    void reset();

    // Whether or not this player has achieved a winning score
    bool hasWon();

    // Player's name
    std::string getName();

    // Player's threshold
    int getThreshold();

    // Target points
    int getTargetPoints();

    // NOTE: just temporarily available for tesing purposes
    int getCurrentScore();

private:
    // Reference to a PigRoller object to simulate rolling the pigs
    PigRoller& pigRoller;

    // The score this player is playing to
    int targetPoints;

    // This player's threshold when rolling
    int threshold;

    // This player's starting score
    int startingPoints;

    // This player's current score
    int currentPoints;

    // This player's name
    std::string name;
};
