#include "Food.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Food::Food(int width, int height) : stageWidth(width), stageHeight(height) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    position.x = width / 2;
    position.y = height / 2;
}

void Food::generate(const std::deque<Point>& snakeBody) {
    // Build a set-like check for faster lookup
    bool found = false;
    int attempts = 0;
    const int MAX_RANDOM_ATTEMPTS = 300;
    
    // First, try random placement several times
    while (!found && attempts < MAX_RANDOM_ATTEMPTS) {
        int x = 1 + (std::rand() % (stageWidth - 2));
        int y = 1 + (std::rand() % (stageHeight - 2));
        
        // Check if this position is NOT occupied by snake
        bool occupied = false;
        for (size_t i = 0; i < snakeBody.size(); ++i) {
            if (snakeBody[i].x == x && snakeBody[i].y == y) {
                occupied = true;
                break;
            }
        }
        
        if (!occupied) {
            position.x = x;
            position.y = y;
            found = true;
        }
        attempts++;
    }
    
    // If random placement failed, do systematic search
    if (!found) {
        for (int y = 1; y < stageHeight - 1; ++y) {
            for (int x = 1; x < stageWidth - 1; ++x) {
                bool occupied = false;
                for (size_t i = 0; i < snakeBody.size(); ++i) {
                    if (snakeBody[i].x == x && snakeBody[i].y == y) {
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    position.x = x;
                    position.y = y;
                    return;
                }
            }
        }
        // Fallback: place at a fixed safe position
        // This should rarely happen unless snake fills entire board
        position.x = 1;
        position.y = 1;
    }
}

Point Food::getPosition() const {
    return position;
}

void Food::setPosition(const Point& pos) {
    position = pos;
}