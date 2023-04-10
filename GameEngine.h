//
// Game Engine: this is the main game controller class
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

//
// Game Engine: an object of this class is reponsible for "running"
// the game. It is an Fl_Widget and so is responsible for the window
// area that makes up the game area, and for informing FLTK that the
// window needs redrawn after the game state is updated (using Fl::redraw())
//

#include "GameParams.h"
#include "PlayerFactory.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>

// helper class that holds info about a player: its
// current score, goal, and whether it reached the goal
// yet or not
class PlayerStats
{
 public:
    int score;
    Position goal;
    bool atGoal;
    Position prev;
    PlayerInfo info;
};

//
// GameEngine inherits from Fl_Widget because it is responsible for
// the window area that the game is drawn on. It implements its own draw()
// method which gets invoked from the FLTK toolkit whenever the window
// needs redrawn.
//
class GameEngine : public Fl_Widget
{
 public:
    GameEngine(int X, int Y, int W, int H, const char* Label = 0);
    void newGame();
    std::vector<std::string> playerNames(); // return list of players
    void setPlayer(int playerNum, int id, std::string name); // set's the player
    void draw();   // draw the current game state
    void update(); // update to a new game state
    bool gameOver()
    {
        return (numPlayers > 0 && numGoalsReached == numPlayers);
    }
    void showGameStats();
    bool overlap(Position low1, Position high1, Position low2, Position high2);
 private:
    // upper left and lower right of animated drawing area
    Position upperLeft, lowerRight;
    // players
    std::vector<Player*> players;
    // GameEngine keeps its own stats on the players, does not trust
    // them to report accurately :-)
    std::vector<PlayerStats> playerStats;
    unsigned int numPlayers;
    unsigned int numGoalsReached;
    // player factory
    PlayerFactory* playerFactory;
    // prizes and obstacles
    std::vector<Prize*> prizes;
    std::vector<Obstacle*> obstacles;
};

#endif
