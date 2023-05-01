//
// Game Parameters
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#ifndef GAME_PARAMS_H
#define GAME_PARAMS_H

constexpr unsigned int OBSTACLE_HIT_PENALTY = 100;
constexpr unsigned int OUT_OF_BOUNDS_PENALTY = 100;
constexpr unsigned int TOO_FAST_PENALTY = 300;
constexpr unsigned int MIN_PRIZE_VALUE = 10;
constexpr unsigned int MAX_PRIZE_VALUE = 200;
constexpr unsigned int FIRST_FINISH_VALUE = 60;
constexpr unsigned int SECOND_FINISH_VALUE = 30;
constexpr unsigned int THIRD_FINISH_VALUE = 10;
constexpr unsigned int FOURTH_FINISH_VALUE = 2;
constexpr unsigned int ATTACK_VALUE = 20;
constexpr unsigned int ATTACK_OVERLAP = 6;

//constexpr unsigned int PLAYER_SIZE = 32; in Player.h
constexpr unsigned int PRIZE_SIZE = 32;

constexpr unsigned int NUM_PRIZES = 12;
constexpr unsigned int NUM_OBSTACLES = 5;

constexpr unsigned int MIN_OBSTACLE_WIDTH = 40;
constexpr unsigned int MAX_OBSTACLE_WIDTH = 120;
constexpr unsigned int MIN_OBSTACLE_HEIGHT = 40;
constexpr unsigned int MAX_OBSTACLE_HEIGHT = 120;

// Unsure if code allows this to be different!
constexpr int MAX_PLAYERS = 4;

// Game window size
constexpr unsigned int WINDOW_WIDTH = 1100;
constexpr unsigned int WINDOW_HEIGHT = 800;

// Game frame update rate
constexpr float TIMER_RATE = 0.025; // 40 times a second

#endif
