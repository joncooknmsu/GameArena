
#ifndef PLAYER_JONFAST_H
#define PLAYER_JONFAST_H
#include <Player.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

class PlayerJonfast : public Player
{
public:
   PlayerJonfast(unsigned int id, Position start, Position goal);
   virtual void draw();
   virtual void update(const GameArea& area, const std::vector<Prize const *> prizes,
      const std::vector<Obstacle const *> obstacles,
      const std::vector<PlayerInfo const *> players);
   virtual void prizeClaimed(const Prize& prize);
   virtual Position currentPosition() { return pos; }
   virtual const char* name() { return "Jonfast"; }
   virtual bool inAttackMode();
private:
   Position pos, dir;
   int size;
   Fl_Color color;
   bool haveTarget;
   bool attackMode;
   Position obstacleTarget;
};

#endif

