
#ifndef PLAYER_JONSMART_H
#define PLAYER_JONSMART_H
#include <Player.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class PlayerJonsmart : public Player
{
public:
   //PlayerJonsmart(const Position initial, const Position goal);
   PlayerJonsmart();
   virtual void draw();
   virtual void update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players);
   virtual void prizeClaimed(const Prize& prize);
   virtual Position currentPosition() { return pos; }
   virtual void setStart(Position start) { pos = start; }
   virtual void setGoal(Position goal) { this->goal = goal; }
   virtual const char* name() { return "Jonsmart"; }
   virtual bool inAttackMode() { return false; }
private:
   Position pos, dir, goal;
   int size;
   Fl_Color color;
   bool haveTarget;
   Position obstacleTarget;
};

#endif

