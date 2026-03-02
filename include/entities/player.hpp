#pragma once
#include "entities/entity.hpp"
#include "utilities/vector2D.hpp"
#include <SDL.h>

struct InputState;

struct Player : public Entity{};

Player createPlayer();

void updatePlayer(Player& player, float deltaTime, InputState state);

void renderPlayer(Player& player, SDL_Renderer* renderer);