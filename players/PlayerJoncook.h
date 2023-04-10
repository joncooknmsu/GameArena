
#ifndef PLAYERJONCOOK_H
#define PLAYERJONCOOK_H
#include <Player.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class PlayerJoncook : public Player
{
public:
   //PlayerJoncook(const Position initial, const Position goal);
   PlayerJoncook();
   virtual void draw();
   virtual void update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players);
   virtual void prizeClaimed(const Prize& prize);
   virtual Position currentPosition() { return pos; }
   virtual void setStart(Position start) { pos = start; }
   virtual void setGoal(Position goal) { this->goal = goal; }
   virtual const char* name() { return "Joncook"; }
   virtual bool inAttackMode() { return false; }
private:
   Position pos, dir, goal;
   int size;
   Fl_Color color;
};

#endif

