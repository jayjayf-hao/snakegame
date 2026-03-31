#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include "Renderer.h"
#include "Input.h"
#include "SaveSystem.h"
#include <string>

enum GameStatus { MENU, PLAYING, PAUSED, GAME_OVER };

class Game {
public:
    Game(int width, int height);
    ~Game();
    void run();
    void save(const std::string& filename);
    void load(const std::string& filename);

private:
    int width, height;
    Snake snake;
    Food food;
    Renderer* renderer;
    GameStatus state;
    int score;
    bool gameOver;
    bool skipCollisionCheckThisFrame;  // Protect frame after eating food

    void update();
    void render();
    void handleInput();
    void checkCollisions();
    void drawBorder();
    void drawScore();
    void drawGameInfo();
};

#endif // GAME_H