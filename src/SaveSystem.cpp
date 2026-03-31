#include "SaveSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool SaveSystem::saveGame(const std::string& filename, const SaveData& state) {
    std::ofstream file(filename);
    if (!file) return false;

    file << "score=" << state.score << "\n";
    file << "direction=" << static_cast<int>(state.direction) << "\n";
    file << "food=" << state.foodPos.x << "," << state.foodPos.y << "\n";
    file << "snake=";
    for (size_t i = 0; i < state.snakeBody.size(); ++i) {
        file << state.snakeBody[i].x << "," << state.snakeBody[i].y;
        if (i < state.snakeBody.size() - 1) file << ";";
    }
    file << "\n";
    return true;
}

bool SaveSystem::loadGame(const std::string& filename, SaveData& state) {
    std::ifstream file(filename);
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            std::getline(iss, value);
            if (key == "score") {
                state.score = std::stoi(value);
            } else if (key == "direction") {
                state.direction = static_cast<Direction>(std::stoi(value));
            } else if (key == "food") {
                size_t comma = value.find(',');
                state.foodPos.x = std::stoi(value.substr(0, comma));
                state.foodPos.y = std::stoi(value.substr(comma + 1));
            } else if (key == "snake") {
                state.snakeBody.clear();
                std::istringstream snakeStream(value);
                std::string pointStr;
                while (std::getline(snakeStream, pointStr, ';')) {
                    size_t comma = pointStr.find(',');
                    int x = std::stoi(pointStr.substr(0, comma));
                    int y = std::stoi(pointStr.substr(comma + 1));
                    state.snakeBody.push_back(Point(x, y));
                }
            }
        }
    }
    return true;
}