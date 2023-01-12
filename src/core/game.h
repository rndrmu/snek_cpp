#include "sound.h"
#include "snake.h"
#include "apple.h"
#include <vector>

struct GameState 
{
    int width;
    int height;
    Snake player;
    Apple apple;
};


void setup_game();

void draw_game(GameState state);

void game_loop(float update_interval_secs, GameState &state);

void player_control(char pressed_key, GameState &state);

void spawn_enemy(GameState &state);

void move_enemy(GameState &state);


void collision_detection(GameState &state);
bool detect_collision(GameState &state);


