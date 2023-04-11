//
// Player interface, with helper classes; each robot
// player class must inherit from and then implement the
// methods in the abstract Player class. The helper classes
// are simple data structures to make the interfaces cleaner.
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//

#ifndef Player_H
#define Player_H

#include <iostream>
#include <vector>

// must draw player image in a square of this size
constexpr unsigned int PLAYER_SIZE = 32;
// maximum position move in either or both x,y directions
constexpr int MAX_MOVE = 3;

//
// A simple struct for an (x,y) coordinate pair
// - with an ostream output formatter
//
class Position
{
 public:
    unsigned int x;
    unsigned int y;
 private:
    friend std::ostream& operator<<(std::ostream& os, const Position& p);
};

//
// A simple struct containing the game drawing and moving area
// - Position low is the upper left corner, high is the lower right
//
class GameArea
{
 public:
    Position low;  // upper left corner (lowest x,y values)
    Position high; // lower right corner (highest x,y values)
};

//
// Simple struct to hold the info about a Prize;
//
class Prize
{
 public:
    Position pos;       // prize position
    unsigned int value; // prize value
    bool claimed;       // true is this prize has already been picked up
};

//
// A simple struct to hold information about an obstacle
// - obstacles are all rectangular
// - Position low is the upper left corner, high is the lower right
//
class Obstacle
{
 public:
    Position low;  // upper left corner (lowest x,y values)
    Position high; // lower right corner (highest x,y values)
};

// struct for info about the other players, just their
// position and their last direction
class PlayerInfo
{
 public:
    unsigned int id;
    Position pos;
    // last direction is not currently being used
    enum { N = 1, NE, E, SE, S, SW, W, NW } lastDir;
};

//
// Generic Player Interface (all methods public, virtual, and =0, no data)
//
class Player
{
 public:
    Player(unsigned int id, Position start, Position goal)
          : id(id), start(start), goal(goal){};
    virtual ~Player(){};
    // draw your player: must be CENTERED on
    // player position and within a PLAYER_SIZE pixel box
    virtual void draw() = 0;
    // update your player: you can move your player up to MAX_MOVE pixels in
    // each of the X and Y directions; you can use all of the parameter info
    // to help you decide where to move. A move is simply updating your own
    // position data, which is reported by the currentPosition() method.
    virtual void update(const GameArea& area,
                        const std::vector<Prize const*> prizes,
                        const std::vector<Obstacle const*> obstacles,
                        const std::vector<PlayerInfo const*> players) = 0;
    // The game engine will call this if you have claimed a prize; you can
    // implement it as an empty method, or you can use it to have fun like
    // draw something on your bot image
    virtual void prizeClaimed(const Prize& prize) = 0;
    // The game engine will call this to query your current position;
    // it must be your CENTER; if you move too far your bot will
    // receive penalties.
    virtual Position currentPosition() = 0;
    // Game engine will call this to see if you are in attack mode; attack mode
    // costs one point of score for each turn, but if you overlap with another
    // player while in attack mode, you get some points. True means you ARE in
    // attack mode, false means you are not.
    virtual bool inAttackMode() = 0;
    virtual const char* name() = 0; // string that is your player's name
 protected:
    unsigned int id;
    Position start;
    Position goal;
};

#endif
