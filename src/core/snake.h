#pragma once
#include "apple.h"
#include <vector>
#include <deque>
#include <utility>


enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct BodyPart {
    int x_pos;
    int y_pos;
    Direction direction;
};

class Snake 
{
    public:
        Snake(int x_pos, int y_pos);
        ~Snake();
        void grow();
        void move(Direction direction);
        int get_snek_x_pos();
        int get_snek_y_pos();
        int get_snek_length();
        void eat_apple();
        void set_snek_x_pos(int x_pos);
        void set_snek_y_pos(int y_pos);
        std::vector<BodyPart> body_parts;
        std::deque<std::pair<int, int>> body;
    private:
        int score;
        int y_pos;
        int x_pos;
        int length;
        Direction direction;
};