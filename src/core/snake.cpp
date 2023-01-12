#include "snake.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <deque>
#include <utility>

Snake::Snake(int start_x_pos, int start_y_pos) // start in center 
{
    x_pos = start_x_pos;
    y_pos = start_y_pos;
    direction = RIGHT;
    // init snake body with 5 parts
    for (int i = 0; i < 5; i++)
    {
        this->body.push_back(std::make_pair(x_pos - i, y_pos));
    }
    length = this->body.size();
}

Snake::~Snake() { }

void Snake::grow()
{
    auto tail = this->body.back();
    this->body.push_back(tail);
    this->length++;

}

void Snake::move(Direction direction)
{
    auto head = this->body.front();
    int dx = 0, dy = 0;
    switch (direction) {
        case Direction::UP:
            dy = -1;
            break;
        case Direction::DOWN:
            dy = 1;
            break;
        case Direction::LEFT:
            dx = -1;
            break;
        case Direction::RIGHT:
            dx = 1;
            break;
    }
    this->body.push_front(std::make_pair(head.first + dx, head.second + dy));
    this->body.pop_back();

}

int Snake::get_snek_x_pos()
{
    return x_pos;
}

int Snake::get_snek_y_pos()
{
    return y_pos;
}

int Snake::get_snek_length()
{
    return length;
}

void Snake::eat_apple()
{
    this->grow();
    this->score++;
}

void Snake::set_snek_x_pos(int x_pos)
{
    this->x_pos = x_pos;
}

void Snake::set_snek_y_pos(int y_pos)
{
    this->y_pos = y_pos;
}

