//
// Example player code -- a default player
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#ifndef PLAYERJONCOOK_H
#define PLAYERJONCOOK_H
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <Player.h>

class JonCook : public Player
{
 public:
    JonCook(unsigned int id, Position start, Position goal);
    virtual void draw();
    virtual void update(const GameArea& area,
                        const std::vector<Prize const*> prizes,
                        const std::vector<Obstacle const*> obstacles,
                        const std::vector<PlayerInfo const*> players);
    virtual void prizeClaimed(const Prize& prize);
    virtual Position currentPosition() { return pos; }
    virtual const char* name() { return "JonCook"; }
    virtual bool inAttackMode() { return false; }
 private:
    Position pos, dir;
    int size;
    Fl_Color color;
};

#endif
