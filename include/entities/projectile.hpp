#pragma once
#include "utilities/vector2D.hpp"
#include <SDL.h>
#include <vector>

struct Player;

enum class ProjectileType {
    Small,
    Medium,
    Big
};

struct Projectile {
    SDL_Rect rectProjectile;

    Vector2D position;
    Vector2D direction;
    float speed;

    bool alive;
    ProjectileType type;
};

Projectile createProjectile(ProjectileType type);

void updateProjectile(std::vector<Projectile>& projectiles, Player& player, float deltaTime);

void renderProjectile(std::vector<Projectile>& projectiles, SDL_Renderer* renderer);