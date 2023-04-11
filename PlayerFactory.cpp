//
// PlayerFactory class; this class is a factory for
// all of the different actual implementations of the Player robots
// - it instantiates each type of player by name (string), and also
//   provides a vector of strings of all the player names so that the
//   GUI can provide a selection list to the user
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//

#include "PlayerFactory.h"
#include "PlayerDefs.h"
#include <iostream>

//
// Create player objects by name
// - each unique player class needs to have an "else if" clause
//   exactly as the ones shown, except the correct player name
//   must be use in the string, and the correct class in the
//   "return new ..." statement.
//
Player* PlayerFactory::createPlayer(std::string playerName, unsigned int id,
                                    Position start, Position goal)
{
    if (!playerName.compare("JonCook")) {
        return new JonCook(id, start, goal);
    } else if (!playerName.compare("JonSlow")) {
        return new JonSlow(id, start, goal);
    } else if (!playerName.compare("JonFast")) {
        return new JonFast(id, start, goal);
    } else if (!playerName.compare("JonSmart")) {
        return new JonSmart(id, start, goal);
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
    names.push_back("JonCook");
    names.push_back("JonSlow");
    names.push_back("JonFast");
    names.push_back("JonSmart");
    return names;
}
