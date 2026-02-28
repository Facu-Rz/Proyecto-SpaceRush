#pragma once
#include "utilities/vector2D.hpp"
#include <SDL.h>

struct InputState;

struct Player {
    SDL_Rect rectPlayer;

    Vector2D position;
    Vector2D direction;
    float speed;

    bool alive;
};

Player createPlayer();

void updatePlayer(Player& player, float deltaTime, InputState state);

void renderPlayer(Player& player, SDL_Renderer* renderer);