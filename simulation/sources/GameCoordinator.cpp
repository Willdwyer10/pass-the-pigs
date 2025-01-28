#include "GameCoordinator.h"

#include "Pig.h"
#include "PigRoller.h"
#include "Player.h"
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
    // auto simulator = Simulator(pigRoller);

    // Determine the optimal threshold for games going to 100 points
    // auto numTurns = simulator.optimalThreshold(100);

    // NOTE: Just now for testing purposes
    /*auto player = Player(pigRoller, 100, 10, 85, "Bob");

    std::cout << "Current player score: " << player.getCurrentScore() << std::endl;
    auto result = player.rollPigs();
    std::cout << "Score returned after rolling pigs: " << result << std::endl;
    std::cout << "Current player score: " << player.getCurrentScore() << std::endl;
    std::cout << "Player has won: " << (player.hasWon() ? "true" : "false") << std::endl;
    player.reset();
    std::cout << "Player reset. Current score: " << player.getCurrentScore() << std::endl;
*/

    auto playerToOptimize = Player(pigRoller, 100, 10, 20, "Will");
    
    std::vector<Player> otherPlayers;
    otherPlayers.emplace_back(pigRoller, 100, 23, 40, "Matt   ");
    otherPlayers.emplace_back(pigRoller, 100, 18, 45, "Jon    ");
    otherPlayers.emplace_back(pigRoller, 100, 5, 55, "Triston");
    otherPlayers.emplace_back(pigRoller, 100, 28, 25, "Reeth  ");

    auto simulator = Simulator(otherPlayers);
    std::cout << "Here is the current state of the game:\n";
    std::cout << "\t" << playerToOptimize.getName() << " is at " << playerToOptimize.getCurrentScore() << ".\n";
    for(auto& player : otherPlayers)
    {
        std::cout << "\t" << player.getName() << " is at " << player.getCurrentScore() << " and generally passes the pigs after getting " << player.getThreshold() << " points.\n";
    }
    //std::cout << "player to optimize won " << simulator.simulateBatchOfGames(playerToOptimize) << "% of games" << std::endl;
    auto results = simulator.optimalThresholdForPlayer(playerToOptimize);
    std::cout << "To give Will the best chance of winning, he should pass the pigs once he hits " << results.second << " points.\n";
    std::cout << "Will has a " << results.first << "% chance of winning in this case\n";
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