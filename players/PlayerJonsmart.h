//
// Example player code -- a little bit of smarts
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#ifndef PLAYER_JONSMART_H
#define PLAYER_JONSMART_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <Player.h>

class PlayerJonsmart : public Player
{
 public:
    //PlayerJonsmart(const Position initial, const Position goal);
    PlayerJonsmart(unsigned int id, Position start, Position goal);
    virtual void draw();
    virtual void update(const GameArea& area,
                        const std::vector<Prize const*> prizes,
                        const std::vector<Obstacle const*> obstacles,
                        const std::vector<PlayerInfo const*> players);
    virtual void prizeClaimed(const Prize& prize);
    virtual Position currentPosition() { return pos; }
    virtual const char* name() { return "Jonsmart"; }
    virtual bool inAttackMode() { return false; }
 private:
    Position pos, dir;
    int size;
    Fl_Color color;
    bool haveTarget;
    Position obstacleTarget;
};

#endif
