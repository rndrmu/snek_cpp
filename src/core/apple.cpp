#include "apple.h"
#include <random>

Apple::Apple(int x, int y)
{
    x_pos = x;
    y_pos = y;

    // 50% percent, that it is a bad apple !! 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    is_bad = dis(gen);
};

Apple::~Apple() { };

int Apple::get_x_pos()
{
    return x_pos;
};

int Apple::get_y_pos()
{
    return y_pos;
};

void Apple::spawn(int size_x, int size_y)
{
    this->x_pos = size_x;
    this->y_pos = size_y;
};