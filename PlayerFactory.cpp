//
//
// MSG: PlayerFactory class; this class is a factory for
// all of the different actual implementations of the Player robots
// - it instantiates each type of player by name (string), and also
//   provides a vector of strings of all the player names so that the
//   GUI can provide a selection list to the user
//
// Author: Jonathan Cook
// Copyright (C) 2013 Jonathan Cook. All rights reserved
//

#include <iostream>
#include "PlayerFactory.h"
#include "PlayerDefs.h"

//
// Create player objects by name
// - each unique player class needs to have an "else if" clause
//   exactly as the ones shown, except the correct player name
//   must be use in the string, and the correct class in the
//   "return new ..." statement.
//
Player* PlayerFactory::createPlayer(std::string playerName)
{
    if (!playerName.compare("Jon-slow")) {
        //std::cout << "creating player Jon-slow\n";
        return new PlayerJonslow();
    } else if (!playerName.compare("Jon-fast")) {
        //std::cout << "creating player Jon-fast\n";
        return new PlayerJonfast();
    } else if (!playerName.compare("Jon-smart")) {
        //std::cout << "creating player Jon-fast\n";
        return new PlayerJonsmart();
    }
    return NULL;
}

//
// Returns a list (vector) of all the players' names.
// - each player needs its name added here in one statement
//   exactly like the existing ones. This name MUST exactly
//   match the one used in createPlayer() above.
//
std::vector<std::string> PlayerFactory::allPlayerNames()
{
    std::vector<std::string> names;
    names.push_back("Jon-slow");
    names.push_back("Jon-fast");
    names.push_back("Jon-smart");
    return names;
}
