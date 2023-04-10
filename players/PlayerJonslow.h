
#ifndef PLAYER_JONSLOW_H
#define PLAYER_JONSLOW_H
#include <Player.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class PlayerJonslow : public Player
{
public:
   //PlayerJonslow(const Position initial, const Position goal);
   PlayerJonslow();
   virtual void draw();
   virtual void update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players);
   virtual void prizeClaimed(const Prize& prize);
   virtual Position currentPosition() { return pos; }
   virtual void setStart(Position start) { pos = start; }
   virtual void setGoal(Position goal) { this->goal = goal; }
   virtual const char* name() { return "Jonslow"; }
   virtual bool inAttackMode() { return false; }
private:
   Position pos, dir, goal, lastPos;
   int size;
   Fl_Color color;
   int chomp;
};

#endif

