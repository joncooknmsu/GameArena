//
// Example player code -- a default player
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#include "JonCook.h"
#include <iostream>
#include <stdlib.h> // for random()

//
// Constructor
// - must invoke Player constructor as shown
//
JonCook::JonCook(unsigned int id, Position start, Position goal)
      : Player(id, start, goal)
{
    dir.x = 0;
    dir.y = 0;
    pos = start;
    color = random() & 0xffffff00;
}

//
// Draw my player image
//
void JonCook::draw()
{
    fl_color(color);
    fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2, PLAYER_SIZE,
           PLAYER_SIZE, 0, 360);
}

//
// Update my position
// - this bot just heads for its goal without doing anything else
//
void JonCook::update(const GameArea& area,
                           const std::vector<Prize const*> prizes,
                           const std::vector<Obstacle const*> obstacles,
                           const std::vector<PlayerInfo const*> players)
{
    int dx, dy;
    Position target = goal;
    dx = target.x - pos.x;
    dy = target.y - pos.y;
    if (dx > MAX_MOVE)
        dx = MAX_MOVE;
    if (dx < -MAX_MOVE)
        dx = -MAX_MOVE;
    if (dy > MAX_MOVE)
        dy = MAX_MOVE;
    if (dy < -MAX_MOVE)
        dy = -MAX_MOVE;
    pos.x += dx;
    pos.y += dy;
}

void JonCook::prizeClaimed(const Prize& prize)
{
    std::cerr << "Hey I (" << name() << ") claimed a prize of value " << prize.value << "!\n";
}
