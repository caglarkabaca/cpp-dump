#include <iostream>

#include "Engine.h"

int main()
{
    atom::Engine game;
    game.initWindow(800, 600, "ecemin hawali kubu");
    game.loop();
    return 0;
}