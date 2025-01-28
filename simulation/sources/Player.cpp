#include "Player.h"

#include <iostream>

// Create a player object using a PigRoller object, the game's targetPoints, the turn threshold, and the score they start at
Player::Player(PigRoller &pigRoller, int targetPoints, int threshold, int startingPoints, std::string name)
  : pigRoller(pigRoller),
  targetPoints(targetPoints),
  threshold(threshold),
  startingPoints(startingPoints),
  currentPoints(startingPoints),
  name(name)
{}

Player::Player(const Player &other, int newThreshold)
  : pigRoller(other.pigRoller),
  targetPoints(other.targetPoints),
  threshold(newThreshold),
  startingPoints(other.startingPoints),
  currentPoints(other.currentPoints),
  name(other.name)
{}

// Rolls the pigs until either the threshold is reached or a pig out occurs; returns the score acquired
int Player::rollPigs()
{
    int scoreAcquired = 0;
    int rollResult = pigRoller.roll();

    while(rollResult != 0 && scoreAcquired < threshold) 
    {
        // std::cout << "Current roll: " << rollResult << std::endl;
        scoreAcquired += rollResult;
        // std::cout << "scoreAcquired: " << scoreAcquired << std::endl << std::endl;
        rollResult = pigRoller.roll();
    }

    if(rollResult != 0) 
    {
        currentPoints += scoreAcquired;
    } 
    else 
    {
        // std::cout << "pig out occurred\n";
    }

    return (rollResult != 0) ? scoreAcquired : 0;
}

// Reset this player's score to their starting score
void Player::reset()
{
    currentPoints = startingPoints;
}

// Whether or not this player has achieved a winning score
bool Player::hasWon()
{
    return currentPoints >= targetPoints;
}

std::string Player::getName()
{
    return name;
}

int Player::getThreshold()
{
    return threshold;
}

int Player::getTargetPoints()
{
    return targetPoints;
}

int Player::getCurrentScore()
{
    return currentPoints;
}
