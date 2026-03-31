#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "Point.h"
#include "Direction.h"
#include <deque>
#include <string>

struct SaveData {
    std::deque<Point> snakeBody;
    Direction direction;
    Point foodPos;
    int score;
};

class SaveSystem {
public:
    static bool saveGame(const std::string& filename, const SaveData& state);
    static bool loadGame(const std::string& filename, SaveData& state);
};

#endif // SAVESYSTEM_H