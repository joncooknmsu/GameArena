//
// MSG GUI classes header: a few GUI classes, the main window
// class should probably move to its own files
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved
//

#include <string>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "GameParams.h"
#include "GameEngine.h"

class MainWindow; // forward declaration

class MenuBar : public Fl_Menu_Bar
{
 public:
    MenuBar(MainWindow& app);
    void exitGame();
 private:
    MainWindow& app;
};

class StartButton : public Fl_Button
{
 public:
    StartButton(MainWindow& app);
    void pushed();
 private:
    MainWindow& app;
};

class NewGameButton : public Fl_Button
{
 public:
    NewGameButton(MainWindow& app);
    void pushed();
 private:
    MainWindow& app;
};

class PlayerSelector : public Fl_Menu_Button
{
 public:
    PlayerSelector(int pi, MainWindow& app);
    static void select(Fl_Widget* w, void* selection);
    void select(int selection);
 private:
    int playerNumber;
    MainWindow& app;
};

class MainWindow : public Fl_Double_Window
{
 public:
    MainWindow();
    void initializeNewGame();
    void timerExpired();
    // user action identifiers
    enum { MENU_EXIT = 1, START_BUTTON, NEWGAME_BUTTON };
    static void dispatcher(Fl_Widget* w, void* selection);
    GameEngine* game;
    std::vector<std::string> playerNames;
 private:
    MenuBar* menuBar;
    StartButton* startButton;
    NewGameButton* newGameButton;
    PlayerSelector* playerSelector[4];
};
