//
// The main game controller implementation
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//

#include "GameEngine.h"
#include <FL/fl_ask.H>
#include <iostream>
#include <stdlib.h>
#include <string>

std::ostream& operator<<(std::ostream& os, const Position& p)
{
    return os << "(" << p.x << "," << p.y << ")";
}

//
// Constructor: Does NOT create any players because the window selections
// still have to be made by the user
//
GameEngine::GameEngine(int X, int Y, int W, int H, const char* Label)
      : Fl_Widget(X, Y, W, H, Label), players(MAX_PLAYERS),
        playerStats(MAX_PLAYERS), prizes(NUM_PRIZES), obstacles(NUM_OBSTACLES)
{
    unsigned int i;
    upperLeft.x = X;
    upperLeft.y = Y;
    lowerRight.x = X + W - 1;
    lowerRight.y = Y + H - 1;
    for (i = 0; i < NUM_PRIZES; i++)
        prizes[i] = NULL;
    for (i = 0; i < NUM_OBSTACLES; i++)
        obstacles[i] = NULL;
    for (i = 0; i < MAX_PLAYERS; i++)
        players[i] = NULL;
    playerFactory = new PlayerFactory();
    std::vector<std::string> names = playerFactory->allPlayerNames();
    // debug output
    //vector<string>::iterator namesI = names.begin();
    //while (namesI != names.end()) {
    //   cout << "Player: " << *namesI << endl;
    //   namesI++;
    //}
    newGame(); // initialize the first game
}

bool GameEngine::overlap(Position low1, Position high1, Position low2,
                         Position high2)
{
    bool overlapInX = false;
    bool overlapInY = false;
    if (low2.x <= high1.x + PLAYER_SIZE && high2.x + PLAYER_SIZE >= low1.x)
        overlapInX = true;
    if (low2.y <= high1.y + PLAYER_SIZE && high2.y + PLAYER_SIZE >= low1.y)
        overlapInY = true;
    if (overlapInX && overlapInY)
        return true;
    else
        return false;
}

//
// Starts a new game: basically regenerates a new set of prizes
// and deletes all the players
//
void GameEngine::newGame()
{
    unsigned int i;
    unsigned int j;
    bool again = false;

    for (i = 0; i < NUM_OBSTACLES; i++) {
        if (obstacles[i])
            delete obstacles[i];
        obstacles[i] = new Obstacle();
        do {
            again = false;
            obstacles[i]->low.x =
                  (random() %
                   (lowerRight.x - upperLeft.x -
                    (MAX_OBSTACLE_WIDTH + MIN_OBSTACLE_WIDTH + PLAYER_SIZE))) +
                  upperLeft.x + MIN_OBSTACLE_WIDTH;
            obstacles[i]->low.y =
                  (random() % (lowerRight.y - upperLeft.y -
                               (MAX_OBSTACLE_HEIGHT + MIN_OBSTACLE_HEIGHT +
                                PLAYER_SIZE))) +
                  upperLeft.y + MIN_OBSTACLE_HEIGHT;
            obstacles[i]->high.x =
                  obstacles[i]->low.x +
                  (random() % MAX_OBSTACLE_WIDTH + MIN_OBSTACLE_WIDTH);
            obstacles[i]->high.y =
                  obstacles[i]->low.y +
                  (random() % MAX_OBSTACLE_HEIGHT + MIN_OBSTACLE_HEIGHT);
            for (j = 0; j < i; j++) {
                if (overlap(obstacles[j]->low, obstacles[j]->high,
                            obstacles[i]->low, obstacles[i]->high)) {
                    std::cout << "Overlapping obstacles!! regenerate\n";
                    again = true;
                    break;
                }
            }
            std::cout << "Obstacle: " << obstacles[i]->low << obstacles[i]->high
                      << std::endl;
        } while (again);
    }
    obstacles[i] = NULL; // Important!

    for (i = 0; i < NUM_PRIZES; i++) {
        if (prizes[i])
            delete prizes[i];
        prizes[i] = new Prize();
        prizes[i]->value = (random() % MAX_PRIZE_VALUE) + MIN_PRIZE_VALUE;
        prizes[i]->claimed = false;
        do {
            Position pl, ph;
            again = false;
            prizes[i]->pos.x =
                  (random() % (lowerRight.x - upperLeft.x - PRIZE_SIZE)) +
                  upperLeft.x + PRIZE_SIZE;
            prizes[i]->pos.y =
                  (random() % (lowerRight.y - upperLeft.y - PRIZE_SIZE)) +
                  upperLeft.y + PRIZE_SIZE;
            pl.x = prizes[i]->pos.x - PRIZE_SIZE / 2;
            pl.y = prizes[i]->pos.y - PRIZE_SIZE / 2;
            ph.x = prizes[i]->pos.x + PRIZE_SIZE / 2;
            ph.y = prizes[i]->pos.y + PRIZE_SIZE / 2;
            for (j = 0; j < NUM_OBSTACLES && obstacles[j]; j++) {
                if (overlap(obstacles[j]->low, obstacles[j]->high, pl, ph)) {
                    std::cout
                          << "Overlapping obstacle/prize!! regenerate prize\n";
                    again = true;
                    break;
                }
            }
        } while (again);
    }
    prizes[i] = NULL; // Important!

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i])
            delete players[i];
        players[i] = NULL;
        playerStats[i] = {0, {0, 0}, false};
    }
    numGoalsReached = 0;
    numPlayers = 0;
}

//
// give the windowing code the list of possible players
//
std::vector<std::string> GameEngine::playerNames()
{
    return playerFactory->allPlayerNames();
}

//
// Create and initialize the player playerNum
// - parameter id is useless, we should remove it
//
void GameEngine::setPlayer(int playerNum, int id, std::string name)
{
    Position start, goal;
    std::cout << "GE: set player " << playerNum << ": " << id << "-" << name
              << std::endl;
    if (playerNum < 0 || playerNum >= MAX_PLAYERS) {
        std::cerr << "GE Error: bad player num " << playerNum << std::endl;
        return;
    }
    if (playerNum % 2 == 0) {
        start.x = upperLeft.x + PLAYER_SIZE;
        goal.x = lowerRight.x - PLAYER_SIZE;
    } else {
        start.x = lowerRight.x - PLAYER_SIZE;
        goal.x = upperLeft.x + PLAYER_SIZE;
    }
    if (playerNum < 2) {
        start.y = upperLeft.y + PLAYER_SIZE;
        goal.y = lowerRight.y - PLAYER_SIZE;
    } else {
        start.y = lowerRight.y - PLAYER_SIZE;
        goal.y = upperLeft.y + PLAYER_SIZE;
    }
    players[playerNum] =
          playerFactory->createPlayer(name, playerNum, start, goal);
    if (!players[playerNum]) {
        std::cerr << "GE Error: player (" << name << ") not found!\n";
        return;
    }
    playerStats[playerNum].score = 0;
    playerStats[playerNum].goal = goal;
    playerStats[playerNum].atGoal = false;
    playerStats[playerNum].prev = start;
    playerStats[playerNum].info.id = playerNum;
    playerStats[playerNum].info.pos = start;
    playerStats[playerNum].info.lastDir = PlayerInfo::N;
    numPlayers++;
}

//
// Draw the current game state
//
void GameEngine::draw()
{
    unsigned int i;
    // get widget (playing area) dimensions
    upperLeft.x = x();            // upper left corner X
    upperLeft.y = y();            // upper left corner Y
    lowerRight.x = x() + w() - 1; // w() gives widget width
    lowerRight.y = y() + h() - 1; // h() gives widget height
    // Draw corner IDs
    fl_draw("0", upperLeft.x + 5, upperLeft.y + 15);
    fl_draw("1", lowerRight.x - 15, upperLeft.y + 15);
    fl_draw("2", upperLeft.x + 5, lowerRight.y - 5);
    fl_draw("3", lowerRight.x - 15, lowerRight.y - 5);
    // debug message
    //std::cerr << "Drawing my widget area! (" << upperLeft.x << "," << upperLeft.y
    //     << ") to (" << lowerRight.x << "," << lowerRight.y << ")" << endl;
    // draw the playing area border
    fl_color(FL_DARK_GREEN);
    fl_line(upperLeft.x, upperLeft.y, upperLeft.x, lowerRight.y);
    fl_line(lowerRight.x, upperLeft.y, lowerRight.x, lowerRight.y);
    fl_line(upperLeft.x, upperLeft.y, lowerRight.x, upperLeft.y);
    fl_line(upperLeft.x, lowerRight.y, lowerRight.x, lowerRight.y);
    // Draw the prizes
    for (i = 0; i < NUM_PRIZES; i++) {
        if (prizes[i]->claimed)
            fl_color(FL_RED);
        else
            fl_color(FL_GREEN);
        fl_rectf(prizes[i]->pos.x - PRIZE_SIZE / 2,
                 prizes[i]->pos.y - PRIZE_SIZE / 2, PRIZE_SIZE, PRIZE_SIZE);
    }
    // Draw the obstacles
    fl_color(FL_YELLOW);
    for (i = 0; i < NUM_OBSTACLES; i++) {
        fl_rectf(obstacles[i]->low.x, obstacles[i]->low.y,
                 obstacles[i]->high.x - obstacles[i]->low.x + 1,
                 obstacles[i]->high.y - obstacles[i]->low.y + 1);
    }
    // Draw the players
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i] && !playerStats[i].atGoal)
            players[i]->draw();
    }
}

// absolute value: Use in prize acquisition checking
#define ABSDIFF(x, y)                                                          \
    (((x) >= (y)) ? (((int)x) - ((int)(y))) : (((int)y) - ((int)(x))))

//
// Update the game state to a new state
//
void GameEngine::update()
{
    unsigned int i, p;
    GameArea area;
    Position oldPos, newPos;
    std::vector<Prize const*> cPrizes(prizes.size());
    for (i = 0; i < prizes.size(); i++)
        cPrizes[i] = prizes[i];
    std::vector<Obstacle const*> cObstacles(obstacles.size());
    for (i = 0; i < obstacles.size(); i++)
        cObstacles[i] = obstacles[i];
    std::vector<PlayerInfo const*> cPlayers(numPlayers);
    for (i = 0; i < numPlayers; i++)
        cPlayers[i] = &(playerStats[i].info);
    // If game over, no more updates
    if (numGoalsReached == numPlayers)
        return;
    area.low = upperLeft;
    area.high = lowerRight;
    // iterate through all players
    for (p = 0; p < MAX_PLAYERS; p++) {
        // if no player at this position, skip
        if (!players[p] || playerStats[p].atGoal)
            continue;
        // tell player to update itself, and check for illegal moves
        oldPos = players[p]->currentPosition();
        players[p]->update(area, cPrizes, cObstacles, cPlayers);
        newPos = players[p]->currentPosition();
        if (ABSDIFF(oldPos.x, newPos.x) > (MAX_MOVE) ||
            ABSDIFF(oldPos.y, newPos.y) > (MAX_MOVE)) {
            std::cerr << "Player " << p
                      << " tries to move to far! Penalty of -1!"
                      << "(" << oldPos << ")"
                      << "(" << newPos << ")\n";
            playerStats[p].score--;
        }
        // now check to see if player landed on any prizes (+/- 1 pixel)
        for (i = 0; i < NUM_PRIZES; i++) {
            if (!prizes[i]->claimed &&
                ABSDIFF(prizes[i]->pos.x, newPos.x) <= 1 &&
                ABSDIFF(prizes[i]->pos.y, newPos.y) <= 1) {
                prizes[i]->claimed = true;
                players[p]->prizeClaimed(*prizes[i]);
                std::cerr << "Player " << p << " claimed a prize!\n";
                playerStats[p].score += prizes[i]->value;
            }
        }
        // now check to see if player hit any obstacle
        for (i = 0; i < NUM_OBSTACLES; i++) {
            Position olow = obstacles[i]->low;
            Position ohigh = obstacles[i]->high;
            // technically PLAYER_SIZE/2 should be the border, but let's be generous
            if (newPos.x > olow.x - PLAYER_SIZE / 4 &&
                newPos.x < ohigh.x + PLAYER_SIZE / 4 &&
                newPos.y > olow.y - PLAYER_SIZE / 4 &&
                newPos.y < ohigh.y + PLAYER_SIZE / 4) {
                std::cerr << "Player " << p << " hit an obstacle!\n";
                playerStats[p].score -= OBSTACLE_HIT_PENALTY;
            }
        }
        // Check to see if player reached their goal (+/- 1 pixel)
        if (ABSDIFF(playerStats[p].goal.x, newPos.x) <= 1 &&
            ABSDIFF(playerStats[p].goal.y, newPos.y) <= 1) {
            std::cerr << "Player " << p << " reached their goal!\n";
            playerStats[p].atGoal = true;
            if (numGoalsReached == 0)
                playerStats[p].score += FIRST_FINISH_VALUE;
            else if (numGoalsReached == 1)
                playerStats[p].score += SECOND_FINISH_VALUE;
            else if (numGoalsReached == 2)
                playerStats[p].score += THIRD_FINISH_VALUE;
            else
                playerStats[p].score += FOURTH_FINISH_VALUE;
            numGoalsReached++;
        }
        // count cost of attack mode
        if (players[p]->inAttackMode()) {
            playerStats[p].score -= 1;
        }
    }
    // Check players for intersecting with each other and
    // see if attack mode is on; if it is, award points
    for (unsigned int i1 = 0; i1 < MAX_PLAYERS; i1++) {
        if (!players[i1])
            continue;
        for (unsigned int i2 = i1 + 1; i2 < MAX_PLAYERS; i2++) {
            if (!players[i2])
                continue;
            Player& p1 = *players[i1];
            Player& p2 = *players[i2];
            Position pos1 = p1.currentPosition();
            Position pos2 = p2.currentPosition();
            if (ABSDIFF(pos1.x, pos2.x) < 3 && ABSDIFF(pos1.y, pos2.y) < 3) {
                //std::cerr << "Players overlap!\n";
                if (p1.inAttackMode() && !p2.inAttackMode()) {
                    std::cerr << p1.name() << " attacks " << p2.name() << "!\n";
                    playerStats[i2].score -= ATTACK_VALUE;
                    playerStats[i1].score += ATTACK_VALUE;
                } else if (!p1.inAttackMode() && p2.inAttackMode()) {
                    std::cerr << p2.name() << " attacks " << p1.name() << "!\n";
                    playerStats[i2].score += ATTACK_VALUE;
                    playerStats[i1].score -= ATTACK_VALUE;
                } else {
                    std::cerr << p1.name() << " overlaps " << p2.name()
                              << "!\n";
                }
            }
        }
    }
    // Update player positions in the info record
    for (unsigned int i = 0; i < MAX_PLAYERS; i++) {
        if (!players[i])
            continue;
        playerStats[i].info.pos = players[i]->currentPosition();
    }
    // now that we have updated the game state, tell FLTK
    // to redraw the window (FLTK will eventually call our
    // draw() method, and we'll draw the new game state in there
    Fl::redraw();
}

void GameEngine::showGameStats()
{
    unsigned int i;
    /** 
    // stdout debugging output
    std::cout << "Game Results\n--------------\n";
    for (i=0; i < MAX_PLAYERS; i++) {
       if (players[i]) {
          std::cout << "Player " << i << " " << players[i]->name() << " Score: " 
              << playerInfo[i].score << std::endl;
       }
    }
    **/
    std::string msg = "Game Results\n-------------------\n";
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (players[i]) {
            msg += "Player " + std::to_string((long long)i) + " " +
                   players[i]->name() + " Score: " +
                   std::to_string((long long)playerStats[i].score) + "\n";
        }
    }
    fl_message("%s", msg.c_str());
}
