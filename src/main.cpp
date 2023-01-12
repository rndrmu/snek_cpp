#include "config.h"
#include "core/game.h"
#include <iostream>
#include <cstring>
#include <conio.h>
#include <thread>
#include <deque>
#include <utility>
#include <algorithm>
#include <vector>



int main(int argc, char *argv[])
{
    // check for sound arg
    if (argc > 1 && std::strcmp(argv[1], "--quiet") == 0)
    {
        use_sound = false;
    }

    // setup game
    srand(time(NULL));
    setup_game();


    return 0;

}

void setup_game()
{
    // create snake
    Snake snake(game_field_width / 2, game_field_height / 2);
    // create random amount of apples
    Apple apple(rand() % game_field_width, rand() % game_field_height); 

    // construct state 
    GameState state 
    {
        game_field_width,
        game_field_height,
        snake,
        apple
    };

    // draw game
    game_loop(0.1f, state);


}

void draw_game(GameState state) 
{
    // draw snek, apple and game field 
    // color snake ANSI green and apple ANSI red
    
     for (int i = 0; i < state.height; i++)
    {
        for (int j = 0; j < state.width; j++)
        {
            if (i == 0 || i == state.height - 1 || j == 0 || j == state.width - 1)
            {
                std::cout << "#";
            }
            // draw snake body from deque
            else if (std::find(state.player.body.begin(), state.player.body.end(), std::make_pair(j, i)) != state.player.body.end())
            {
                std::cout << "\033[32m" << snake_head << "\033[0m";
            }
            
            // draw apple
            else if (state.apple.get_x_pos() == j && state.apple.get_y_pos() == i)
            {
                std::cout << "\033[31m" << apple_texture << "\033[0m";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }


    // print debug info
    std::cout << "Score: " << state.player.get_snek_length() << std::endl;
    std::cout << "Apple at: " << state.apple.get_x_pos() << " " << state.apple.get_y_pos() << std::endl;
}

void game_loop(float update_interval_secs, GameState &state)
{


    // game loop
    while (true)
    {
        // get pressed key
        if (_kbhit())
        {
            char pressed_key = _getch();
            player_control(pressed_key, state);
        }


        // check for collision with apple
        if (state.player.body.front().first == state.apple.get_x_pos() && state.player.body.front().second == state.apple.get_y_pos())
        {

            // respawn apple on random position inside game field
            int new_x_pos = rand() % (state.width - 2) + 1;
            int new_y_pos = rand() % (state.height - 2) + 1;

            state.apple.spawn(new_x_pos, new_y_pos);

            // grow snek
            state.player.grow();
        }

        // check for collision
        collision_detection(state);

        system("cls");

        draw_game(state);

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(update_interval_secs * 1000)));
    }
}

void player_control(char pressed_key, GameState &state)
{
    // check for pressed key and move snek accordingly
    switch (pressed_key)
    {
    case 'w':
        state.player.move(UP);
        break;
    case 's':
        state.player.move(DOWN);
        break;
    case 'a':
        state.player.move(LEFT);
        break;
    case 'd':
        state.player.move(RIGHT);
        break;
    default:
        break;
    }
}

void collision_detection(GameState &state) {
    // check for collision with game field borders
    if (state.player.body.front().first == 0 || state.player.body.front().first == state.width - 1 || state.player.body.front().second == 0 || state.player.body.front().second == state.height - 1)
    {

        // print game over
        system("cls");
        std::cout << "Game Over" << std::endl;
        std::cout << "Score: " << state.player.get_snek_length() << std::endl;
        std::cout << "Press any key to exit" << std::endl;
        // wait for key press
        _getch();
        exit(0);
    }

    // check for collision with snake body
    if (detect_collision(state))
    {

        // print game over
        system("cls");
        std::cout << "Game Over" << std::endl;
        std::cout << "Score: " << state.player.get_snek_length() << std::endl;
        std::cout << "Press any key to exit" << std::endl;
        // wait for key press
        _getch();
        exit(0);
    }   
}

bool detect_collision(GameState& state) {
    std::pair<int, int> snake_head = state.player.body.front();
    for (auto it = state.player.body.begin()+1; it!= state.player.body.end(); ++it) {
        if (snake_head.first == (*it).first && snake_head.second == (*it).second) {
            return true;
        }
    }
    return false;
}