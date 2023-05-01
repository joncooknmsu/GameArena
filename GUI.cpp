//
// GUI Classes Implementation
// This file contains the window construction code and the callback
// functions that connect to user widgets (and the timer callback)
//
// Author: Jonathan Cook
// Copyright (C) 2013 Jonathan Cook. All rights reserved.
//

#include "GUI.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//------------- MainWindow -------------------//

MainWindow::MainWindow()
      : Fl_Double_Window(WINDOW_WIDTH, WINDOW_HEIGHT, "CS 271 Playoff Arena")
{
    // begin window sub-components
    begin();
    // create menu bar
    menuBar = new MenuBar(*this);
    //fl_font(FL_HELVETICA_BOLD,30);
    // create drawing area object
    game = new GameEngine(0, 90, w(), h() - 90);
    // declare the drawing area to be resizable
    resizable(game);
    // create start/stop button
    startButton = new StartButton(*this);
    // create new game button, and connect to function
    newGameButton = new NewGameButton(*this);
    // Create all four player selection menus
    playerNames = game->playerNames();
    for (int pi = 0; pi < 4; pi++) {
        playerSelector[pi] = new PlayerSelector(pi, *this);
        std::vector<std::string>::iterator namesI = playerNames.begin();
        int i = 0;
        while (namesI != playerNames.end()) {
            //std::cout << "main:Player: " << *namesI << endl;
            playerSelector[pi]->add((*namesI).c_str(), 0,
                                    PlayerSelector::select, (void*)((long)i),
                                    0);
            namesI++;
            i++;
        }
    }
    // end window sub-components
    end();
    // display the window
    Fl::visual(FL_DOUBLE |
               FL_INDEX); // FLTK docs say: do this if double-buffering
    show();               //(argc, argv);
}

/**
* Uses the FLTK callback function model to springboard
* into an Object-Oriented model, calling the correct method
* for the menu selection.
**/
void MainWindow::dispatcher(Fl_Widget* w, void* selection)
{
    // std::cout << "Window event! (" << w << "," << selection << ")\n";
    switch ((long)selection) {
    case MainWindow::MENU_EXIT: {
        MenuBar* menu = dynamic_cast<MenuBar*>(w);
        menu->exitGame();
        break;
    }
    case MainWindow::START_BUTTON: {
        StartButton* button = dynamic_cast<StartButton*>(w);
        button->pushed();
        break;
    }
    case MainWindow::NEWGAME_BUTTON: {
        NewGameButton* button = dynamic_cast<NewGameButton*>(w);
        button->pushed();
        break;
    }
    }
    return;
}

/**
 * C function callback for timer
 * - unfortunately FLTK uses a plain C function, but we
 *   just springboard into an object method here
**/
void timerExpired(void* wp)
{
    // cast the void pointer back into a real MainWindow pointer
    MainWindow* app = (MainWindow*)wp;
    app->timerExpired();
}

void MainWindow::timerExpired()
{
    if (!game->gameOver()) {
        game->update();
        Fl::repeat_timeout(TIMER_RATE, ::timerExpired, this);
    } else {
        std::cout << "GAME OVER!!!\n";
        game->showGameStats();
    }
}

void MainWindow::showGameStats()
{
   game->showGameStats();
}

void MainWindow::initializeNewGame()
{
    game->newGame();
    for (int i = 0; i < 4; i++)
        playerSelector[i]->label("No Player");
    Fl::redraw(); // to update the window
}

//------------- PlayerSelector -------------------//

//
// Player selection callback -- this function is the
// callback for all four player selection widgets -- we
// check inside the function to see which widget it was
// that caused the callback to happen, so we know which
// player to set up
// - data value coming in as the void* is actually an
//   integer that represents the selection made from the
//   player drop-down menu
//
void PlayerSelector::select(Fl_Widget* w, void* data)
{
    PlayerSelector* selector = (PlayerSelector*)w;
    long pi = (long)data; // player index from data
    selector->select((int)pi);
    //cout << "Player selected: " << window.playerNames[pi] << endl;
    Fl::redraw(); // to update the selector label and show the player in the game
}

void PlayerSelector::select(int selection)
{
    app.game->setPlayer(playerNumber, selection, app.playerNames[selection]);
    label(app.playerNames[selection].c_str());
}

PlayerSelector::PlayerSelector(int pi, MainWindow& app)
      : Fl_Menu_Button(250 + pi * 190, 35, 185, 45, "NoPlayer"), app(app)
{
    playerNumber = pi;
    this->labelsize(22);
}

//------------- StartButton -------------------//

StartButton::StartButton(MainWindow& app)
      : Fl_Button(5, 35, 80, 45, "Start"), app(app)
{
    // connect this button up to the dispatcher, which will
    // invoke "pushed()" on the button when it is pushed
    callback(MainWindow::dispatcher, (void*)MainWindow::START_BUTTON);
    this->labelsize(22);
}

void StartButton::pushed()
{
    //int i; TODO: fix and re-instate button hiding
    static bool started = false;
    if (!started) {
        std::cout << "Starting game...\n";
        // set up our timer
        Fl::add_timeout(TIMER_RATE, ::timerExpired, &app);
        started = true;
        label("Stop");
        // ?? win->newGameButton->hide();
        // ?? for (i = 0; i < 4; i++)
        // ?? win->playerSelector[i]->hide();
    } else {
        std::cout << "Stopping game...\n";
        Fl::remove_timeout(::timerExpired, &app);
        started = false;
        label("Start");
        app.showGameStats();
        //win->newGameButton->show();
        //for (i = 0; i < 4; i++)
        //    win->playerSelector[i]->show();
    }
}

//------------- NewGameButton -------------------//

NewGameButton::NewGameButton(MainWindow& app)
      : Fl_Button(95, 35, 130, 45, "New Game"), app(app)
{
    // connect this button up to the dispatcher, which will
    // invoke "pushed()" on the button when it is pushed
    callback(MainWindow::dispatcher, (void*)MainWindow::NEWGAME_BUTTON);
    this->labelsize(22);
}

void NewGameButton::pushed()
{
    // tell main window to initialize a new game
    app.initializeNewGame();
}

//------------- MenuBar -------------------//

MenuBar::MenuBar(MainWindow& app) : Fl_Menu_Bar(0, 0, 800, 30), app(app)
{
    // Add File->Quit menu item and connect it to the dispatcher
    add("&File/&Quit", "^q", MainWindow::dispatcher,
        (void*)MainWindow::MENU_EXIT);
}

void MenuBar::exitGame()
{
    std::cout << "Program exiting...\n";
    // TODO: should call app.exit() here and do something
    exit(0); // this C library function immediately exits the program!
}
