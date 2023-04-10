
#include <iostream>
#include "PlayerJoncook.h"

using namespace std;

//
// Constructor
//
//PlayerJoncook::PlayerJoncook(const Position initial, const Position goal)
PlayerJoncook::PlayerJoncook()
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
   dir.x = 0; dir.y = 0;
   pos.x = 100; pos.y = 100;
   color = random() & 0xffffff00;
}


//
// Draw the current game state
//
void PlayerJoncook::draw() 
{
   fl_color(color);
   fl_pie(pos.x-PLAYER_SIZE/2, pos.y-PLAYER_SIZE/2, PLAYER_SIZE, PLAYER_SIZE, 0, 360);
}

//
// Update the game state to a new state
//
void PlayerJoncook::update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players)
{
   // update the game state: in this case, just update
   // the position of the bouncing PlayerJoncook
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
   if (dx > MAX_MOVE) dx = MAX_MOVE;
   if (dx < -MAX_MOVE) dx = -MAX_MOVE;
   if (dy > MAX_MOVE) dy = MAX_MOVE;
   if (dy < -MAX_MOVE) dy = -MAX_MOVE;
   pos.x += dx; pos.y += dy;
/*   if (posX < area.low.x) {
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

void PlayerJoncook::prizeClaimed(const Prize& prize) 
{
   cerr << "Hey I claimed of prize of value " << prize.value << endl;
}


