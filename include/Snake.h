#ifndef SNAKE_H
#define SNAKE_H

#include "Point.h"
#include "Direction.h"
#include <deque>

class Snake {
public:
    Snake();
    void move();
    void grow();
    bool checkCollision(int width, int height) const;
    bool checkSelfCollision() const;
    void setDirection(Direction dir);
    Direction getDirection() const;
    const std::deque<Point>& getBody() const;
    Point getHead() const;
    void setBody(const std::deque<Point>& body);

private:
    std::deque<Point> body;
    Direction direction;
};

#endif // SNAKE_H