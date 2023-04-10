//
// Example player code -- a little slow
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#include "PlayerJonslow.h"
#include <iostream>

using namespace std;

//
// Constructor
//
//PlayerJonslow::PlayerJonslow(const Position initial, const Position goal)
PlayerJonslow::PlayerJonslow(unsigned int id, Position start, Position goal)
      : Player(id, start, goal)
{
    /*
   pos = initial;
   this->goal = goal;
   if (goal.x > pos.x) 
      dir.x = 2;
   else
      dir.x = -2;
   if (goal.y > pos.y) 
      dir.y = 2;
   else
      dir.y = -2;   
*/
    dir.x = 0;
    dir.y = 0;
    pos = start;
    //color = random() & 0xffffff00;
    color = FL_BLUE;
    chomp = 0;
}

//
// Draw the current game state
//
void PlayerJonslow::draw()
{
    fl_color(color);
    if (chomp >= 20)
        // draw closed mouth
        fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2, PLAYER_SIZE,
               PLAYER_SIZE, 0, 360);
    else {
        // draw open mouth (directional)
        if (lastPos.x < pos.x && lastPos.y < pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, -10, 290);
        else if (lastPos.x > pos.x && lastPos.y < pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, -100, 200);
        else if (lastPos.x < pos.x && lastPos.y > pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, 70, 370);
        else if (lastPos.x > pos.x && lastPos.y > pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, 160, 460);
        else if (lastPos.x == pos.x && lastPos.y > pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, 120, 420);
        else if (lastPos.x == pos.x && lastPos.y < pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, -60, 240);
        else if (lastPos.x < pos.x && lastPos.y == pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, 10, 310);
        else if (lastPos.x > pos.x && lastPos.y == pos.y)
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, -150, 150);
        else
            fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2,
                   PLAYER_SIZE, PLAYER_SIZE, 10, 360);
    }
    if (++chomp > 27)
        chomp = 0;
}

//
// Update the game state to a new state
//
void PlayerJonslow::update(const GameArea& area,
                           const std::vector<Prize const*> prizes,
                           const std::vector<Obstacle const*> obstacles,
                           const std::vector<PlayerInfo const*> players)
{
    // update the game state: in this case, just update
    // the position of the bouncing PlayerJonslow
    int dx, dy;
    unsigned int i;
    Position target = goal;
    for (i = 0; i < prizes.size(); i++) {
        if (!prizes[i]->claimed) {
            target = prizes[i]->pos;
            break;
        }
    }
    dx = target.x - pos.x;
    dy = target.y - pos.y;
    if (dx > (MAX_MOVE - 1))
        dx = MAX_MOVE - 1;
    if (dx < -(MAX_MOVE - 1))
        dx = -(MAX_MOVE - 1);
    if (dy > (MAX_MOVE - 1))
        dy = (MAX_MOVE - 1);
    if (dy < -(MAX_MOVE - 1))
        dy = -(MAX_MOVE - 1);
    lastPos = pos;
    pos.x += dx;
    pos.y += dy;
    // should not need window boundary testing, because
    // we always are going towards a target in the window
    /*
   if (posX < area.low.x) {
      posX = area.low.x;
      dirX = -dirX;
   } else if (posX > area.high.x-size) {
      posX = area.high.x-size;
      dirX = -dirX;
   }
   if (posY < area.low.y) {
      posY = area.low.y;
      dirY = -dirY;
   } else if (posY > area.high.y-size) {
      posY = area.high.y-size;
      dirY = -dirY;
   }
   */
}

void PlayerJonslow::prizeClaimed(const Prize& prize)
{
    cerr << "Hey I claimed of prize of value " << prize.value << endl;
}
