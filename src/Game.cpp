#include "Game.h"
#include <windows.h>
#include <thread>
#include <chrono>

Game::Game(int w, int h) : width(w), height(h), food(w, h), state(MENU), score(0), gameOver(false), skipCollisionCheckThisFrame(false) {
    renderer = new Renderer(w + 30, h + 3); // +30 for info panel on right
    food.generate(snake.getBody());
}

Game::~Game() {
    delete renderer;
}

void Game::run() {
    while (!gameOver) {
        handleInput();
        if (state == PLAYING) {
            update();
            // Check collisions, but skip if we just ate food (protected frame)
            if (state == PLAYING && !skipCollisionCheckThisFrame) {
                checkCollisions();
            }
            // Reset the skip flag after this frame
            skipCollisionCheckThisFrame = false;
        }
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::update() {
    snake.move();
    if (snake.getHead() == food.getPosition()) {
        snake.grow();
        score += 10;
        food.generate(snake.getBody());
        // Skip collision check this frame to protect newly generated food
        skipCollisionCheckThisFrame = true;
    }
}

void Game::render() {
    renderer->clear();
    drawBorder();

    // Draw snake
    for (size_t i = 1; i < snake.getBody().size(); ++i) {
        const auto& p = snake.getBody()[i];
        renderer->drawChar(p.x + 1, p.y + 1, 'o');
    }
    // Draw head
    Point head = snake.getHead();
    renderer->drawChar(head.x + 1, head.y + 1, '@');

    // Draw food
    Point foodPos = food.getPosition();
    renderer->drawChar(foodPos.x + 1, foodPos.y + 1, '*');

    drawScore();
    drawGameInfo();

    if (state == GAME_OVER) {
        renderer->drawText(width / 2 - 4, height / 2, "GAME OVER!");
    } else if (state == PAUSED) {
        renderer->drawText(width / 2 - 4, height / 2, "P A U S E D");
    }

    renderer->render();
    renderer->swapBuffers();
}

void Game::handleInput() {
    // Get raw keyboard input - single point of input
    char key = Input::getRawInput();
    if (key == 0) return;  // No input
    
    // Convert to lowercase for easier comparison
    char keyLower = (key >= 'A' && key <= 'Z') ? (key + 32) : key;
    
    // Handle direction input (W/A/S/D)
    if (keyLower == 'w') {
        if (state == MENU) state = PLAYING;
        if (state == PLAYING) snake.setDirection(UP);
    }
    else if (keyLower == 'a') {
        if (state == MENU) state = PLAYING;
        if (state == PLAYING) snake.setDirection(LEFT);
    }
    else if (keyLower == 's') {
        if (state == MENU) state = PLAYING;
        if (state == PLAYING) snake.setDirection(DOWN);
    }
    else if (keyLower == 'd') {
        if (state == MENU) state = PLAYING;
        if (state == PLAYING) snake.setDirection(RIGHT);
    }
    // Handle function keys
    else if (keyLower == 'p') {
        // Pause/Resume toggle
        if (state == PLAYING) {
            state = PAUSED;
        } else if (state == PAUSED) {
            state = PLAYING;
        }
    }
    else if (keyLower == 'c') {
        // Save game
        if (state != GAME_OVER) {
            save("save.txt");
        }
    }
    else if (keyLower == 'v') {
        // Load game
        load("save.txt");
    }
    else if (keyLower == 'x') {
        // Exit game (only in pause or game over states)
        if (state == PAUSED || state == GAME_OVER) {
            gameOver = true;
        }
    }
}

void Game::checkCollisions() {
    if (snake.checkCollision(width, height) || snake.checkSelfCollision()) {
        state = GAME_OVER;
        gameOver = true;
    }
}

void Game::drawBorder() {
    for (int x = 0; x < width + 2; ++x) {
        renderer->drawChar(x, 0, '#');
        renderer->drawChar(x, height + 1, '#');
    }
    for (int y = 0; y < height + 2; ++y) {
        renderer->drawChar(0, y, '#');
        renderer->drawChar(width + 1, y, '#');
    }
}

void Game::drawScore() {
    std::string scoreText = "Score: " + std::to_string(score);
    renderer->drawText(1, 0, scoreText);
}

void Game::drawGameInfo() {
    int infoX = width + 4;
    renderer->drawText(infoX, 2, "=== Game Info ===");
    renderer->drawText(infoX, 4, "Controls:");
    renderer->drawText(infoX, 5, "W/A/S/D: Move");
    renderer->drawText(infoX, 6, "P: Pause/Resume");
    renderer->drawText(infoX, 7, "C: Save Game");
    renderer->drawText(infoX, 8, "V: Load Game");
    renderer->drawText(infoX, 9, "X: Exit");
    
    renderer->drawText(infoX, 11, "Game Status:");
    std::string statusText;
    if (state == PLAYING) statusText = "Playing";
    else if (state == PAUSED) statusText = "Paused";
    else if (state == GAME_OVER) statusText = "Game Over";
    else statusText = "Menu";
    renderer->drawText(infoX, 12, statusText);
}

void Game::save(const std::string& filename) {
    SaveData gs;
    gs.snakeBody = snake.getBody();
    gs.direction = snake.getDirection();
    gs.foodPos = food.getPosition();
    gs.score = score;
    SaveSystem::saveGame(filename, gs);
}

void Game::load(const std::string& filename) {
    SaveData gs;
    if (SaveSystem::loadGame(filename, gs)) {
        snake.setBody(gs.snakeBody);
        snake.setDirection(gs.direction);
        food.setPosition(gs.foodPos);
        score = gs.score;
        state = PLAYING;
    }
}