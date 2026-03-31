#include "Snake.h"

Snake::Snake() : direction(STOP) {
    body.push_back(Point(10, 10)); // Initial position
}

void Snake::move() {
    if (direction == STOP) return;

    Point head = body.front();
    switch (direction) {
    case LEFT: head.x--; break;
    case RIGHT: head.x++; break;
    case UP: head.y--; break;
    case DOWN: head.y++; break;
    }
    body.push_front(head);
    body.pop_back();
}

void Snake::grow() {
    // Ensure we have a valid body
    if (!body.empty()) {
        // Add a copy of the last segment to extend the snake
        Point tail = body.back();
        body.push_back(tail);
    }
}

bool Snake::checkCollision(int width, int height) const {
    Point head = body.front();
    return head.x < 0 || head.x >= width || head.y < 0 || head.y >= height;
}

bool Snake::checkSelfCollision() const {
    Point head = body.front();
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i]) return true;
    }
    return false;
}

void Snake::setDirection(Direction dir) {
    // Prevent reversing into itself
    if ((direction == LEFT && dir == RIGHT) ||
        (direction == RIGHT && dir == LEFT) ||
        (direction == UP && dir == DOWN) ||
        (direction == DOWN && dir == UP)) {
        return;
    }
    direction = dir;
}

Direction Snake::getDirection() const {
    return direction;
}

const std::deque<Point>& Snake::getBody() const {
    return body;
}

Point Snake::getHead() const {
    return body.front();
}

void Snake::setBody(const std::deque<Point>& newBody) {
    body = newBody;
}