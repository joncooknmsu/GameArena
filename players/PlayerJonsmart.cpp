//
// Example player code -- a little bit of smarts
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#include "PlayerJonsmart.h"
#include <iostream>

using namespace std;

//
// Constructor
//
//PlayerJonsmart::PlayerJonsmart(const Position initial, const Position goal)
PlayerJonsmart::PlayerJonsmart(unsigned int id, Position start, Position goal)
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
    color = FL_GREEN;
    haveTarget = false;
    obstacleTarget = {0, 0};
}

//
// Draw the current game state
//
void PlayerJonsmart::draw()
{
    fl_color(color);
    fl_pie(pos.x - PLAYER_SIZE / 2, pos.y - PLAYER_SIZE / 2, PLAYER_SIZE,
           PLAYER_SIZE, 0, 360);
    fl_color(FL_BLACK);
    fl_pie(pos.x - 4, pos.y - 4, 2, 3, 0, 360);
    fl_pie(pos.x + 1, pos.y - 4, 2, 3, 0, 360);
    fl_line(pos.x - 2, pos.y + 2, pos.x + 2, pos.y + 2);
}

#define POS_DIST(p1, p2)                                                       \
    ((((p1).x > (p2).x) ? ((p1).x - (p2).x) : ((p2).x - (p1).x)) +             \
     (((p1).y > (p2).y) ? ((p1).y - (p2).y) : ((p2).y - (p1).y)))

//
// Update the game state to a new state
//
void PlayerJonsmart::update(const GameArea& area,
                            const std::vector<Prize const*> prizes,
                            const std::vector<Obstacle const*> obstacles,
                            const std::vector<PlayerInfo const*> players)
{
    int dx, dy, curDistance, newDistance;
    unsigned int i;
    Position target = goal;
    if (haveTarget) {
        if (pos.x == obstacleTarget.x && pos.y == obstacleTarget.y)
            haveTarget = false;
        else
            target = obstacleTarget;
    }
    for (i = 0; !haveTarget && i < obstacles.size(); i++) {
        Position olow = obstacles[i]->low;
        Position ohigh = obstacles[i]->high;
        if (pos.x > (olow.x - PLAYER_SIZE / 2) &&
            pos.x < (ohigh.x + PLAYER_SIZE / 2) &&
            pos.y > (olow.y - PLAYER_SIZE / 2) &&
            pos.y < (ohigh.y + PLAYER_SIZE / 2)) {
            target = pos;
            //if (pos.x < (olow.x+ohigh.x)/2)
            if (pos.y < olow.y)
                target.x = ohigh.x + PLAYER_SIZE;
            else if (pos.y > ohigh.y)
                target.x = olow.x - PLAYER_SIZE;
            if (pos.x < olow.x)
                target.y = olow.y - PLAYER_SIZE;
            else if (pos.x > ohigh.x)
                target.y = ohigh.y + PLAYER_SIZE;
            //skipCount = 50;
            obstacleTarget = target;
            haveTarget = true;
            //return;
        }
    }
    curDistance = 1000000; // impossibly large number
    for (i = 0; !haveTarget && i < prizes.size(); i++) {
        if (!prizes[i]->claimed) { // && !skipCount) {
            newDistance = POS_DIST(pos, prizes[i]->pos);
            if (newDistance < curDistance) {
                target = prizes[i]->pos;
                curDistance = newDistance;
            }
            //break;
        }
    }
    //if (skipCount) {
    //   skipCount--;
    //   target.x = (area.high.x-area.low.x)/2;
    //   target.y = (area.high.y-area.low.y)/2;
    //}
    dx = target.x - pos.x;
    dy = target.y - pos.y;
    if (dx > (MAX_MOVE))
        dx = (MAX_MOVE);
    if (dx < -(MAX_MOVE))
        dx = -(MAX_MOVE);
    if (dy > (MAX_MOVE))
        dy = (MAX_MOVE);
    if (dy < -(MAX_MOVE))
        dy = -(MAX_MOVE);
    //if (skipCount) dx = 0;
    pos.x += dx;
    pos.y += dy;
}

void PlayerJonsmart::prizeClaimed(const Prize& prize)
{
    cerr << "Hey I claimed of prize of value " << prize.value << endl;
}
