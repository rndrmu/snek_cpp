#pragma once

class Apple 
{
    public:
        Apple(int x, int y);
        ~Apple();
        int get_x_pos();
        int get_y_pos();
        void spawn(int size_x, int size_y);
        bool is_bad;
    private:
        int x_pos;
        int y_pos;
};