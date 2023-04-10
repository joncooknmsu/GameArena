//
// MSG: Player interface, with helper classes; each robot
// player class must inherit from and then implement the
// methods in the abstract Player class. The helper classes
// are simple data structures to make the interfaces cleaner.
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved
//

#ifndef Player_H
#define Player_H

#include <iostream>
#include <vector>

constexpr unsigned int PLAYER_SIZE = 32;
constexpr int MAX_MOVE = 3;

//
// A simple struct for an (x,y) coordinate pair
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
   Position pos; // prize position
   unsigned int value;    // prize value
   bool claimed; // true is this prize has already been picked up
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
   Position pos;
   enum { N = 1, NE, E, SE, S, SW, W, NW } lastDir;
};

//
// Generic Player Interface (all methods public, virtual, and =0, no data)
//
class Player
{
public:
   virtual ~Player() {};
   // draw your player: must be CENTERED on
   // player position and within a 16x16 pixel box
   virtual void draw() = 0;
   // update your player: you can move your player 0, 1, or 2 pixels in
   // each of the X and Y directions; you can use your given goal location,
   // the game drawing area, and the array of prizes to help
   // determine your direction; the LAST element in the prize array
   // is a NULL pointer (this tells you where the array ends, similar to a
   // character string. The array of obstacles is similar to the prize array;
   // the last element is a pointer value of 0; if your player moves into an
   // obstacle (any of your 16x16 is overlapping it) your player will be
   // disqualified;
   virtual void update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players) = 0;
   // The game engine will call this if you have claimed a prize
   virtual void prizeClaimed(const Prize& prize) = 0;
   // The game engine will call this to query your current position;
   // it must be your CENTER
   virtual Position currentPosition() = 0;
   // Game engine will call setStart() and setGoal() BEFORE starting the game
   virtual void setStart(Position start) = 0;
   virtual void setGoal(Position goal) = 0;
   // Game engine will call this to see if you are in attack mode; attack mode
   // costs one point of score for each turn, but if you overlap with another
   // player while in attack mode, you get some points
   virtual bool inAttackMode() = 0;
   virtual const char* name() = 0; // string that is your player's name
private:
};

#endif
