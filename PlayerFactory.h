//
// PlayerFactory header; this class is a factory for
// all of the different actual implementations of the Player robots
// - it instantiates each type of player by name (string), and also
//   provides a vector of strings of all the player names so that the
//   GUI can provide a selection list to the user
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//

#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

//
// This is a "factory" that creates the different player objects.
// An object factory is a well-known OO design "pattern" that isolates
// the creation of objects of various subclasses into one place.
// Our GameEngine object uses a PlayerFactory object to create the players
// that will participate in a game.
// - NOTE: the createPlayer() method returns a generic Player pointer, but
//   internally it creates objects of the specific player classes. This is
//   the beauty of inheritance and polymorphism!
//

#include "Player.h"
#include <string>
#include <vector>

class PlayerFactory
{
 public:
    Player* createPlayer(std::string playerName, unsigned int id,
                         Position start, Position goal);
    std::vector<std::string> allPlayerNames();
};

#endif
