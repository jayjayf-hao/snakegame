#include "Game.h"
#include <iostream>

int main() {
    const int WIDTH = 20;
    const int HEIGHT = 20;

    Game game(WIDTH, HEIGHT);
    game.run();

    return 0;
}