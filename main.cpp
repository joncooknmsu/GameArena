//
// Game main
//
// Author: Jonathan Cook
// Copyright (C) 2023 Jonathan Cook. All rights reserved.
//
#include "GUI.h"

//
// Program main: construct window and game object,
// then turn control over to GUI system
//
int main(int argc, char* argv[])
{
    if (--argc) {
        int randseed = atoi(argv[1]);
        srandom(randseed);
    }
    // create a GUI window object
    MainWindow* app = new MainWindow();
    if (!app) { /*suppress warning*/
    }
    // standard way to run an FLTK GUI app
    return (Fl::run());
}
