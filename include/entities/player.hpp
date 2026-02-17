#pragma once
#include "utilities/vector2D.hpp"
#include "core/input.hpp"
#include <SDL.h>

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