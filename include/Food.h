#ifndef FOOD_H
#define FOOD_H

#include "Point.h"
#include <deque>

class Food {
public:
    Food(int width, int height);
    void generate(const std::deque<Point>& snakeBody);
    Point getPosition() const;
    void setPosition(const Point& pos);

private:
    Point position;
    int stageWidth, stageHeight;
};

#endif // FOOD_H